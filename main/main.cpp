//	main.cpp

#include"../window/window.h"
#include<Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {

	window win;
	if (!win.create(hInstance)) {
		return -1;
	}
	while (win.message_loop()) {
		//	ここでゲームの更新や描画を行う
	}
	//	ウィンドウが閉じられた後のクリーンアップ処理などがあればここに記述
	return 0;
}