#include"Window.h"

int CALLBACK wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow)
{
	Window wnd(800, 300, "Donkey Fart Box");

	//message pump
	MSG msg;
	bool gResult;
	//メッセージキューからメッセージを取り出す
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
		//キー入力メッセージを文字メッセージに変換する
		TranslateMessage(&msg);
		//メッセージをウィンドウプロシージャに送信する
		DispatchMessage(&msg);
	}

	if (gResult == -1) {
		return -1;
	}

	return 0;
}