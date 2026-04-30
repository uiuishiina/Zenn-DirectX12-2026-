#pragma once
//	Polygon.h

#include<DirectXMath.h>
#include<d3d12.h>
#include<wrl/client.h>

using Microsoft::WRL::ComPtr;


namespace Vertex
{
	struct PosColor
	{
		DirectX::XMFLOAT3 position;	//	頂点の位置
		DirectX::XMFLOAT4 color;	//	頂点の色
	};
}

//	ポリゴンクラス
class PolygonBase final
{
	//	三角形の頂点データ
	Vertex::PosColor vertices_[3] = { 
		{{ 0.0f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f} },	//	中央上の頂点
		{{ 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f} },	//	右下の頂点
		{{ -0.5f, -0.5f, 0.0f }, {0.0f, 1.0f, 0.0f, 1.0f}}	//	左下の頂点
	};

	UINT indices_[3] = { 0, 1, 2 };	//	インデックスデータ

	ComPtr<ID3D12Resource>		vertex_buffer_;			//	頂点バッファ
	ComPtr<ID3D12Resource>		index_buffer_;			//	インデックスバッファ

	D3D12_VERTEX_BUFFER_VIEW	vertex_buffer_view_{};	//	頂点バッファビュー
	D3D12_INDEX_BUFFER_VIEW		index_buffer_view_{};		//	インデックスバッファビュー

	//@brief	頂点バッファの作成
	//@param	device			D3D12デバイス
	//@return	作成の成否
	[[nodiscard]] bool create_vertex_buffer(ID3D12Device* device);

	//@brief	インデックスバッファの作成
	//@param	device			D3D12デバイス
	//@return	作成の成否
	[[nodiscard]] bool create_index_buffer(ID3D12Device* device);
public:
	//	コンストラクタとデストラクタ
	PolygonBase() = default;
	~PolygonBase() = default;
	//	コピー禁止,ムーブ禁止
	PolygonBase(const PolygonBase&) = delete;
	PolygonBase& operator=(const PolygonBase&) = delete;
	PolygonBase(const PolygonBase&&) = delete;
	PolygonBase&& operator=(const PolygonBase&&) = delete;

	//@brief	ポリゴンの初期化
	//@param	device			D3D12デバイス
	//@return	初期化の成否
	[[nodiscard]] bool initialize_Polygon(ID3D12Device* device);

	void draw_polygon(ID3D12GraphicsCommandList* command_list) const noexcept;
};