#include"Window.h"
#include<sstream>

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
			static int i = 0;
			//�}�E�X�̃C�x���g����łȂ��Ȃ�
			while (!wnd.mouse.IsEmpty()) {
				////�擪�̃C�x���g���擾����
				const auto e = wnd.mouse.Read();
				////�C�x���g��Move�Ȃ�
				//if (e.GetType() == Mouse::Event::MouseType::Move) {
				//	std::ostringstream oss;
				//	oss << "Mouse Position: (" << e.GetX() << "," << e.GetY() << ")";
				//	wnd.SetTitle(oss.str());
				//}
				switch (e.GetType()) {
				/*case Mouse::Event::MouseType::Leave:
					wnd.SetTitle("Gone!");
					break;
				case Mouse::Event::MouseType::Move:
				{
					std::ostringstream oss;
					oss << "Mouse moved to (" << e.GetX() << "," << e.GetY() << ")";
					wnd.SetTitle(oss.str());
					break;
				}*/
				case Mouse::Event::MouseType::WheelUp:
					i++;
					{
						std::ostringstream oss;
						oss << "Up: " << i;
						wnd.SetTitle(oss.str());
						break;
					}
				case Mouse::Event::MouseType::WheelDown:
					i--;
					{
						std::ostringstream oss;
						oss << "Down: " << i;
						wnd.SetTitle(oss.str());
						break;
					}
				}
			}
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