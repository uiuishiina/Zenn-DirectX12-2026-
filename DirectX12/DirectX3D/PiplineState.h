#pragma once
//	PiplineState.h

#include<d3d12.h>
#include<wrl/client.h>

using Microsoft::WRL::ComPtr;

class PiplineState final
{
	ComPtr<ID3D12PipelineState> pipline_state_;	//	パイプラインステートオブジェクト
public:
	PiplineState() = default;
	~PiplineState() = default;
	//	コピー禁止,ムーブ禁止
	PiplineState(const PiplineState&) = delete;
	PiplineState& operator=(const PiplineState&) = delete;
	PiplineState(const PiplineState&&) = delete;
	PiplineState&& operator=(const PiplineState&&) = delete;

	//@brief	パイプラインステートオブジェクトの作成
	//@param	device			D3D12デバイス
	//@param	root_signature	ルートシグネチャ
	//@param	vsshader		頂点シェーダ
	//@param	poshader		ピクセルシェーダ
	//@return	作成の成否
	[[nodiscard]] bool create_pipline_state(ID3D12Device* device, ID3D12RootSignature* root_signature, ID3DBlob* vsshader, ID3DBlob* poshader);

	//@brief	パイプラインステートオブジェクトの取得
	//@return	パイプラインステートオブジェクト
	[[nodiscard]] ID3D12PipelineState* get_pipline_state() const noexcept;
};