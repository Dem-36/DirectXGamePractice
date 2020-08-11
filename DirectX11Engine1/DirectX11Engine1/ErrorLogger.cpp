#include "ErrorLogger.h"
#include<comdef.h>

void ErrorLogger::Log(std::string message)
{
	std::string errorMsg = "Error: " + message;
	MessageBoxA(NULL, errorMsg.c_str(), "Error", MB_ICONERROR);
}

void ErrorLogger::Log(HRESULT hr, std::string message)
{
	GetKeyState('A' & 0x80);
	_com_error error(hr);
	std::wstring errorMsg = L"Error: " + 
		StringConverter::StringToWide(message) + L"\n" + 
		StringConverter::StringToWide(error.ErrorMessage());
	MessageBoxW(NULL, errorMsg.c_str(), L"Error", MB_ICONERROR);
}

void ErrorLogger::Log(HRESULT hr, std::wstring message)
{
	_com_error error(hr);
	std::wstring errorMsg = L"Error: " + message + L"\n" + StringConverter::StringToWide(error.ErrorMessage());
	MessageBoxW(NULL, errorMsg.c_str(), L"Error", MB_ICONERROR);
}
