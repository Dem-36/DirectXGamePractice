#ifndef _APP_H_
#define _APP_H_

#include"Window.h"

class App
{
public:
	App();
	//メッセージループ
	int Go();
private:
	//更新
	void DoFrame();
private:
	Window wnd;
};
#endif
