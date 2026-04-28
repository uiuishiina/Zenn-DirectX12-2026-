//	CommandAllocator.cpp

#include"CommandAllocator.h"
#include"../../Debug/Log.h"
#include"../../Debug/Assert.h"

[[nodiscard]] bool CommandAllocator::create_command_allocator(ID3D12Device* device, const size_t& index) {
	
	command_allocator_.resize(index);
	for (size_t i = 0; i < command_allocator_.size(); i++) {
		const auto hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&command_allocator_[i]));
		if (FAILED(hr)) {
			LOG_HRESULT(hr);
			return false;
		}
	}
	return true;
}


[[nodiscard]] ID3D12CommandAllocator* CommandAllocator::get_command_allocator(const size_t& index) const noexcept {
	ASSERT(index < command_allocator_.size());
	ASSERT(command_allocator_[index] != nullptr);
	return command_allocator_[index].Get();
}


void CommandAllocator::reset_command_allocator(const size_t& index) {
	ASSERT(index < command_allocator_.size());
	ASSERT(command_allocator_[index] != nullptr);
	const auto hr = command_allocator_[index]->Reset();
	if (FAILED(hr)) {
		LOG_HRESULT(hr);
	}
}