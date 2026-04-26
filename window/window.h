#pragma once
//	window.h

//不透明ポインタ作成・・・WIndows APIを隠ぺいするための前方宣言
struct HWND__;		//	HWND互換
using HWND = HWND__*;

struct HINSTANCE__;	//	HINSTANCE互換
using HINSTANCE = HINSTANCE__*;

//ウィンドウクラス
class window final
{
	HWND hwnd_;		//	ウィンドウハンドル
public:
	window() = default;
	~window() = default;

	//コピー禁止,ムーブ禁止
	window(const window&) = delete;
	window& operator=(const window&) = delete;
	window(const window&&) = delete;
	window&& operator=(const window&&) = delete;

	//@brief	ウィンドウの作成
	//@param	hInstance	インスタンスハンドル
	//@return	作成の成否
	[[nodiscard]] bool create(HINSTANCE hInstance);

	//@brief	ウィンドウハンドルの取得
	//@return	ウィンドウハンドル
	[[nodiscard]] HWND get_HWND() const noexcept;

	//@brief	メッセージループ
	//@return	ループが続行可能かどうか
	[[nodiscard]] bool message_loop() const noexcept;
};