//	window.cpp

#include"window.h"
#include<Windows.h>

namespace {
	//	ウィンドウプロシージャ
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		switch (uMsg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
}

[[nodiscard]] bool window::create(HINSTANCE hInstance) {

	//	ウィンドウクラスの設定
    WNDCLASS wc{};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
	wc.lpszClassName = L"SampleWindowClass";
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	//	ウィンドウクラス登録
	if (!RegisterClass(&wc)) {
		return false;
	}

	//	ウィンドウ作成
	hwnd_ = CreateWindowEx(
		0,						//	拡張スタイル
		wc.lpszClassName,		//	クラス名
		L"Sample Window",		//	ウィンドウタイトル
		WS_OVERLAPPEDWINDOW,	//	ウィンドウスタイル
		CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,	//	位置とサイズ
		nullptr,				//	親ウィンドウ
		nullptr,				//	メニューハンドル
		hInstance,				//	インスタンスハンドル
		nullptr					//	追加パラメータ
	);

	if (!hwnd_) {
		return false;
	}

	//	ウィンドウ表示
	ShowWindow(hwnd_, SW_SHOW);

	return true;
}

[[nodiscard]] HWND window::get_HWND() const noexcept {
	return hwnd_;
}

[[nodiscard]] bool window::message_loop() const noexcept {
	MSG msg{};
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {

		//	WM_QUITメッセージが来たらループを抜ける
		if (msg.message == WM_QUIT) {
			return false;
		}

		//	メッセージの翻訳とディスパッチ
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;	//	常にループを続行する
}

