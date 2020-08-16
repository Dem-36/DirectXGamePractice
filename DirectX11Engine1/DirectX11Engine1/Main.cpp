#include"Window.h"

int CALLBACK wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow)
{

	try {
		Window wnd(800, 300, "Donkey Fart Box");

		//message pump
		MSG msg;
		BOOL gResult;
		//メッセージキューからメッセージを取り出す
		while ((gResult = GetMessage(&msg, nullptr, 0, 0))) {
			//キー入力メッセージを文字メッセージに変換する
			TranslateMessage(&msg);
			//メッセージをウィンドウプロシージャに送信する
			DispatchMessage(&msg);
		}

		if (gResult == -1) {
			throw WND_LAST_EXCEPT();
		}

		return msg.wParam;
	}
	//自作エラー内容表示
	catch (const WinException& e) {
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	//基底エラークラス内容表示
	catch (const std::exception& e) {
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	//それ以外
	catch (...) {
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return 0;
}