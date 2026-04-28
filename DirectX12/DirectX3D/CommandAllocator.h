#pragma once
// CommandAllocator.h

#include<d3d12.h>
#include<wrl/client.h>
#include<vector>

using Microsoft::WRL::ComPtr;

//	コマンドアロケータクラス
class CommandAllocator final
{
	std::vector<ComPtr<ID3D12CommandAllocator>> command_allocator_;	//	コマンドアロケータ
public:
	//	コンストラクタとデストラクタ
	CommandAllocator() = default;
	~CommandAllocator() = default;
	//	コピー禁止,ムーブ禁止
	CommandAllocator(const CommandAllocator&) = delete;
	CommandAllocator& operator=(const CommandAllocator&) = delete;
	CommandAllocator(const CommandAllocator&&) = delete;
	CommandAllocator&& operator=(const CommandAllocator&&) = delete;

	//@brief	コマンドアロケータ作成
	//@param	device	コマンドアロケータを作成するD3D12デバイス
	//@param	index	作成するコマンドアロケータのインデックス
	//@return	作成の成否
	[[nodiscard]] bool create_command_allocator(ID3D12Device* device, const size_t& index);

	//@brief	コマンドアロケータ取得
	//@param	index 取得するコマンドアロケータのインデックス
	//@return	コマンドアロケータ
	[[nodiscard]] ID3D12CommandAllocator* get_command_allocator(const size_t& index) const noexcept;

	//@brief	コマンドアロケータリセット
	//@param	index リセットするコマンドアロケータのインデックス
	void reset_command_allocator(const size_t& index);
};