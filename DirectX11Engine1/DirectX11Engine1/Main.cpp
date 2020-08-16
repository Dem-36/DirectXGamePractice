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
		//���b�Z�[�W�L���[���烁�b�Z�[�W�����o��
		while ((gResult = GetMessage(&msg, nullptr, 0, 0))) {
			//�L�[���̓��b�Z�[�W�𕶎����b�Z�[�W�ɕϊ�����
			TranslateMessage(&msg);
			//���b�Z�[�W���E�B���h�E�v���V�[�W���ɑ��M����
			DispatchMessage(&msg);
		}

		if (gResult == -1) {
			throw WND_LAST_EXCEPT();
		}

		return msg.wParam;
	}
	//����G���[���e�\��
	catch (const WinException& e) {
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	//���G���[�N���X���e�\��
	catch (const std::exception& e) {
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	//����ȊO
	catch (...) {
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return 0;
}