#include "WindowException.h"
#include<sstream>

WindowException::WindowException(int line, const char* file, HRESULT hr) noexcept
	:WinException(line,file),hr(hr)
{
}

const char* WindowException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] " << GetErrorCode() << std::endl
		<< "[Description] " << GetErrorString() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* WindowException::GetType() const noexcept
{
	return "Window Exception";
}

std::string WindowException::TranslateErrorCode(HRESULT hr) noexcept
{
	char* pMsgBuf = nullptr;
	//Windows��error������Ƀ����������蓖�āA�|�C���^��������w���悤�ɂ��܂�
	DWORD nMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr
	);

	//�Ԃ���镶����̒�����0�Ȃ玸�s
	if (nMsgLen == 0) {
		return "Unidentified error code";
	}
	//�G���[��������E�B���h�E�Ɋ��蓖�Ă�ꂽ�o�b�t�@����string�ɃR�s�[���܂�
	std::string errorString = pMsgBuf;
	//���[�J���������I�u�W�F�N�g���J�����ăn���h���𖳌��ɂ���
	LocalFree(pMsgBuf);
	return errorString;
}

HRESULT WindowException::GetErrorCode() const noexcept
{
	return hr;
}

std::string WindowException::GetErrorString() const noexcept
{
	return TranslateErrorCode(hr);
}
