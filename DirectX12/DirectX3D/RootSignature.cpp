//	RootSignature.cpp

#include "RootSignature.h"
#include"../../Debug/Log.h"
#include"../../Debug/Assert.h"


[[nodiscard]] bool RootSignature::create_root_signature(ID3D12Device* device) {
	
	//	ルートシグネチャの設定
	D3D12_ROOT_SIGNATURE_DESC desc{};
	desc.NumParameters = 0;	//	ルートパラメータの数
	desc.pParameters = nullptr;
	desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT; // 入力アセンブラの入力レイアウトを許可

	//	ルートシグネチャのシリアライズ
	Microsoft::WRL::ComPtr<ID3DBlob> serialized;
	Microsoft::WRL::ComPtr<ID3DBlob> error_blob;
	auto hr = D3D12SerializeRootSignature(
		&desc,
		D3D_ROOT_SIGNATURE_VERSION_1,
		&serialized,
		&error_blob
	);
	if (FAILED(hr)) {
		if (error_blob) {
			LOG_ERROR(static_cast<const char*>(error_blob->GetBufferPointer()));
		}
		LOG_HRESULT(hr);
		return false;
	}

	//	ID3D12RootSignatureの作成
	hr = device->CreateRootSignature(
		0,
		serialized->GetBufferPointer(),
		serialized->GetBufferSize(),
		IID_PPV_ARGS(&root_signature_)
	);
	if (FAILED(hr)) {
		LOG_HRESULT(hr);
		return false;
	}
	return true;
}

[[nodiscard]] ID3D12RootSignature* RootSignature::get_root_signature() const noexcept{
	ASSERT(root_signature_ != nullptr);
	return root_signature_.Get();
}