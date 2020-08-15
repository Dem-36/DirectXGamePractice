#include "Window.h"
#include"WindowMessageMap.h"
#include<sstream>

//---WindowClass---

//static�ϐ��̏�����(private)
Window::WindowClass Window::WindowClass::wndClass;

const char* Window::WindowClass::GetWindowClassName() noexcept
{
	return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	//singleton���o�R����hInstance���擾����(�B��̂���)
	return wndClass.hInstance;
}

Window::WindowClass::WindowClass() noexcept
	:hInstance(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);           //�\���̂̃T�C�Y
	wc.style = CS_HREDRAW | CS_VREDRAW; //�E�B���h�E�̃X�^�C��
	wc.lpfnWndProc = HandleMsgSetUp;   //�E�B���h�E���b�Z�[�W�����̃R�[���o�b�N�֐��̃|�C���^
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();         //�E�B���h�E�v���V�[�W��������C���X�^���X�n���h��
	wc.hIcon = nullptr;               //�A�C�R��
	wc.hCursor = nullptr;             //�}�E�X�J�[�\��
	wc.hbrBackground = nullptr;       //�w�i�F
	wc.lpszClassName = GetWindowClassName();    //�E�B���h�E�N���X��
	wc.hIconSm = nullptr;             //�������T�C�Y�̃A�C�R��

	//�E�B���h�E�N���X��o�^����
	RegisterClassEx(&wc);
}


Window::WindowClass::~WindowClass()
{
	//�E�B���h�E�N���X�̓o�^���������A�������J�����s��
	UnregisterClass(GetWindowClassName(), GetInstance());
}

//---Window---

Window::Window(int width, int height, const char* name) noexcept
{
	this->width = width;
	this->height = height;

	//window�̃T�C�Y����ݒ�
	RECT rect;
	rect.left = 100;
	rect.right = width + rect.left;
	rect.top = 100;
	rect.bottom = height + rect.top;

	//�K�v�ȃN���C�A���g�����`�̃T�C�Y�Ɋ�Â��āA�E�B���h�E�����`�̕K�v�ȃT�C�Y���v�Z���܂��B
	//���ɁA�E�B���h�E�̎l�p�`��CreateWindow�֐��ɓn���āA�N���C�A���g�̈悪�ړI�̃T�C�Y�ł���E�B���h�E���쐬�ł��܂��B
	AdjustWindowRect(&rect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	hWnd = CreateWindowEx(
		0,                  //dwStyle�̊g��
		WindowClass::GetWindowClassName(),         //�E�B���h�E�N���X��
		name,                                      //�E�B���h�E�^�C�g��
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,//dwStyle
		200,                //X
		200,                //Y
		640,                //width
		460,                //height
		nullptr,
		nullptr,
		WindowClass::GetInstance(),
		nullptr
	);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	if (hWnd != nullptr) {
		DestroyWindow(hWnd);
	}
}

LRESULT Window::HandleMsgSetUp(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	//CreateWindow()����n���ꂽ�쐬�p�����[�^�[���g�p���āAWinAPI���ŃE�B���h�E�N���X�|�C���^�[���i�[���܂�
	//�E�B���h�E���ŏ��ɍ쐬���ꂽ�Ƃ��ɁAWM_CREATE���b�Z�[�W�̑O�ɑ��M����܂��B
	if (msg == WM_NCCREATE) {

		//�쐬�f�[�^����E�B���h�E�N���X��ptr�𒊏o����
		//�E�B���h�E�v���V�[�W���ɓn����鏉�����p�����[�^�[���`���܂��B
		//�����̃����o�[�́ACreateWindowEx�֐��̃p�����[�^�[�Ɠ����ł��B
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);

		//WinAPI���Ǘ����郆�[�U�[�f�[�^��ݒ肵�āAptr���E�B���h�E�N���X�ɕۑ�����
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		//�Z�b�g�A�b�v�����������̂ŁA���b�Z�[�W�v���V�[�W����ʏ�́i��Z�b�g�A�b�v�j�n���h���[�ɐݒ肵�܂�
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		//���b�Z�[�W���E�B���h�E�N���X�n���h���[�ɓ]������
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}

	//WM_NCCREATE���b�Z�[�W�̑O�Ƀ��b�Z�[�W���󂯎�����ꍇ�́A�f�t�H���g�̃n���h���[�ŏ������܂��B
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	//�E�B���h�E�N���X�̃|�C���^�擾
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	//���b�Z�[�W���E�B���h�E�N���X�n���h���[�ɓ]������
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	//lparam,wparam�̏������O�\������
	static WindowMessageMap mm;
	OutputDebugString(mm(msg, lParam, wParam).c_str());

	switch (msg)
	{
		//window������ꂽ�Ƃ�
	case WM_CLOSE:
	{
		//msg��wparam�Ɉ����̐��l���i�[�����
		PostQuitMessage(0);
		break;
	}
	//�L�[�������ꂽ�Ƃ�
	case WM_KEYDOWN:
	{
		//wParam�ɃL�[��񂪓����Ă���
		if (wParam == 'F') {
			SetWindowText(hWnd, "Respects");
		}
		break;
	}
	case WM_KEYUP:
	{
		if (wParam == 'F') {
			SetWindowText(hWnd, "Dangerfield");
		}
		break;
	}
	case WM_CHAR:
	{
		static std::string title;
		//wParam�ɕ�����񂪓����Ă���̂ŁAtitle�̖����ɒǉ����Ă���
		title.push_back((char)wParam);
		SetWindowText(hWnd, title.c_str());
		break;
	}
	case WM_LBUTTONDOWN:
	{
		//lParam�ɂ̓E�B���h�E��ł̃}�E�X���W���i�[����Ă���
		POINTS pt = MAKEPOINTS(lParam);
		std::ostringstream oss;
		oss << pt.x << "::" << pt.y;
		SetWindowText(hWnd, oss.str().c_str());
	}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
