#ifndef _WIDNOW_H_
#define _WINDOW_H_

#include"DisableUnusedDefine.h"
#include"WindowException.h"
#include"Keyboard.h"
#include"Mouse.h"
#include"Graphics.h"
#include<optional>
#include<memory>

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
	void SetTitle(const std::string& title);
	static std::optional<int>ProcessMessages();
	Graphics& Gfx();
private:
	static LRESULT CALLBACK HandleMsgSetUp(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)noexcept;
public:
	Keyboard keyboard;
	Mouse mouse;
private:
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<Graphics> pGfx;
};

#define WND_EXCEPT(hr) WindowException::HrException(__LINE__,__FILE__,(hr))
//�Ō�ɔ��������G���[��Ԃ�
#define WND_LAST_EXCEPT() WindowException::HrException(__LINE__,__FILE__,GetLastError())
#define WND_NOGFX_EXCEPT() WindowException::NoGfxException(__LINE__,__FILE__)

#endif