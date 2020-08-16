#ifndef _WINDOWEXCEPTION_H_
#define _WINDOWEXCEPTION_H_

#include"DisableUnusedDefine.h"
#include"WinException.h"

class WindowException:public WinException
{
public:
	WindowException(int line, const char* file, HRESULT hr)noexcept;
	//エラー文を返す
	const char* what()const noexcept override;
	//エラータイプ
	virtual const char* GetType()const noexcept;
	//HRESULTのエラー内容を文字列に変換する
	static std::string TranslateErrorCode(HRESULT hr)noexcept;
	//HRESULTを返す
	HRESULT GetErrorCode()const noexcept;
	//HRESULTのエラー文を文字列に変換したものを返す
	std::string GetErrorString()const noexcept;
private:
	HRESULT hr;
};

#endif