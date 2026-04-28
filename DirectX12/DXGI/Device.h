#pragma once
// Device.h

#include"DXGI.h"

using Microsoft::WRL::ComPtr;

//	D3D12デバイスクラス
class Device final
{
	ComPtr<ID3D12Device> device_;	//	D3D12デバイス

	//@brief	D3D12デバイスの選択と作成
	//@param	adapter	DXGIアダプターポインタ
	//@param	featureLevel	要求する機能レベル
	//@return	作成されたD3D12デバイスポインタ
	[[nodiscard]] ComPtr<ID3D12Device> select_device(IDXGIAdapter4* adapter, D3D_FEATURE_LEVEL featureLevel);
public:
	//	コンストラクタとデストラクタ
	Device() = default;
	~Device() = default;
	//	コピー禁止,ムーブ禁止
	Device(const Device&) = delete;
	Device& operator=(const Device&) = delete;
	Device(const Device&&) = delete;
	Device&& operator=(const Device&&) = delete;

	//@brief	D3D12デバイス作成
	//@param	adapter	DXGIアダプターポインタ
	//@return	作成の成否
	[[nodiscard]] bool create_device(IDXGIAdapter4* adapter);

	//@brief	D3D12デバイス取得
	//@return	D3D12デバイスポインタ
	[[nodiscard]] ID3D12Device* get_device() const noexcept;
};