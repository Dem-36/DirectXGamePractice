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

	//�X���b�v�`�F�[���̃e�N�X�`�����T�u���\�[�X�ɃA�N�Z�X����
	ID3D11Resource* pBackBuffer = nullptr;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));
	pDevice->CreateRenderTargetView(
		pBackBuffer,
		nullptr,
		&pRTV
	);
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
	pSwapChain->Present(1u, 0u);
}
