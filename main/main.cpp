//	main.cpp
#include"Application.h"	

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {

	//	アプリケーションインスタンスを作成し、初期化とメインループを実行
	Application app;
	if (!app.initialize_App(hInstance)) {
		return -1;
	}
	app.run();
	return 0;
}