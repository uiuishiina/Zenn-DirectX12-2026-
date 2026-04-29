#pragma once
//	Fence.h

#include<d3d12.h>
#include<wrl/client.h>

using Microsoft::WRL::ComPtr;

//	フェンスクラス
class Fence final
{
	ComPtr<ID3D12Fence> fence_;	//	フェンス
	HANDLE wait_event_ = nullptr;	//	フェンスイベント
	UINT64 fence_value_ = 0;	//	フェンスの値
public:
	//	コンストラクタとデストラクタ
	Fence() = default;
	~Fence() = default;
	//	コピー禁止,ムーブ禁止
	Fence(const Fence&) = delete;
	Fence& operator=(const Fence&) = delete;
	Fence(const Fence&&) = delete;
	Fence&& operator=(const Fence&&) = delete;

	//@brief	フェンス作成
	//@param	device	フェンスを作成するD3D12デバイス
	//@return	作成の成否
	[[nodiscard]] bool create_fence(ID3D12Device* device);

	//@brief	コマンドキューにフェンスをシグナル
	//@param	command_queue	フェンスをシグナルするコマンドキュー
	[[nodiscard]] UINT64 signal(ID3D12CommandQueue* command_queue) noexcept;

	//@brief	フェンス値の取得
	//@return	フェンス値
	[[nodiscard]] UINT64 get_completed_value() const noexcept;

	//@brief	フェンス取得
	//@return	フェンス
	[[nodiscard]] ID3D12Fence* get_fence() const noexcept;

	//@brief	フェンスの値を待機
	//@param	fence_value	待機するフェンスの値
	void wait_event(UINT64 fence_value) const noexcept;
};