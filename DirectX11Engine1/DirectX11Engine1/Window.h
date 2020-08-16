#ifndef _WIDNOW_H_
#define _WINDOW_H_

#include"DisableUnusedDefine.h"
#include"WindowException.h"
#include"Keyboard.h"

class Window
{
private:
	//�E�B���h�E�쐬�ɕK�v�ȏ����Ǘ�����
	//private�̃V���O���g��
	class WindowClass
	{
	public:
		static const char* GetWindowClassName()noexcept;
		static HINSTANCE GetInstance()noexcept;
	private:
		WindowClass()noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* wndClassName = "Direct3D Engine Window";
		static WindowClass wndClass;
		HINSTANCE hInstance;
	};

public:
	Window(int width, int height, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
private:
	static LRESULT CALLBACK HandleMsgSetUp(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)noexcept;
public:
	Keyboard keyboard;
private:
	int width;
	int height;
	HWND hWnd;
};

#define WND_EXCEPT(hr) WindowException(__LINE__,__FILE__,hr)
//�Ō�ɔ��������G���[��Ԃ�
#define WND_LAST_EXCEPT() WindowException(__LINE__,__FILE__,GetLastError())

#endif