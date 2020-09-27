#include "GraphicsException.h"
#include"src\dxerr\dxerr.h"
#include<sstream>

GraphicsException::HrException::HrException(int line, const char* file, HRESULT hr)noexcept
	:Exception(line, file), hr(hr) {

}

const char* GraphicsException::HrException::what()const noexcept {
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
		<< std::dec << " (" << (unsigned long)GetErrorCode() << ")" << std::endl
		<< "[Error String] " << GetErrorString() << std::endl
		<< "[Description] " << GetErrorDescription() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* GraphicsException::HrException::GetType()const noexcept {
	return "Graphics Exception";
}

HRESULT GraphicsException::HrException::GetErrorCode()const noexcept {
	return hr;
}

std::string GraphicsException::HrException::GetErrorString()const noexcept {
	return DXGetErrorString(hr);
}

std::string GraphicsException::HrException::GetErrorDescription()const noexcept {
	char buf[512];
	DXGetErrorDescription(hr, buf, sizeof(buf));
	return buf;
}

const char* GraphicsException::DeviceRemovedException::GetType()const noexcept {
	return "Graphics Exception [Device Removed] (DXGI_ERROR_DEVICE_REMOVED)";
}