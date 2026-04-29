//	CommandList.cpp

#include"CommandList.h"
#include"../../Debug/Log.h"
#include"../../Debug/Assert.h"

[[nodiscard]] bool CommandList::create_command_list(ID3D12Device* device, ID3D12CommandAllocator* allocator) {

	//	コマンドリストの作成
	const auto hr = device->CreateCommandList(
		0,						//	ノードマスク
		D3D12_COMMAND_LIST_TYPE_DIRECT,	//	コマンドリストのタイプ
		allocator,				//	コマンドアロケータ
		nullptr,				//	初期パイプラインステート（必要に応じて指定）
		IID_PPV_ARGS(&command_list_) // コマンドリストの取得
	);
	if (FAILED(hr)) {
		LOG_HRESULT(hr);
		return false;
	}

	command_list_->Close(); // コマンドリストは作成後にクローズする必要がある
	return true;
}

[[nodiscard]] ID3D12GraphicsCommandList* CommandList::get_command_list() const noexcept {
	ASSERT(command_list_ != nullptr);
	return command_list_.Get();
}

void CommandList::reset_command_list(ID3D12CommandAllocator* allocator) {
	ASSERT(command_list_ != nullptr);
	const auto hr = command_list_->Reset(allocator, nullptr); // コマンドアロケータをリセットしてコマンドリストを再利用
	if (FAILED(hr)) {
		LOG_HRESULT(hr);
	}
}