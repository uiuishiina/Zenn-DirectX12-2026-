//	Fence.cpp

#include"Fence.h"
#include"../../Debug/Log.h"
#include"../../Debug/Assert.h"

[[nodiscard]] bool Fence::create_fence(ID3D12Device* device) {
	//	フェンスの作成
	const auto hr = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence_));
	if (FAILED(hr)) {
		LOG_HRESULT(hr);
		return false;
	}

	//	フェンスイベントの作成
	wait_event_ = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	if (wait_event_ == nullptr) {
		LOG_ERROR("Failed to create fence event");
		return false;
	}

	return true;
}


[[nodiscard]] UINT64 Fence::signal(ID3D12CommandQueue* command_queue) noexcept {
	ASSERT(fence_ != nullptr);
	fence_value_++;
	const auto hr = command_queue->Signal(fence_.Get(), fence_value_);
	if (FAILED(hr)) {
		LOG_HRESULT(hr);
	}
	return fence_value_;
}


[[nodiscard]] UINT64 Fence::get_completed_value() const noexcept {
	ASSERT(fence_ != nullptr);
	return fence_->GetCompletedValue();
}

[[nodiscard]] ID3D12Fence* Fence::get_fence() const noexcept {
	ASSERT(fence_ != nullptr);
	return fence_.Get();
}


void Fence::wait_event(UINT64 fence_value) const noexcept {
	ASSERT(fence_ != nullptr);
	if(fence_->GetCompletedValue() < fence_value) {
		fence_->SetEventOnCompletion(fence_value, wait_event_);
		WaitForSingleObject(wait_event_, INFINITE);
	}
}