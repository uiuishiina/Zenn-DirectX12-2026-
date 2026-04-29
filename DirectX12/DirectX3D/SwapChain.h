#pragma once
//	SwapChain.h

#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl/client.h>

using Microsoft::WRL::ComPtr;

//	スワップチェーンクラス
class SwapChain final
{
	ComPtr<IDXGISwapChain4> swapchain_;	//	スワップチェーン
public:
	//	コンストラクタとデストラクタ
	SwapChain() = default;
	~SwapChain() = default;
	//	コピー禁止,ムーブ禁止
	SwapChain(const SwapChain&) = delete;
	SwapChain& operator=(const SwapChain&) = delete;
	SwapChain(const SwapChain&&) = delete;
	SwapChain&& operator=(const SwapChain&&) = delete;

	//@brief	スワップチェーン作成
	//@param	factory			スワップチェーンを作成するDXGIファクトリー
	//@param	command_queue	スワップチェーンを作成するコマンドキュー
	//@param	hwnd			スワップチェーンを関連付けるウィンドウのハンドル
	//@param	width.height	スワップチェーンのサイズ
	//@param	buffer_size	スワップチェーンのバッファ数
	//@return	作成の成否
	[[nodiscard]] bool create_swapchain(IDXGIFactory6* factory, ID3D12CommandQueue* command_queue, HWND hwnd, const UINT& width, const UINT& height, const size_t& buffer_size);

	//@brief	スワップチェーン取得
	//@param	index 取得するスワップチェーンのインデックス
	//@return	スワップチェーンのポインタ
	[[nodiscard]] IDXGISwapChain4* get_swapchain() const noexcept;
};