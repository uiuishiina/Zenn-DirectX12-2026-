// Renderer.cpp

#include"../Debug/Log.h"
#include"../Debug/Assert.h"

#include"../DirectX12/DXGI/DXGI.h"
#include"../DirectX12/DXGI/Device.h"
#include"../DirectX12/DirectX3D/CommandQueue.h"
#include"../DirectX12/DirectX3D/CommandAllocator.h"
#include"../DirectX12/DirectX3D/CommandList.h"

#include"Renderer.h"

Renderer::Renderer() = default;
Renderer::~Renderer() = default;

[[nodiscard]] bool Renderer::initialize_Renderer() {

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


	return true; // レンダラーの初期化に成功した場合はtrueを返す
}

void Renderer::render_update() {
	//	ここにレンダラーの更新と描画処理を追加
}