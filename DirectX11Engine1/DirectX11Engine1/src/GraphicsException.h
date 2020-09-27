#ifndef _GRAPHICSEXCEPTION_H_
#define _GRAPHICSEXCEPTION_H_

#include"DisableUnusedDefine.h"
#include"WinException.h"
#include<vector>

class GraphicsException
{
public:
	class Exception :public WinException {
		using WinException::WinException;
	};

	class HrException :public Exception {
	public:
		HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs = {})noexcept;
		//エラー文を返す
		const char* what()const noexcept override;
		//エラータイプ
		const char* GetType()const noexcept override;
		//HRESULTを返す
		HRESULT GetErrorCode()const noexcept;
		std::string GetErrorString()const noexcept;
		//HRESULTのエラー文を文字列に変換したものを返す
		std::string GetErrorDescription()const noexcept;
		std::string GetErrorInfo()const noexcept;
	private:
		HRESULT hr;
		std::string info;
	};

	class DeviceRemovedException :public HrException {
		using HrException::HrException;
	public:
		const char* GetType()const noexcept override;
	private:
		std::string reason;
	};
};

#endif