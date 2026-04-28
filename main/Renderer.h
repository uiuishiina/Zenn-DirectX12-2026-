#pragma once
// Renderer.h

#include<memory>

// 前方宣言
class DXGI;
class Device;
class CommandQueue;
class CommandAllocator;
class CommandList;

// レンダラークラス
class Renderer final
{
	const int FRAME_BUFFER_COUNT = 2;	//	フレームバッファの数

	std::unique_ptr<DXGI>	dxgi_;		//	DXGIクラスインスタンス
	std::unique_ptr<Device> device_;	//	D3D12デバイスクラスインスタンス

	std::unique_ptr<CommandQueue> command_queue_;	//	コマンドキュークラスインスタンス
	std::unique_ptr<CommandAllocator> command_allocator_;	//	コマンドアロケータクラスインスタンス
	std::unique_ptr<CommandList> command_list_;	//	コマンドリストクラスインスタンス
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
	[[nodiscard]] bool initialize_Renderer();

	//@brief	レンダラーの更新と描画処理
	void render_update();
};