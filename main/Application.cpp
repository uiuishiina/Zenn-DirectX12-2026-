// Application.cpp

#include"Application.h"
#include"../Debug/Log.h"
#include"../Debug/Assert.h"

//	エラー処理マクロ・・・条件式がfalseのときにfalseを返す
#define Create_Check(bool_expr) \
	do { \
		if (!(bool_expr)) { \
			LOG_ERROR(#bool_expr); \
			return false; \
		} \
	} while (0)


[[nodiscard]] bool Application::initialize_App(HINSTANCE hInstance) {
	
	//	ウィンドウクラスのインスタンスを作成し、ウィンドウを初期化
	window_ = std::make_unique<window>();
	Create_Check(window_->create_window(hInstance));

	//	DXGIの初期化
	dxgi_ = std::make_unique<DXGI>();
	Create_Check(dxgi_->initialize_DXGI());

	LOG_INFO("Application initialized successfully.");
	return true;
}

void Application::run() {
	//	ウィンドウのメッセージループを実行
	while (window_->message_loop()) {
		//	ここにゲームロジックや描画処理を追加
	}
}