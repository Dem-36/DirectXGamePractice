#include "Graphics.h"
#include"ReleaseProcess.h"
#include"AdapterReader.h"
#include<vector>

Graphics::Graphics(HWND hWnd)
{
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

	GFX_THROW_FAILED(D3D11CreateDeviceAndSwapChain(
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
	));
	//スワップチェーンのテクスチャをサブリソースにアクセスする
	ID3D11Resource* pBackBuffer = nullptr;
	GFX_THROW_FAILED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer)));
	GFX_THROW_FAILED(pDevice->CreateRenderTargetView(
		pBackBuffer,
		nullptr,
		&pRTV
	));
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
	HRESULT hr;
	if (FAILED(hr = pSwapChain->Present(1u, 0u))) {
		if (hr == DXGI_ERROR_DEVICE_REMOVED) {
			throw GFX_DEVICE_REMOVED_EXCEPT(pDevice->GetDeviceRemovedReason());
		}
		else {
			GFX_THROW_FAILED(hr);
		}
	}
}

void Graphics::ClearBuffer(float r, float g, float b) noexcept {
	const float color[] = { r,g,b,1.0f };
	pDeviceContext->ClearRenderTargetView(pRTV, color);
}