//	RenderTarget.cpp

#include"RenderTarget.h"
#include"../../Debug/Log.h"
#include"../../Debug/Assert.h"

[[nodiscard]] bool RenderTarget::create_render_target(IDXGISwapChain4* swapchain, ID3D12DescriptorHeap* heap, const UINT& descriptor_size, const UINT& buffer_size) {

	//	レンダーターゲットの数をリサイズ
	render_targets_.resize(static_cast<size_t>(buffer_size));

	rtv_descriptor_size_ = descriptor_size;

	ComPtr<ID3D12Device> device;
	heap->GetDevice(IID_PPV_ARGS(&device));	//	ディスクリプタヒープからデバイスを取得

	rtv_handle_ = heap->GetCPUDescriptorHandleForHeapStart();	//	ディスクリプタヒープのCPUハンドルを取得
	auto handle = rtv_handle_;
	//	レンダーターゲットの数だけループ
	for (UINT i = 0; i < buffer_size; ++i) {
		//	スワップチェーンからバックバッファを取得し、レンダーターゲットとして保存
		const auto hr = swapchain->GetBuffer(i, IID_PPV_ARGS(&render_targets_[i]));
		if (FAILED(hr)) {
			LOG_HRESULT(hr);
			return false;
		}

		//	レンダーターゲットビューを作成
		D3D12_RENDER_TARGET_VIEW_DESC rtv_desc{};
		rtv_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		rtv_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		device->CreateRenderTargetView(render_targets_[i].Get(), &rtv_desc, handle);
		handle.ptr += rtv_descriptor_size_;
	}
	return true;
}


[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE RenderTarget::get_rtv_handle(const size_t& index) const noexcept {
	ASSERT(index < render_targets_.size());
	auto handle = rtv_handle_;
	handle.ptr += index * rtv_descriptor_size_;
	return handle;
}


[[nodiscard]] ID3D12Resource* RenderTarget::get_render_target(const size_t& index) const noexcept {
	ASSERT(index < render_targets_.size());
	ASSERT(render_targets_[index] != nullptr);
	return render_targets_[index].Get();
}