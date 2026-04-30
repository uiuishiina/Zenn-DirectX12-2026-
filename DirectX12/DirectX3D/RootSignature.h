#pragma once
//	RootSignature.h

#include<d3d12.h>
#include<wrl/client.h>

using Microsoft::WRL::ComPtr;

class RootSignature final
{
	ComPtr<ID3D12RootSignature> root_signature_;	//	ルートシグネチャ

public:
	RootSignature() = default;
	~RootSignature() = default;
	//	コピー禁止,ムーブ禁止
	RootSignature(const RootSignature&) = delete;
	RootSignature& operator=(const RootSignature&) = delete;
	RootSignature(const RootSignature&&) = delete;
	RootSignature&& operator=(const RootSignature&&) = delete;

	//@brief	ルートシグネチャの作成
	//@param	device			D3D12デバイス
	//@return	作成の成否
	[[nodiscard]] bool create_root_signature(ID3D12Device* device);

	[[nodiscard]] ID3D12RootSignature* get_root_signature() const noexcept;
};