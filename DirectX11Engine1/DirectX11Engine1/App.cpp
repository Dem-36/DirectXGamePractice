#include "App.h"
#include<sstream>
#include<iomanip>

App::App()
	:wnd(800,600,"The Donkey Fart Box")
{
}

int App::Go()
{
	while (true) {
		//保留中のすべてのメッセージを処理しますが、新しいメッセージをブロックしません
		if (const auto ecode = Window::ProcessMessages()) {
			//ecodeに値がある場合は終了しているので終了コードを返す
			//ProcessMessagesでWM_QUITが呼ばれているため
			return *ecode;
		}
		DoFrame();
	}
}

void App::DoFrame()
{
	//何かしらのイベントが呼ばれないと更新されない
	const float t = timer.Peek();
	std::ostringstream oss;
	oss << "Time elapsed: " << std::setprecision(1) << std::fixed << t << "s";

	wnd.SetTitle(oss.str());
}
