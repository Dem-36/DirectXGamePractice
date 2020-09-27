#include "WindowException.h"
#include<sstream>

std::string WindowException::Exception::TranslateErrorCode(HRESULT hr) noexcept
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

WindowException::HrException::HrException(int line, const char* file, HRESULT hr) noexcept
	:Exception(line,file),hr(hr)
{
}

const char* WindowException::HrException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
		<< std::dec << " (" << (unsigned long)GetErrorCode() << ")" << std::endl
		<< "[Description] " << GetErrorDescription() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* WindowException::HrException::GetType() const noexcept
{
	return "Window Exception";
}

HRESULT WindowException::HrException::GetErrorCode() const noexcept
{
	return hr;
}

std::string WindowException::HrException::GetErrorDescription() const noexcept
{
	return Exception::TranslateErrorCode(hr);
}

const char* WindowException::NoGfxException::GetType() const noexcept
{
	return "Window Exception [No Graphics]";
}
