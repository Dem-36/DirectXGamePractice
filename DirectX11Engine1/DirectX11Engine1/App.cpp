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
	//���b�Z�[�W�L���[���烁�b�Z�[�W�����o��
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
		//�L�[���̓��b�Z�[�W�𕶎����b�Z�[�W�ɕϊ�����
		TranslateMessage(&msg);
		//���b�Z�[�W���E�B���h�E�v���V�[�W���ɑ��M����
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
	//��������̃C�x���g���Ă΂�Ȃ��ƍX�V����Ȃ�
	const float t = timer.Peek();
	std::ostringstream oss;
	oss << "Time elapsed: " << std::setprecision(1) << std::fixed << t << "s";

	wnd.SetTitle(oss.str());
}
