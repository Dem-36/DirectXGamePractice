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
	UnregisterClass(wndClassName, GetInstance());
}

//---Window---

Window::Window(int width, int height, const char* name)
	:width(width),height(height)
{
	//window�̃T�C�Y����ݒ�
	RECT rect;
	rect.left = 100;
	rect.right = width + rect.left;
	rect.top = 100;
	rect.bottom = height + rect.top;

	//�K�v�ȃN���C�A���g�����`�̃T�C�Y�Ɋ�Â��āA�E�B���h�E�����`�̕K�v�ȃT�C�Y���v�Z���܂��B
	//���ɁA�E�B���h�E�̎l�p�`��CreateWindow�֐��ɓn���āA�N���C�A���g�̈悪�ړI�̃T�C�Y�ł���E�B���h�E���쐬�ł��܂��B
	if (!AdjustWindowRect(&rect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE)) {
		throw WND_LAST_EXCEPT();
	}

	//�e�X�g ����G���[�N���X�ŃG���[���N����
	//throw WND_EXCEPT(ERROR_ARENA_TRASHED);
	//���N���X�ŃG���[���N����
	//throw std::runtime_error("butts butts buuuuuuuuuttssssssssss");
	//��G���[���΂�
	//throw 424324;

	hWnd = CreateWindowEx(
		0,                  //dwStyle�̊g��
		WindowClass::GetWindowClassName(),         //�E�B���h�E�N���X��
		name,                                      //�E�B���h�E�^�C�g��
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,//dwStyle
		CW_USEDEFAULT,                //X
		CW_USEDEFAULT,                //Y
		rect.right - rect.left,                //width
		rect.bottom - rect.top,                //height
		nullptr,
		nullptr,
		WindowClass::GetInstance(),
		this
	);

	if (hWnd == nullptr) {
		throw WND_LAST_EXCEPT();
	}

	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	if (hWnd != nullptr) {
		DestroyWindow(hWnd);
	}
}

void Window::SetTitle(const std::string& title)
{
	if (SetWindowText(hWnd, title.c_str()) == 0) {
		throw WND_LAST_EXCEPT();
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
		//msg��wparam�Ɉ����̐��l���i�[�����
		PostQuitMessage(0);
		break;
	//---�L�[�{�[�h����---
	//wParam�ɃL�[�{�[�h�������Ă���
	case WM_KILLFOCUS:
		keyboard.ClearState();
		break;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		if (!(lParam & 0x40000000) || keyboard.AutoRepeatIsEnabled()) {
			keyboard.OnKeyPressed(static_cast<unsigned char>(wParam));
		}
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		keyboard.OnKeyReleased(static_cast<unsigned char>(wParam));
		break;
	case WM_CHAR:
		keyboard.OnChar(static_cast<unsigned char>(wParam));
		break;
	//------------
	//---�}�E�X����--- 
	//lParam�Ƀ}�E�X�̍��W�������Ă��� wParam�ɂ̓}�E�X�z�C�[���̈ړ���?�������Ă���
	case WM_MOUSEMOVE:
	{		
		const POINTS pt = MAKEPOINTS(lParam);

		//�}�E�X�J�[�\������ʓ��ɂ���Ƃ�
		if (pt.x >= 0 && pt.x < width && pt.y >= 0 && pt.y < height) {
			mouse.OnMouseMove(pt.x, pt.y);
			//�O�܂ŃE�B���h�E�O�ɂ�����
			if (!mouse.IsInWindow()) {
				//�}�E�X���ēx�E�B���h�E�ɃL���v�`���ł���悤�ɂ���
				SetCapture(hWnd);
				//�}�E�X���E�B���h�E���ɖ߂��Ă����ʒm
				mouse.OnMouseEnter();
			}
		}
		else {
			//�}�E�X�̍��A�܂��͉E��������Ă�����
			if (wParam & (MK_LBUTTON | MK_RBUTTON)) {
				mouse.OnMouseMove(pt.x, pt.y);
			}
			//��ʊO�ɂ��āA���Ȃɂ�������ĂȂ��Ȃ�
			else {
				//�}�E�X�L���v�`�����J������
				ReleaseCapture();
				mouse.OnMouseLeave();
			}
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnLeftPressed(pt.x, pt.y);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnRightPressed(pt.x, pt.y);
		break;
	}
	case WM_LBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnLeftReleased(pt.x, pt.y);
		break;
	}
	case WM_RBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnRightReleased(pt.x, pt.y);
		break;
	}
	case WM_MOUSEWHEEL:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		//�z�C�[���l���擾(�O�Ȃ�120,���Ȃ�-120��Ԃ��H)
		short wheel = GET_WHEEL_DELTA_WPARAM(wParam);
		mouse.OnWheelDelta(pt.x, pt.y, wheel);
		break;
	}
	//------------
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
