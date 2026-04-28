#pragma once
// Application.h

#include"Renderer.h"
#include"../window/window.h"
#include<memory>

// アプリケーションクラス
class Application final
{
	std::unique_ptr<window> window_;	//	ウィンドウクラスインスタンス
	std::unique_ptr<Renderer> renderer_;	//	レンダラークラスインスタンス
public:
	Application() = default;
	~Application() = default;

	// コピー禁止,ムーブ禁止
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	Application(const Application&&) = delete;
	Application&& operator=(const Application&&) = delete;

	//@brief	アプリケーション初期化
	//@param	hInstance インスタンスハンドル
	//@return	初期化の成否
	[[nodiscard]] bool initialize_App(HINSTANCE hInstance);

	// アプリケーションメインループ
	void run();
};