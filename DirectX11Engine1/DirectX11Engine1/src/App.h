#ifndef _APP_H_
#define _APP_H_

#include"Window.h"
#include"DxTimer.h"

class App
{
public:
	App();
	//���b�Z�[�W���[�v
	int Go();
private:
	//�X�V
	void DoFrame();
private:
	Window wnd;
	DxTimer timer;
};
#endif
