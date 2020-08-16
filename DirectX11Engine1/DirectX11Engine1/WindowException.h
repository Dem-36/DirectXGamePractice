#ifndef _WINDOWEXCEPTION_H_
#define _WINDOWEXCEPTION_H_

#include"DisableUnusedDefine.h"
#include"WinException.h"

class WindowException:public WinException
{
public:
	WindowException(int line, const char* file, HRESULT hr)noexcept;
	//�G���[����Ԃ�
	const char* what()const noexcept override;
	//�G���[�^�C�v
	virtual const char* GetType()const noexcept;
	//HRESULT�̃G���[���e�𕶎���ɕϊ�����
	static std::string TranslateErrorCode(HRESULT hr)noexcept;
	//HRESULT��Ԃ�
	HRESULT GetErrorCode()const noexcept;
	//HRESULT�̃G���[���𕶎���ɕϊ��������̂�Ԃ�
	std::string GetErrorString()const noexcept;
private:
	HRESULT hr;
};

#endif