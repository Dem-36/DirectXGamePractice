#ifndef _WINDOWEXCEPTION_H_
#define _WINDOWEXCEPTION_H_

#include"DisableUnusedDefine.h"
#include"WinException.h"

class WindowException
{
public:
	class Exception :public WinException {
		//Exception���p��������WinException���ȗ�����
		using WinException::WinException;
	public:
		//HRESULT�̃G���[���e�𕶎���ɕϊ�����
		static std::string TranslateErrorCode(HRESULT hr)noexcept;
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
		//HRESULT�̃G���[���𕶎���ɕϊ��������̂�Ԃ�
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