#include<Windows.h>
#include"WindowMessageMap.h"

//ウィンドウプロシージャ
//送られてくるメッセージによってふるまう
LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam){

	//lparam,wparamの情報をログ表示する
	static WindowMessageMap mm;
	OutputDebugString(mm(msg, lParam, wParam).c_str());

	switch (msg) {
		//windowが閉じられたとき
	case WM_CLOSE:
		//msgのwparamに引数の数値が格納される
		PostQuitMessage(0);
		break;
		//キーが押されたとき
	case WM_KEYDOWN:
		//wParamにキー情報が入っている
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
	const auto pClassName = "DirectXGame"; //ウィンドウクラス名
	//register window class
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);           //構造体のサイズ
	wc.style = CS_HREDRAW|CS_VREDRAW; //ウィンドウのスタイル
	wc.lpfnWndProc = WndProc;   //ウィンドウメッセージ処理のコールバック関数のポインタ
	wc.cbClsExtra = 0;                
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;         //ウィンドウプロシージャがあるインスタンスハンドル
	wc.hIcon = nullptr;               //アイコン
	wc.hCursor = nullptr;             //マウスカーソル
	wc.hbrBackground = nullptr;       //背景色
	wc.lpszClassName = pClassName;    //ウィンドウクラス名
	wc.hIconSm = nullptr;             //小さいサイズのアイコン

	//ウィンドウクラスを登録する
	RegisterClassEx(&wc);
	//create window
	HWND hWnd = CreateWindowEx(
		0,                  //dwStyleの拡張
		pClassName,         //ウィンドウクラス名
		"Happy hard Window",//ウィンドウタイトル
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
	//メッセージキューからメッセージを取り出す
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
		//キー入力メッセージを文字メッセージに変換する
		TranslateMessage(&msg);
		//メッセージをウィンドウプロシージャに送信する
		DispatchMessage(&msg);
	}

	if (gResult == -1)
		return  - 1;
	else {
		return msg.wParam;
	}

	return 0;
}