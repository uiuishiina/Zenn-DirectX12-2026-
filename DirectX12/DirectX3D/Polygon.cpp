//	Polygon.cpp

#include"Polygon.h"
#include"../../Debug/Log.h"
#include"../../Debug/Assert.h"

[[nodiscard]] bool PolygonBase::create_vertex_buffer(ID3D12Device* device) {
	//	頂点バッファのサイズを計算
	const UINT vertex_buffer_size = sizeof(vertices_);

	//	ヒープの設定
	D3D12_HEAP_PROPERTIES heap_properties;
	heap_properties.Type = D3D12_HEAP_TYPE_UPLOAD;	//	アップロードヒープ
	heap_properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heap_properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heap_properties.CreationNodeMask = 1;
	heap_properties.VisibleNodeMask = 1;

	//	リソースの設定
	D3D12_RESOURCE_DESC resource_desc{};
	resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resource_desc.Width = vertex_buffer_size;
	resource_desc.Height = 1;
	resource_desc.DepthOrArraySize = 1;
	resource_desc.MipLevels = 1;
	resource_desc.Format = DXGI_FORMAT_UNKNOWN;
	resource_desc.SampleDesc.Count = 1;
	resource_desc.SampleDesc.Quality = 0;
	resource_desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	resource_desc.Flags = D3D12_RESOURCE_FLAG_NONE;

	//	頂点バッファの作成
	auto hr = device->CreateCommittedResource(
		&heap_properties,
		D3D12_HEAP_FLAG_NONE,
		&resource_desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertex_buffer_)
	);
	if (FAILED(hr)) {
		LOG_HRESULT(hr);
		return false;
	}

	//	頂点データを頂点バッファにコピー
	Vertex::PosColor* vertex_data_begin;
	hr = vertex_buffer_->Map(0, nullptr, reinterpret_cast<void**>(&vertex_data_begin));
	if (FAILED(hr)) {
		LOG_HRESULT(hr);
		return false;
	}

	memcpy(vertex_data_begin, vertices_, vertex_buffer_size);
	vertex_buffer_->Unmap(0, nullptr);
	// 頂点バッファビューの設定
	vertex_buffer_view_.BufferLocation = vertex_buffer_->GetGPUVirtualAddress();
	vertex_buffer_view_.StrideInBytes = sizeof(Vertex::PosColor);
	vertex_buffer_view_.SizeInBytes = vertex_buffer_size;
	return true;
}

[[nodiscard]] bool PolygonBase::create_index_buffer(ID3D12Device* device) {
	//	インデックスバッファのサイズを計算
	const UINT index_buffer_size = sizeof(indices_);	//	3つの頂点を描画するためのインデックス

	//	ヒープの設定
	D3D12_HEAP_PROPERTIES heap_properties;
	heap_properties.Type = D3D12_HEAP_TYPE_UPLOAD;	//	アップロードヒープ
	heap_properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heap_properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heap_properties.CreationNodeMask = 1;
	heap_properties.VisibleNodeMask = 1;

	//	リソースの設定
	D3D12_RESOURCE_DESC resource_desc{};
	resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resource_desc.Width = index_buffer_size;
	resource_desc.Height = 1;
	resource_desc.DepthOrArraySize = 1;
	resource_desc.MipLevels = 1;
	resource_desc.Format = DXGI_FORMAT_UNKNOWN;
	resource_desc.SampleDesc.Count = 1;
	resource_desc.SampleDesc.Quality = 0;
	resource_desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	resource_desc.Flags = D3D12_RESOURCE_FLAG_NONE;

	//	インデックスバッファの作成
	auto hr = device->CreateCommittedResource(
		&heap_properties,
		D3D12_HEAP_FLAG_NONE,
		&resource_desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&index_buffer_)
	);
	if (FAILED(hr)) {
		LOG_HRESULT(hr);
		return false;
	}
	UINT* index_data_begin;
	hr = index_buffer_->Map(0, nullptr, reinterpret_cast<void**>(&index_data_begin));
	if (FAILED(hr)) {
		LOG_HRESULT(hr);
		return false;
	}

	memcpy_s(index_data_begin, index_buffer_size, indices_, index_buffer_size);
	index_buffer_->Unmap(0, nullptr);

	index_buffer_view_.BufferLocation = index_buffer_->GetGPUVirtualAddress();
	index_buffer_view_.Format = DXGI_FORMAT_R32_UINT;
	index_buffer_view_.SizeInBytes = index_buffer_size;
	return true;
}

[[nodiscard]] bool PolygonBase::initialize_Polygon(ID3D12Device* device) {
	if (!create_vertex_buffer(device)) {
		LOG_ERROR("Failed to create vertex buffer.");
		return false;
	}
	if (!create_index_buffer(device)) {
		LOG_ERROR("Failed to create index buffer.");
		return false;
	}
	return true;
}

void PolygonBase::draw_polygon(ID3D12GraphicsCommandList* command_list) const noexcept {
	//	頂点バッファとインデックスバッファをコマンドリストに設定
	command_list->IASetVertexBuffers(0, 1, &vertex_buffer_view_);
	command_list->IASetIndexBuffer(&index_buffer_view_);
	//	プリミティブトポロジーを設定
	command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//	インデックスバッファを使用して三角形を描画
	command_list->DrawIndexedInstanced(3, 1, 0, 0, 0);
}