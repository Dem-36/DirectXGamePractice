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
	//���b�Z�[�W�L���[���烁�b�Z�[�W�����o��
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
		//�L�[���̓��b�Z�[�W�𕶎����b�Z�[�W�ɕϊ�����
		TranslateMessage(&msg);
		//���b�Z�[�W���E�B���h�E�v���V�[�W���ɑ��M����
		DispatchMessage(&msg);
	}

	if (gResult == -1) {
		return -1;
	}

	return 0;
}