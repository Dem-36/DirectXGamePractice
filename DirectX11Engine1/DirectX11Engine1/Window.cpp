#include "Window.h"
#include"WindowMessageMap.h"
#include<sstream>

//---WindowClass---

//static変数の初期化(private)
Window::WindowClass Window::WindowClass::wndClass;

const char* Window::WindowClass::GetWindowClassName() noexcept
{
	return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	//singletonを経由してhInstanceを取得する(唯一のもの)
	return wndClass.hInstance;
}

Window::WindowClass::WindowClass() noexcept
	:hInstance(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);           //構造体のサイズ
	wc.style = CS_HREDRAW | CS_VREDRAW; //ウィンドウのスタイル
	wc.lpfnWndProc = HandleMsgSetUp;   //ウィンドウメッセージ処理のコールバック関数のポインタ
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();         //ウィンドウプロシージャがあるインスタンスハンドル
	wc.hIcon = nullptr;               //アイコン
	wc.hCursor = nullptr;             //マウスカーソル
	wc.hbrBackground = nullptr;       //背景色
	wc.lpszClassName = GetWindowClassName();    //ウィンドウクラス名
	wc.hIconSm = nullptr;             //小さいサイズのアイコン

	//ウィンドウクラスを登録する
	RegisterClassEx(&wc);
}


Window::WindowClass::~WindowClass()
{
	//ウィンドウクラスの登録を解除し、メモリ開放を行う
	UnregisterClass(wndClassName, GetInstance());
}

//---Window---

Window::Window(int width, int height, const char* name)
{
	//windowのサイズ等を設定
	RECT rect;
	rect.left = 100;
	rect.right = width + rect.left;
	rect.top = 100;
	rect.bottom = height + rect.top;

	//必要なクライアント長方形のサイズに基づいて、ウィンドウ長方形の必要なサイズを計算します。
	//次に、ウィンドウの四角形をCreateWindow関数に渡して、クライアント領域が目的のサイズであるウィンドウを作成できます。
	BOOL check = AdjustWindowRect(&rect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
	if (!check) {
		throw WND_LAST_EXCEPT();
	}

	//テスト 自作エラークラスでエラーを起こす
	//throw WND_EXCEPT(ERROR_ARENA_TRASHED);
	//基底クラスでエラーを起こす
	//throw std::runtime_error("butts butts buuuuuuuuuttssssssssss");
	//謎エラーを飛ばす
	//throw 424324;

	hWnd = CreateWindowEx(
		0,                  //dwStyleの拡張
		WindowClass::GetWindowClassName(),         //ウィンドウクラス名
		name,                                      //ウィンドウタイトル
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

LRESULT Window::HandleMsgSetUp(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	//CreateWindow()から渡された作成パラメーターを使用して、WinAPI側でウィンドウクラスポインターを格納します
	//ウィンドウが最初に作成されたときに、WM_CREATEメッセージの前に送信されます。
	if (msg == WM_NCCREATE) {

		//作成データからウィンドウクラスにptrを抽出する
		//ウィンドウプロシージャに渡される初期化パラメーターを定義します。
		//これらのメンバーは、CreateWindowEx関数のパラメーターと同じです。
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);

		//WinAPIが管理するユーザーデータを設定して、ptrをウィンドウクラスに保存する
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		//セットアップが完了したので、メッセージプロシージャを通常の（非セットアップ）ハンドラーに設定します
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		//メッセージをウィンドウクラスハンドラーに転送する
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}

	//WM_NCCREATEメッセージの前にメッセージを受け取った場合は、デフォルトのハンドラーで処理します。
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	//ウィンドウクラスのポインタ取得
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	//メッセージをウィンドウクラスハンドラーに転送する
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	//lparam,wparamの情報をログ表示する
	//static WindowMessageMap mm;
	//OutputDebugString(mm(msg, lParam, wParam).c_str());
	switch (msg)
	{
		//windowが閉じられたとき
	case WM_CLOSE:
		//msgのwparamに引数の数値が格納される
		PostQuitMessage(0);
		break;
	case WM_KILLFOCUS:
		keyboard.ClearState();
		break;
	case WM_KEYDOWN:
		keyboard.OnKeyPressed(static_cast<unsigned char>(wParam));
		break;
	case WM_KEYUP:
		keyboard.OnKeyReleased(static_cast<unsigned char>(wParam));
		break;
	case WM_CHAR:
		keyboard.OnChar(static_cast<unsigned char>(wParam));
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
