#ifndef _DXGIINFOMANAGER_H_
#define _DXGIINFOMANAGER_H_

#include"DisableUnusedDefine.h"
#include<vector>
#include<string>

class DxgiInfoManager
{
public:
	DxgiInfoManager();
	~DxgiInfoManager();
	DxgiInfoManager(const DxgiInfoManager&) = delete;
	DxgiInfoManager& operator=(const DxgiInfoManager&) = delete;
	void Set()noexcept;
	std::vector<std::string> GetMessages()const;
private:
	unsigned long long next = 0u;
	struct IDXGIInfoQueue* pDxgiInfoQueue = nullptr;
};

#endif