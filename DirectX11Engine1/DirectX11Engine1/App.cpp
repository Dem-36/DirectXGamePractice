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
	//��������̃C�x���g���Ă΂�Ȃ��ƍX�V����Ȃ�
	const float t = timer.Peek();
	std::ostringstream oss;
	oss << "Time elapsed: " << std::setprecision(1) << std::fixed << t << "s";

	wnd.SetTitle(oss.str());
}
