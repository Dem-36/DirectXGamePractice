#ifndef _GRAPHICSEXCEPTION_H_
#define _GRAPHICSEXCEPTION_H_

#include"DisableUnusedDefine.h"
#include"WinException.h"

class GraphicsException
{
public:
	class Exception :public WinException {
		using WinException::WinException;
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
		std::string GetErrorString()const noexcept;
		//HRESULTのエラー文を文字列に変換したものを返す
		std::string GetErrorDescription()const noexcept;
	private:
		HRESULT hr;
	};

	class DeviceRemovedException :public HrException {
		using HrException::HrException;
	public:
		const char* GetType()const noexcept override;
	};
};

#endif