#include<Windows.h>
#include"WindowMessageMap.h"

//�E�B���h�E�v���V�[�W��
//�����Ă��郁�b�Z�[�W�ɂ���Ăӂ�܂�
LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam){

	//lparam,wparam�̏������O�\������
	static WindowMessageMap mm;
	OutputDebugString(mm(msg, lParam, wParam).c_str());

	switch (msg) {
		//window������ꂽ�Ƃ�
	case WM_CLOSE:
		//msg��wparam�Ɉ����̐��l���i�[�����
		PostQuitMessage(0);
		break;
		//�L�[�������ꂽ�Ƃ�
	case WM_KEYDOWN:
		//wParam�ɃL�[��񂪓����Ă���
		if (wParam == 'F') {
			SetWindowText(hwnd, "Respects");
		}
		break;
	case WM_KEYUP:
		if (wParam == 'F') {
			SetWindowText(hwnd, "Dangerfield");
		}
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int CALLBACK wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow)
{
	const auto pClassName = "DirectXGame"; //�E�B���h�E�N���X��
	//register window class
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);           //�\���̂̃T�C�Y
	wc.style = CS_HREDRAW|CS_VREDRAW; //�E�B���h�E�̃X�^�C��
	wc.lpfnWndProc = WndProc;   //�E�B���h�E���b�Z�[�W�����̃R�[���o�b�N�֐��̃|�C���^
	wc.cbClsExtra = 0;                
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;         //�E�B���h�E�v���V�[�W��������C���X�^���X�n���h��
	wc.hIcon = nullptr;               //�A�C�R��
	wc.hCursor = nullptr;             //�}�E�X�J�[�\��
	wc.hbrBackground = nullptr;       //�w�i�F
	wc.lpszClassName = pClassName;    //�E�B���h�E�N���X��
	wc.hIconSm = nullptr;             //�������T�C�Y�̃A�C�R��

	//�E�B���h�E�N���X��o�^����
	RegisterClassEx(&wc);
	//create window
	HWND hWnd = CreateWindowEx(
		0,                  //dwStyle�̊g��
		pClassName,         //�E�B���h�E�N���X��
		"Happy hard Window",//�E�B���h�E�^�C�g��
		WS_CAPTION|WS_MINIMIZEBOX|WS_SYSMENU,//dwStyle
		200,                //X
		200,                //Y
		640,                //width
		460,                //height
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	//show the damn window
	ShowWindow(hWnd, SW_SHOW);

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

	if (gResult == -1)
		return  - 1;
	else {
		return msg.wParam;
	}

	return 0;
}