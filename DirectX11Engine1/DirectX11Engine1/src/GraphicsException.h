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
		//�G���[����Ԃ�
		const char* what()const noexcept override;
		//�G���[�^�C�v
		const char* GetType()const noexcept override;
		//HRESULT��Ԃ�
		HRESULT GetErrorCode()const noexcept;
		std::string GetErrorString()const noexcept;
		//HRESULT�̃G���[���𕶎���ɕϊ��������̂�Ԃ�
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