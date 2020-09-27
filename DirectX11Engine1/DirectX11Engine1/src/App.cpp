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
	const float c = sin(timer.Peek());
	wnd.Gfx().ClearBuffer(c, c, 1.0f);
	wnd.Gfx().EndFrame();
}
