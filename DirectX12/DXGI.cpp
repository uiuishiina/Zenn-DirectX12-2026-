// DXGI.cpp

#include"DXGI.h"
#include"../Debug/Log.h"
#include"../Debug/Assert.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d12.lib")


namespace {
	//	要求するD3D機能レベルのリスト...DirectX 12.2からDirectX 11.0までの機能レベルを指定
	D3D_FEATURE_LEVEL levels[] = {
	D3D_FEATURE_LEVEL_12_2,
	D3D_FEATURE_LEVEL_12_1,
	D3D_FEATURE_LEVEL_12_0,
	D3D_FEATURE_LEVEL_11_1,
	D3D_FEATURE_LEVEL_11_0
	};

	//	要求するGPUの優先度のリスト...高性能GPU、デフォルトGPU、最低消費電力GPUの順で指定	
	DXGI_GPU_PREFERENCE preferences[] = {
		DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,	//	2
		DXGI_GPU_PREFERENCE_UNSPECIFIED,		//	0
		DXGI_GPU_PREFERENCE_MINIMUM_POWER		//	1
	};
}

[[nodiscard]] bool DXGI::initialize_DXGI(){

	//	DXGIファクトリーの作成とDXGIアダプターの選択を行う
	if (!create_factory()) {
		LOG_ERROR("Failed to create DXGI factory.");
		return false;
	}

	if (!resolve_adapter()) {
		LOG_ERROR("Failed to select DXGI adapter.");
		return false;
	}

	return true;
}


[[nodiscard]] bool DXGI::create_factory() {
#if _DEBUG
	// デバッグレイヤーオン
	ComPtr<ID3D12Debug> debug{};
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debug)))) {
		debug->EnableDebugLayer();
	}
#endif

	UINT Flags = 0;
#if _DEBUG
	Flags |= DXGI_CREATE_FACTORY_DEBUG;	// デバッグフラグを設定
#endif
	//	DXGIファクトリーの作成
	const auto hr = CreateDXGIFactory2(Flags,IID_PPV_ARGS(&factory_));
	if (FAILED(hr)) {
		LOG_HRESULT(hr);
		return false;
	}
	return true;
}


[[nodiscard]] bool DXGI::resolve_adapter() {

	//	要求するGPUの優先度のリストを順に試して、最初に見つかった適切なGPUを選択
	for (const auto preference : preferences) {
		adapter_ = select_adapter(preference);
		if (adapter_.Get()) {
			LOG_INFO("Selected GPU with preference:	" + std::to_string(preference));
			return true;
		}
	}

	LOG_ERROR("Failed to select a suitable GPU.");
	return false;
}

ComPtr<IDXGIAdapter4> DXGI::select_adapter(DXGI_GPU_PREFERENCE preference) {

	// アダプタを列挙
	for (int i = 0; ; ++i)
	{
		DXGI_ADAPTER_DESC1 desc{};
		ComPtr<IDXGIAdapter4> dxgiAdapter{};

		// GPUの優先度設定してアダプタを列挙
		if (FAILED(factory_->EnumAdapterByGpuPreference(i,
			preference, IID_PPV_ARGS(&dxgiAdapter)))) {
			break;
		}

		//	アダプタの説明を取得
		dxgiAdapter->GetDesc1(&desc);

		//	ソフトウェアアダプタはスキップ
		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
			continue;
		}

		return dxgiAdapter;
	}

	LOG_ERROR("Failed to select DXGI adapter.");
	return nullptr;
}


[[nodiscard]] IDXGIFactory6* DXGI::get_factory() const noexcept {
	ASSERT(factory_ != nullptr);
	return factory_.Get();
}


[[nodiscard]] IDXGIAdapter4* DXGI::get_adapter() const noexcept {
	ASSERT(adapter_ != nullptr);
	return adapter_.Get();
}