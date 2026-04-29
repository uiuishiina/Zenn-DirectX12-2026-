#pragma once
// Renderer.h

#include<vector>
#include<memory>
#include<wrl/client.h>

// 前方宣言
struct HWND__;
using HWND = HWND__*;

class DXGI;
class Device;
class CommandQueue;
class CommandAllocator;
class CommandList;
class SwapChain;
class DescriptorHeap;
class RenderTarget;
class Fence;

// レンダラークラス
class Renderer final
{
	const int FRAME_BUFFER_COUNT = 3;	//	フレームバッファの数
	std::vector<UINT64> frameFenceValue_;	//	各フレームのフェンスの値

	std::unique_ptr<DXGI>	dxgi_;		//	DXGIクラスインスタンス
	std::unique_ptr<Device> device_;	//	D3D12デバイスクラスインスタンス

	std::unique_ptr<CommandQueue>		command_queue_;		//	コマンドキュークラスインスタンス
	std::unique_ptr<CommandAllocator>	command_allocator_;	//	コマンドアロケータクラスインスタンス
	std::unique_ptr<CommandList>		command_list_;		//	コマンドリストクラスインスタンス

	std::unique_ptr<SwapChain>			swapchain_;			//	スワップチェーンクラスインスタンス
	std::unique_ptr<DescriptorHeap>		rtv_heap_;			//	RTV用ディスクリプタヒープクラスインスタンス
	std::unique_ptr<RenderTarget>		render_target_;		//	レンダーターゲットクラスインスタンス
	std::unique_ptr<Fence>				fence_;				//	フェンスクラスインスタンス
public:
	//	コンストラクタとデストラクタ
	Renderer();
	~Renderer();

	// コピー禁止,ムーブ禁止
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	Renderer(const Renderer&&) = delete;
	Renderer&& operator=(const Renderer&&) = delete;

	//@brief	レンダラーの初期化
	//@return	初期化の成否
	[[nodiscard]] bool initialize_Renderer(HWND hwnd);

	//@brief	レンダラーの更新と描画処理
	void render_update();

	//@brief	レンダラーの描画処理の終了
	void render_end();
};