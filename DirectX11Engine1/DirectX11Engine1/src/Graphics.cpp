#include "Graphics.h"
#include"ReleaseProcess.h"
#include"AdapterReader.h"
#include<vector>

Graphics::Graphics(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	//�o�b�N�o�b�t�@�̐ݒ�
	sd.BufferDesc.Width = 0;          //�o�b�t�@�̕�
	sd.BufferDesc.Height = 0;         //�o�b�t�@�̍���
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//�}���`�T���v�����O�̐ݒ�
	sd.SampleDesc.Count = 1;   //1�s�N�Z���̐F�����߂�T���v�����O��
	sd.SampleDesc.Quality = 0; //�T���v�����O�̐����x
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
	//�X���b�v�`�F�[���̃e�N�X�`�����T�u���\�[�X�ɃA�N�Z�X����
	ID3D11Resource* pBackBuffer = nullptr;
	GFX_THROW_FAILED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer)));
	GFX_THROW_FAILED(pDevice->CreateRenderTargetView(
		pBackBuffer,
		nullptr,
		&pRTV
	));
	//���
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