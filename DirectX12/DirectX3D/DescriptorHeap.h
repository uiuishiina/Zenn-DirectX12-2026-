#pragma once
//	DescriptorHeap.h

#include<d3d12.h>
#include<wrl/client.h>

using Microsoft::WRL::ComPtr;

//	ディスクリプタヒープクラス
class DescriptorHeap final
{
	ComPtr<ID3D12DescriptorHeap> descriptor_heap_;	//	ディスクリプタヒープ
	UINT descriptor_size_ = 0;						//	ディスクリプタサイズ
public:
	DescriptorHeap() = default;
	~DescriptorHeap() = default;
	//	コピー禁止,ムーブ禁止
	DescriptorHeap(const DescriptorHeap&) = delete;
	DescriptorHeap& operator=(const DescriptorHeap&) = delete;
	DescriptorHeap(const DescriptorHeap&&) = delete;
	DescriptorHeap&& operator=(const DescriptorHeap&&) = delete;

	//@brief	ディスクリプタヒープ作成
	//@param	device ディスクリプタヒープを作成するデバイス
	//@param	type ディスクリプタヒープのタイプ
	//@param	num_descriptors ディスクリプタヒープのディスクリプタ数
	//@param	flags ディスクリプタヒープのフラグ
	//@return 作成の成否
	[[nodiscard]] bool create_descriptor_heap(ID3D12Device* device, const D3D12_DESCRIPTOR_HEAP_TYPE& type, const UINT& num_descriptors, const bool& flags);
	
	//@brief ディスクリプタサイズ取得
	//@return ディスクリプタサイズ
	[[nodiscard]] UINT get_descriptor_size() const noexcept;
	
	//@brief ディスクリプタヒープ取得
	//@return ディスクリプタヒープのポインタ
	[[nodiscard]] ID3D12DescriptorHeap* get_descriptor_heap() const noexcept;
};