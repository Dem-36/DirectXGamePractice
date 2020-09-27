#ifndef _ADAPTERREADER_H_
#define _ADAPTERREADER_H_

#include<d3d11.h>
#pragma comment(lib,"DXGI.lib")
#include<wrl/client.h>
#include<vector>

using namespace Microsoft;

//IDXGIAdapter = GPU,DAC,ƒrƒfƒIƒƒ‚ƒŠ‚Ìî•ñ‚ğæ“¾‚·‚é

class AdapterData {
public:
	AdapterData(IDXGIAdapter* pAdapter);
	IDXGIAdapter* pAdapter = NULL;
	DXGI_ADAPTER_DESC desc;
};

class AdapterReader
{
public:
	static std::vector<AdapterData> GetAdapter();
private:
	static std::vector<AdapterData> adapters;
};

#endif