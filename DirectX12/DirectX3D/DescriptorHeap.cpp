//	DescriptorHeap.cpp

#include"DescriptorHeap.h"
#include"../../Debug/Log.h"
#include"../../Debug/Assert.h"

[[nodiscard]] bool DescriptorHeap::create_descriptor_heap(ID3D12Device* device, const D3D12_DESCRIPTOR_HEAP_TYPE& type, const UINT& num_descriptors, const bool& flags) {
	
	//	ディスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC desc{};
	desc.Type = type;
	desc.NumDescriptors = num_descriptors;
	desc.Flags = flags ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	//	ディスクリプタヒープを作成
	const auto hr = device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&descriptor_heap_));
	if (FAILED(hr)) {
		LOG_HRESULT(hr);
		return false;
	}

	//	ディスクリプタサイズを取得
	descriptor_size_ = device->GetDescriptorHandleIncrementSize(type);
	return true;
}

[[nodiscard]] UINT DescriptorHeap::get_descriptor_size() const noexcept {
	ASSERT(descriptor_size_ != 0);
	return descriptor_size_;
}

[[nodiscard]] ID3D12DescriptorHeap* DescriptorHeap::get_descriptor_heap() const noexcept {
	ASSERT(descriptor_heap_ != nullptr);
	return descriptor_heap_.Get();
}