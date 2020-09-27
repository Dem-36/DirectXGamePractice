#include "Graphics.h"
#include"ReleaseProcess.h"
#include"AdapterReader.h"
#include<vector>

Graphics::Graphics(HWND hWnd)
{
	D3D_DRIVER_TYPE driverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
		D3D_DRIVER_TYPE_UNKNOWN
	};

	UINT driverLength = ARRAYSIZE(driverTypes);

	DXGI_SWAP_CHAIN_DESC sd = {};
	//バックバッファの設定
	sd.BufferDesc.Width = 0;          //バッファの幅
	sd.BufferDesc.Height = 0;         //バッファの高さ
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//マルチサンプリングの設定
	sd.SampleDesc.Count = 1;   //1ピクセルの色を決めるサンプリング数
	sd.SampleDesc.Quality = 0; //サンプリングの制精度
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	HRESULT hr;
	for (int i = 0; i < driverLength; i++) {
		hr = D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			0,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&sd,
			&pSwapChain,
			&pDevice,
			nullptr,
			&pDeviceContext
		);
		if (SUCCEEDED(hr))
			break;
	}

	if (FAILED(hr)) {

	}

	//スワップチェーンのテクスチャをサブリソースにアクセスする
	ID3D11Resource* pBackBuffer = nullptr;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));
	pDevice->CreateRenderTargetView(
		pBackBuffer,
		nullptr,
		&pRTV
	);
	//解放
	SafeRelease(pBackBuffer);
}

Graphics::~Graphics()
{
	SafeRelease(pRTV);
	SafeRelease(pDeviceContext);
	SafeRelease(pSwapChain);
	SafeRelease(pDevice);
}

void Graphics::EndFrame()
{
	pSwapChain->Present(1u, 0u);
}
