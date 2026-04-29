#pragma once
//	RenderTarget.h

#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl/client.h>
#include<vector>

using Microsoft::WRL::ComPtr;

//	レンダーターゲットクラス
class RenderTarget final
{
	std::vector<ComPtr<ID3D12Resource>> render_targets_;	//	レンダーターゲット
	D3D12_CPU_DESCRIPTOR_HANDLE rtv_handle_{};						//	RTVハンドル
	UINT rtv_descriptor_size_ = 0;						//	RTVディスクリプタサイズ
public:
	RenderTarget() = default;
	~RenderTarget() = default;
	//	コピー禁止,ムーブ禁止
	RenderTarget(const RenderTarget&) = delete;
	RenderTarget& operator=(const RenderTarget&) = delete;
	RenderTarget(const RenderTarget&&) = delete;
	RenderTarget&& operator=(const RenderTarget&&) = delete;

	//@brief	レンダーターゲット作成
	//@param	swapchain	レンダーターゲットを作成するスワップチェーン
	//@param	buffer_size	レンダーターゲットを作成するスワップチェーンのバッファ数
	//@return	作成の成否
	[[nodiscard]] bool create_render_target(IDXGISwapChain4* swapchain, ID3D12DescriptorHeap* heap, const UINT& descriptor_size, const UINT& buffer_size);

	//@brief	RTVハンドル取得
	//@param	index 取得するRTVハンドルのインデックス
	//@return	RTVハンドル
	[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE get_rtv_handle(const size_t& index) const noexcept;

	//@brief	レンダーターゲット取得
	//@param	index 取得するレンダーターゲットのインデックス
	//@return	レンダーターゲットのポインタ
	[[nodiscard]] ID3D12Resource* get_render_target(const size_t& index) const noexcept;

};