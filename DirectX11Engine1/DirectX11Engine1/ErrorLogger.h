#ifndef _ERRORLOGGER_H_
#define _ERRORLOGGER_H_

#include<Windows.h>
#include"StringConverter.h"

/// <summary>
/// エラーログ表示用クラス
/// </summary>
class ErrorLogger
{
public:
	static void Log(std::string message);
	static void Log(HRESULT hr, std::string message);
	static void Log(HRESULT hr, std::wstring message);
};
#endif
