#pragma once
// DXGI.h

#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl/client.h>

using Microsoft::WRL::ComPtr;

//	DXGIクラス
class DXGI final
{
	ComPtr<IDXGIFactory6> factory_;	//DXGIファクトリー
	ComPtr<IDXGIAdapter4> adapter_;	//DXGIアダプター

	//@brief	DXGIファクトリー作成
	//@return	作成の成否
	[[nodiscard]] bool create_factory();

	//@brief	DXGIアダプター選択
	//@return	選択の成否
	[[nodiscard]] bool resolve_adapter();

	//@brief	DXGIアダプターの列挙と選択
	//@param	preference GPUの優先度
	//@return	選択されたアダプターポインタ
	ComPtr<IDXGIAdapter4> select_adapter(DXGI_GPU_PREFERENCE preference);
	
public:
	//	コンストラクタとデストラクタ
	DXGI() = default;
	~DXGI() = default;
	//	コピー禁止,ムーブ禁止
	DXGI(const DXGI&) = delete;
	DXGI& operator=(const DXGI&) = delete;
	DXGI(const DXGI&&) = delete;
	DXGI&& operator=(const DXGI&&) = delete;

	//@brief	DXGI初期化
	//@return	初期化の成否
	[[nodiscard]] bool initialize_DXGI();

	//@brief	DXGIファクトリー取得
	//@return	DXGIファクトリーポインタ
	[[nodiscard]] IDXGIFactory6* get_factory() const noexcept;

	//@brief	DXGIアダプター取得
	//@return	DXGIアダプターポインタ
	[[nodiscard]] IDXGIAdapter4* get_adapter() const noexcept;
};