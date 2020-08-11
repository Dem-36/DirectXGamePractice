#ifndef _ERRORLOGGER_H_
#define _ERRORLOGGER_H_

#include<Windows.h>
#include"StringConverter.h"

/// <summary>
/// �G���[���O�\���p�N���X
/// </summary>
class ErrorLogger
{
public:
	static void Log(std::string message);
	static void Log(HRESULT hr, std::string message);
	static void Log(HRESULT hr, std::wstring message);
};
#endif
