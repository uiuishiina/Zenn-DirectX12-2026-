// Renderer.cpp

#include"../Debug/Log.h"
#include"../Debug/Assert.h"

#include"../DirectX12/DXGI/DXGI.h"
#include"../DirectX12/DXGI/Device.h"
#include"../DirectX12/DirectX3D/CommandQueue.h"
#include"../DirectX12/DirectX3D/CommandAllocator.h"
#include"../DirectX12/DirectX3D/CommandList.h"
#include"../DirectX12/DirectX3D/SwapChain.h"
#include"../DirectX12/DirectX3D/DescriptorHeap.h"
#include"../DirectX12/DirectX3D/RenderTarget.h"
#include"../DirectX12/DirectX3D/Fence.h"

#include"Renderer.h"

Renderer::Renderer() = default;
Renderer::~Renderer() = default;

namespace {
	//@brief	リソースバリアの作成
	//@param	resource	リソースバリアを作成するリソース
	//@param	from	リソースの現在の状態
	//@param	to		リソースの遷移先の状態
	//@return	作成されたリソースバリア
	[[nodiscard]]	D3D12_RESOURCE_BARRIER resource_Barrier(ID3D12Resource* resource, D3D12_RESOURCE_STATES from, D3D12_RESOURCE_STATES to) noexcept {
		D3D12_RESOURCE_BARRIER barrier{};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = resource;
		barrier.Transition.StateBefore = from;
		barrier.Transition.StateAfter = to;
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

		return barrier;
	}
}

[[nodiscard]] bool Renderer::initialize_Renderer(HWND hwnd) {

	//	DXGIクラスのインスタンスを作成し、初期化
	dxgi_ = std::make_unique<DXGI>();
	Create_Check(dxgi_->initialize_DXGI());

	//	D3D12デバイスクラスのインスタンスを作成し、初期化
	device_ = std::make_unique<Device>();
	Create_Check(device_->create_device(dxgi_->get_adapter()));

	//	コマンドキュークラスのインスタンスを作成し、初期化
	command_queue_ = std::make_unique<CommandQueue>();
	Create_Check(command_queue_->create_command_queue(device_->get_device()));

	//	コマンドアロケータクラスのインスタンスを作成し、初期化
	command_allocator_ = std::make_unique<CommandAllocator>();
	Create_Check(command_allocator_->create_command_allocator(device_->get_device(), FRAME_BUFFER_COUNT));

	//	コマンドリストクラスのインスタンスを作成し、初期化
	command_list_ = std::make_unique<CommandList>();
	Create_Check(command_list_->create_command_list(device_->get_device(), command_allocator_->get_command_allocator(0)));

	//	スワップチェーンクラスのインスタンスを作成し、初期化
	swapchain_ = std::make_unique<SwapChain>();
	Create_Check(swapchain_->create_swapchain(dxgi_->get_factory(), command_queue_->get_command_queue(), hwnd, 1280, 720, FRAME_BUFFER_COUNT));

	//	ディスクリプタヒープクラスのインスタンスを作成し、初期化
	rtv_heap_ = std::make_unique<DescriptorHeap>();
	Create_Check(rtv_heap_->create_descriptor_heap(device_->get_device(), D3D12_DESCRIPTOR_HEAP_TYPE_RTV, FRAME_BUFFER_COUNT, false));

	//	レンダーターゲットクラスのインスタンスを作成し、初期化
	render_target_ = std::make_unique<RenderTarget>();
	Create_Check(render_target_->create_render_target(swapchain_->get_swapchain(), rtv_heap_->get_descriptor_heap(), rtv_heap_->get_descriptor_size(), FRAME_BUFFER_COUNT));

	//	フェンスクラスのインスタンスを作成し、初期化
	fence_ = std::make_unique<Fence>();
	Create_Check(fence_->create_fence(device_->get_device()));
	frameFenceValue_.resize(FRAME_BUFFER_COUNT, 0);

	return true; // レンダラーの初期化に成功した場合はtrueを返す
}

void Renderer::render_update() {
	
	const auto backBufferIndex = swapchain_->get_swapchain()->GetCurrentBackBufferIndex();

	// 以前のフレームの GPU の処理が完了しているか確認して待機する
	if (frameFenceValue_[backBufferIndex] != 0) {
		fence_->wait_event(frameFenceValue_[backBufferIndex]);
	}

	// コマンドアロケータリセット
	command_allocator_->reset_command_allocator(backBufferIndex);
	// コマンドリストリセット
	command_list_->reset_command_list(command_allocator_->get_command_allocator(backBufferIndex));

	// リソースバリアでレンダーターゲットを Present から RenderTarget へ変更
	auto pToRT = resource_Barrier(render_target_->get_render_target(backBufferIndex), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	command_list_->get_command_list()->ResourceBarrier(1, &pToRT);

	// レンダーターゲットの設定
	D3D12_CPU_DESCRIPTOR_HANDLE handles[] = { render_target_->get_rtv_handle(backBufferIndex) };
	command_list_->get_command_list()->OMSetRenderTargets(1, handles, false, nullptr);

	// レンダーターゲットのクリア
	const float clearColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };  // 赤色でクリア
	command_list_->get_command_list()->ClearRenderTargetView(handles[0], clearColor, 0, nullptr);

	// リソースバリアでレンダーターゲットを RenderTarget から Present へ変更
	auto rtToP = resource_Barrier(render_target_->get_render_target(backBufferIndex), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	command_list_->get_command_list()->ResourceBarrier(1, &rtToP);

	// コマンドリストをクローズ
	command_list_->get_command_list()->Close();

	// コマンドキューにコマンドリストを送信
	ID3D12CommandList* ppCommandLists[] = { command_list_->get_command_list() };
	command_queue_->get_command_queue()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	// プレゼント
	swapchain_->get_swapchain()->Present(1, 0);

	const auto nextFenceValue = fence_->signal(command_queue_->get_command_queue());
	frameFenceValue_[backBufferIndex] = nextFenceValue;
}

void Renderer::render_end() {
	//	レンダラーの描画処理の終了前に必要なクリーンアップ処理があればここに追加

	//	すべてのフレームの GPU の処理が完了するまで待機
	for (auto& fenceValue : frameFenceValue_) {
		if (fenceValue != 0) {
			fence_->wait_event(fenceValue);
		}
	}
	LOG_INFO("Renderer cleanup completed. All GPU tasks have finished.");
	LOG_VARIABLE(fence_->get_completed_value());
}