#pragma once
//	CommandQueue.h

#include<d3d12.h>
#include<wrl/client.h>

using Microsoft::WRL::ComPtr;

//	コマンドキュークラス
class CommandQueue final
{
	ComPtr<ID3D12CommandQueue> command_queue_;	//	コマンドキュー
public:
	//	コンストラクタとデストラクタ
	CommandQueue() = default;
	~CommandQueue() = default;
	//	コピー禁止,ムーブ禁止
	CommandQueue(const CommandQueue&) = delete;
	CommandQueue& operator=(const CommandQueue&) = delete;
	CommandQueue(const CommandQueue&&) = delete;
	CommandQueue&& operator=(const CommandQueue&&) = delete;

	//@brief	コマンドキュー作成
	//@param	device	コマンドキューを作成するD3D12デバイス
	//@param	type	コマンドキューのタイプ
	//@return	作成の成否
	[[nodiscard]] bool create_command_queue(ID3D12Device* device);

	//@brief	コマンドキュー取得
	//@return	コマンドキュー
	[[nodiscard]] ID3D12CommandQueue* get_command_queue() const noexcept;
};