#include "App.h"
#include<sstream>
#include<iomanip>

App::App()
	:wnd(800,600,"The Donkey Fart Box")
{
}

int App::Go()
{
	//message pump
	MSG msg;
	BOOL gResult;
	//メッセージキューからメッセージを取り出す
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
		//キー入力メッセージを文字メッセージに変換する
		TranslateMessage(&msg);
		//メッセージをウィンドウプロシージャに送信する
		DispatchMessage(&msg);

		DoFrame();
	}

	if (gResult == -1) {
		throw WND_LAST_EXCEPT();
	}

	return msg.wParam;
}

void App::DoFrame()
{
	//何かしらのイベントが呼ばれないと更新されない
	const float t = timer.Peek();
	std::ostringstream oss;
	oss << "Time elapsed: " << std::setprecision(1) << std::fixed << t << "s";

	wnd.SetTitle(oss.str());
}
