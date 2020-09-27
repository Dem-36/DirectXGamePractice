#include "WindowException.h"
#include<sstream>

std::string WindowException::Exception::TranslateErrorCode(HRESULT hr) noexcept
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

WindowException::HrException::HrException(int line, const char* file, HRESULT hr) noexcept
	:Exception(line,file),hr(hr)
{
}

const char* WindowException::HrException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
		<< std::dec << " (" << (unsigned long)GetErrorCode() << ")" << std::endl
		<< "[Description] " << GetErrorDescription() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* WindowException::HrException::GetType() const noexcept
{
	return "Window Exception";
}

HRESULT WindowException::HrException::GetErrorCode() const noexcept
{
	return hr;
}

std::string WindowException::HrException::GetErrorDescription() const noexcept
{
	return Exception::TranslateErrorCode(hr);
}

const char* WindowException::NoGfxException::GetType() const noexcept
{
	return "Window Exception [No Graphics]";
}
