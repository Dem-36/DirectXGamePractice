#ifndef _WINDOWEXCEPTION_H_
#define _WINDOWEXCEPTION_H_

#include"DisableUnusedDefine.h"
#include"WinException.h"

class WindowException
{
public:
	class Exception :public WinException {
		//Exceptionを継承するやつにWinExceptionを省略する
		using WinException::WinException;
	public:
		//HRESULTのエラー内容を文字列に変換する
		static std::string TranslateErrorCode(HRESULT hr)noexcept;
	};

	class HrException :public Exception {
	public:
		HrException(int line, const char* file, HRESULT hr)noexcept;
		//エラー文を返す
		const char* what()const noexcept override;
		//エラータイプ
		const char* GetType()const noexcept override;
		//HRESULTを返す
		HRESULT GetErrorCode()const noexcept;
		//HRESULTのエラー文を文字列に変換したものを返す
		std::string GetErrorDescription()const noexcept;
	private:
		HRESULT hr;
	};

	class NoGfxException :public Exception {
	public:
		using Exception::Exception;
		const char* GetType()const noexcept override;
	};
};

#endif