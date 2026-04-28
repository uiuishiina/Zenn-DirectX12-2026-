//	Device.cpp

#include"Device.h"
#include"../../Debug/Log.h"
#include"../../Debug/Assert.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxguid.lib")

namespace {
	//	要求するD3D機能レベルのリスト...DirectX 12.2からDirectX 11.0までの機能レベルを指定
	D3D_FEATURE_LEVEL levels[] = {
	D3D_FEATURE_LEVEL_12_2,	//	49664
	D3D_FEATURE_LEVEL_12_1,	//	49408
	D3D_FEATURE_LEVEL_12_0,	//	49152
	D3D_FEATURE_LEVEL_11_1,	//	45056
	D3D_FEATURE_LEVEL_11_0	//	40960
	};
}

[[nodiscard]] bool Device::create_device(IDXGIAdapter4* adapter) {
	
	for (const auto& level : levels) {
		device_ = select_device(adapter, level);
		if (device_) {
			LOG_INFO("D3D12 device created successfully with feature level " + std::to_string(level) + ".");
			return true; // デバイスの作成に成功した場合はtrueを返す
		}
	}
	
	LOG_ERROR("Failed to create D3D12 device with any of the specified feature levels.");
	return false;
}

[[nodiscard]] ComPtr<ID3D12Device> Device::select_device(IDXGIAdapter4* adapter, D3D_FEATURE_LEVEL featureLevel) {
	ComPtr<ID3D12Device> device;
	//	D3D12デバイスの作成を試みる
	const auto hr = D3D12CreateDevice(
		adapter,					//	使用するDXGIアダプターポインタ
		featureLevel,				//	要求する機能レベル
		IID_PPV_ARGS(&device)		//	ID3D12Deviceインターフェースのポインタを受け取る
	);
	if (FAILED(hr)) {
		return nullptr; // デバイスの作成に失敗した場合はnullptrを返す
	}
	return device; // デバイスの作成に成功した場合はデバイスポインタを返す
}


[[nodiscard]] ID3D12Device* Device::get_device() const noexcept {
	ASSERT(device_ != nullptr);
	return device_.Get();
}