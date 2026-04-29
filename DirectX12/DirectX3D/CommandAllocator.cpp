//	CommandAllocator.cpp

#include"CommandAllocator.h"
#include"../../Debug/Log.h"
#include"../../Debug/Assert.h"

[[nodiscard]] bool CommandAllocator::create_command_allocator(ID3D12Device* device, const size_t& buffer_size) {
	
	//	コマンドアロケータの数をリサイズ
	command_allocators_.resize(buffer_size);

	//	コマンドアロケータの作成
	for (size_t i = 0; i < command_allocators_.size(); i++) {
		const auto hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&command_allocators_[i]));
		if (FAILED(hr)) {
			LOG_HRESULT(hr);
			return false;
		}
	}
	return true;
}


[[nodiscard]] ID3D12CommandAllocator* CommandAllocator::get_command_allocator(const size_t& index) const noexcept {
	ASSERT(index < command_allocators_.size());
	ASSERT(command_allocators_[index] != nullptr);
	return command_allocators_[index].Get();
}


void CommandAllocator::reset_command_allocator(const size_t& index) {
	ASSERT(index < command_allocators_.size());
	ASSERT(command_allocators_[index] != nullptr);
	const auto hr = command_allocators_[index]->Reset();
	if (FAILED(hr)) {
		LOG_HRESULT(hr);
	}
}