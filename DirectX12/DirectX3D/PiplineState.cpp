//	PiplineState.cpp

#include"PiplineState.h"
#include"../../Debug/Log.h"
#include"../../Debug/Assert.h"

[[nodiscard]] bool PiplineState::create_pipline_state(ID3D12Device* device, ID3D12RootSignature* root_signature, ID3DBlob* vsshader, ID3DBlob* poshader) {

	//	頂点レイアウト作成
	const D3D12_INPUT_ELEMENT_DESC input_element_desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};

	//	ラスタライザステートの設定
	D3D12_RASTERIZER_DESC rasterizer_desc{};
	rasterizer_desc.FillMode = D3D12_FILL_MODE_SOLID;	//	塗りつぶしモード
	rasterizer_desc.CullMode = D3D12_CULL_MODE_BACK;	//	カリングモード
	rasterizer_desc.FrontCounterClockwise = FALSE;	//	頂点の順序
	rasterizer_desc.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;	//	深度バイアス
	rasterizer_desc.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;	//	深度バイアスクランプ
	rasterizer_desc.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;	//	傾斜スケーリングされた深度バイアス
	rasterizer_desc.DepthClipEnable = TRUE;	//	深度クリッピングの有効化
	rasterizer_desc.MultisampleEnable = FALSE;	//	マルチサンプルの有効化
	rasterizer_desc.AntialiasedLineEnable = FALSE;	//	アンチエイリアスされたラインの有効化
	rasterizer_desc.ForcedSampleCount = 0;	//	強制サンプル数
	rasterizer_desc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;	//	保守的なラスタライゼーションのモード

	//	ブレンドステートの設定
	const D3D12_RENDER_TARGET_BLEND_DESC default_render_target_blend_desc{
		FALSE, FALSE,
		D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
		D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
		D3D12_LOGIC_OP_NOOP,
		D3D12_COLOR_WRITE_ENABLE_ALL
	};

	//	グラフィックスパイプラインステートの設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC desc{};
	desc.InputLayout = { input_element_desc, _countof(input_element_desc) };
	desc.pRootSignature = root_signature;
	desc.RasterizerState = rasterizer_desc;
	desc.VS = { vsshader->GetBufferPointer(), vsshader->GetBufferSize() };
	desc.PS = { poshader->GetBufferPointer(), poshader->GetBufferSize() };
	desc.BlendState.AlphaToCoverageEnable = FALSE;
	desc.BlendState.IndependentBlendEnable = FALSE;
	desc.SampleMask = UINT_MAX;
	desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	desc.NumRenderTargets = 1;
	desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;

	//	ブレンドステートの設定
	for (auto& render_target_blend_desc : desc.BlendState.RenderTarget) {
		render_target_blend_desc = default_render_target_blend_desc;
	}
	
	const auto hr = device->CreateGraphicsPipelineState(&desc, IID_PPV_ARGS(&pipline_state_));
	if (FAILED(hr)) {
		LOG_HRESULT(hr);
		return false;
	}
	return true;
}

[[nodiscard]] ID3D12PipelineState* PiplineState::get_pipline_state() const noexcept {
	ASSERT(pipline_state_ != nullptr);
	return pipline_state_.Get();
}