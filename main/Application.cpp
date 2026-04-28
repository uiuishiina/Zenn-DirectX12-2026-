// Application.cpp

#include"Application.h"
#include"../Debug/Log.h"
#include"../Debug/Assert.h"

[[nodiscard]] bool Application::initialize_App(HINSTANCE hInstance) {
	
	//	ウィンドウクラスのインスタンスを作成し、ウィンドウを初期化
	window_ = std::make_unique<window>();
	Create_Check(window_->create_window(hInstance));

	//	レンダラークラスのインスタンスを作成し、初期化
	renderer_ = std::make_unique<Renderer>();
	Create_Check(renderer_->initialize_Renderer());

	LOG_INFO("Application initialized successfully.");
	return true;
}

void Application::run() {
	//	ウィンドウのメッセージループを実行
	while (window_->message_loop()) {
		//	レンダラーの更新と描画処理を実行
		renderer_->render_update();
	}
}