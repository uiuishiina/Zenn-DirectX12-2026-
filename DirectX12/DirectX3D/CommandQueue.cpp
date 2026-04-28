//	CommandQueue.cpp

#include"CommandQueue.h"
#include"../../Debug/Log.h"
#include"../../Debug/Assert.h"

[[nodiscard]] bool CommandQueue::create_command_queue(ID3D12Device* device) {
	D3D12_COMMAND_QUEUE_DESC desc{};
	desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask = 0;
	const auto hr = device->CreateCommandQueue(&desc, IID_PPV_ARGS(&command_queue_));
	if (FAILED(hr)) {
		LOG_HRESULT(hr);
		return false;
	}
	return true;
}


[[nodiscard]] ID3D12CommandQueue* CommandQueue::get_command_queue() const noexcept {
	ASSERT(command_queue_ != nullptr);
	return command_queue_.Get();
}