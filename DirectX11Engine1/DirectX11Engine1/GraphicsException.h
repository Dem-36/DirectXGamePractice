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
		//�G���[����Ԃ�
		const char* what()const noexcept override;
		//�G���[�^�C�v
		const char* GetType()const noexcept override;
		//HRESULT��Ԃ�
		HRESULT GetErrorCode()const noexcept;
		std::string GetErrorString()const noexcept;
		//HRESULT�̃G���[���𕶎���ɕϊ��������̂�Ԃ�
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