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
		//�ۗ����̂��ׂẴ��b�Z�[�W���������܂����A�V�������b�Z�[�W���u���b�N���܂���
		if (const auto ecode = Window::ProcessMessages()) {
			//ecode�ɒl������ꍇ�͏I�����Ă���̂ŏI���R�[�h��Ԃ�
			//ProcessMessages��WM_QUIT���Ă΂�Ă��邽��
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
