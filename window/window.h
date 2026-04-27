#pragma once
//	window.h

#include<Windows.h>

#define WIN32_LEAN_AND_MEAN	//	Windowsヘッダの軽量化

//ウィンドウクラス
class window final
{
	HWND hwnd_;		//	ウィンドウハンドル
	HINSTANCE hInstance_;	//	インスタンスハンドル
public:
	//	コンストラクタとデストラクタ
	window() = default;
	~window() = default;

	//	コピー禁止,ムーブ禁止
	window(const window&) = delete;
	window& operator=(const window&) = delete;
	window(const window&&) = delete;
	window&& operator=(const window&&) = delete;

	//@brief	ウィンドウの作成
	//@param	hInstance	インスタンスハンドル
	//@return	作成の成否
	[[nodiscard]] bool create_window(HINSTANCE hInstance);

	//@brief	ウィンドウハンドルの取得
	//@return	ウィンドウハンドル
	[[nodiscard]] HWND get_HWND() const noexcept;

	//@brief	メッセージループ
	//@return	ループが続行可能かどうか
	[[nodiscard]] bool message_loop() const noexcept;
};