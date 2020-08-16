#include "WindowException.h"
#include<sstream>

WindowException::WindowException(int line, const char* file, HRESULT hr) noexcept
	:WinException(line,file),hr(hr)
{
}

const char* WindowException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] " << GetErrorCode() << std::endl
		<< "[Description] " << GetErrorString() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* WindowException::GetType() const noexcept
{
	return "Window Exception";
}

std::string WindowException::TranslateErrorCode(HRESULT hr) noexcept
{
	char* pMsgBuf = nullptr;
	//Windowsはerror文字列にメモリを割り当て、ポインタがそれを指すようにします
	DWORD nMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr
	);

	//返される文字列の長さが0なら失敗
	if (nMsgLen == 0) {
		return "Unidentified error code";
	}
	//エラー文字列をウィンドウに割り当てられたバッファからstringにコピーします
	std::string errorString = pMsgBuf;
	//ローカルメモリオブジェクトを開放してハンドルを無効にする
	LocalFree(pMsgBuf);
	return errorString;
}

HRESULT WindowException::GetErrorCode() const noexcept
{
	return hr;
}

std::string WindowException::GetErrorString() const noexcept
{
	return TranslateErrorCode(hr);
}
