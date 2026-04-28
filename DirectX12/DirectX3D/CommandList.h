#pragma once
// CommandList.h

#include<d3d12.h>
#include<wrl/client.h>

using Microsoft::WRL::ComPtr;

//	コマンドリストクラス
class CommandList final
{
	ComPtr<ID3D12GraphicsCommandList> command_list_;	//	コマンドリスト
public:
	//	コンストラクタとデストラクタ
	CommandList() = default;
	~CommandList() = default;
	//	コピー禁止,ムーブ禁止
	CommandList(const CommandList&) = delete;
	CommandList& operator=(const CommandList&) = delete;
	CommandList(const CommandList&&) = delete;
	CommandList&& operator=(const CommandList&&) = delete;

	//@brief	コマンドリスト作成
	//@param	device	コマンドリストを作成するD3D12デバイス
	//@return	作成の成否
	[[nodiscard]] bool create_command_list(ID3D12Device* device, ID3D12CommandAllocator* allocator);

	//@brief	コマンドリスト取得
	//@return	コマンドリスト
	[[nodiscard]] ID3D12GraphicsCommandList* get_command_list() const noexcept;

	//@brief	コマンドリストリセット
	//@param	allocator	コマンドリストをリセットするコマンドアロケータ
	void reset_command_list(ID3D12CommandAllocator* allocator);
};