#include "Graphics.h"
#include"AdapterReader.h"
#include<vector>

//����cpp���̂ݏȗ�
namespace wrl = Microsoft::WRL;


//hr�͂��̃}�N�����g�p�O�Ƀ��[�J���Ƃ��Đ錾���Ă���
#define GFX_EXCEPT_NOINFO(hr) GraphicsException::HrException(__LINE__,__FILE__,(hr) )
#define GFX_THROW_NOINFO(hrcall) if(FAILED( hr = (hrcall) ) ) throw GraphicsException::HrException( __LINE__,__FILE__,hr )

#ifndef NDEBUG
#define GFX_EXCEPT(hr) GraphicsException::HrException(__LINE__,__FILE__,(hr),infoManager.GetMessages() )
#define GFX_THROW_INFO(hrcall) infoManager.Set(); if(FAILED( hr = (hrcall) ) ) throw GFX_EXCEPT(hr)
#define GFX_DEVICE_REMOVED_EXCEPT(hr) GraphicsException::DeviceRemovedException(__LINE__,__FILE__,(hr),infoManager.GetMessages() )
#define GFX_THROW_INFO_ONLY(call) infoManager.Set(); (call); {auto v = infoManager.GetMessages(); if(!v.empty()) {throw GraphicsException::InfoException(__LINE__,__FILE__,v);}}
#else
#define GFX_EXCEPT(hr) GraphicsException::HrException(__LINE__,__FILE__,(hr) )
#define GFX_THROW_INFO(hrcall) GFX_THROW_NOINFO(hrcall)
#define GFX_DEVICE_REMOVED_EXCEPT(hr) GraphicsException::DeviceRemovedException(__LINE__,__FILE__,(hr) )
#define GFX_THROW_INFO_ONLY(call) (call)
#endif


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

	UINT swapCreateFlags = 0u;
#ifndef NDEBUG
	swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT hr;

	GFX_THROW_INFO(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		swapCreateFlags,
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
	wrl::ComPtr<ID3D11Resource> pBackBuffer;
	GFX_THROW_INFO(pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer));
	GFX_THROW_INFO(pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pRTV));
}

void Graphics::EndFrame()
{
	HRESULT hr;
#ifndef NDEBUG
	infoManager.Set();
#endif

	if (FAILED(hr = pSwapChain->Present(1u, 0u))) {
		if (hr == DXGI_ERROR_DEVICE_REMOVED) {
			throw GFX_DEVICE_REMOVED_EXCEPT(pDevice->GetDeviceRemovedReason());
		}
		else {
			throw GFX_EXCEPT(hr);
		}
	}
}

void Graphics::ClearBuffer(float r, float g, float b) noexcept {
	const float color[] = { r,g,b,1.0f };
	pDeviceContext->ClearRenderTargetView(pRTV.Get(), color);
}

void Graphics::DrawTriangle()
{
	HRESULT hr;

	struct Vertex {
		float x, y;
	};

	//���_�o�b�t�@�̍쐬
	const Vertex vertices[] = {
		{0.0f,0.5f},
		{0.5f,-0.5f},
		{-0.5f,-0.5f}
	};

	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = sizeof(vertices);
	bd.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices;
	GFX_THROW_INFO(pDevice->CreateBuffer(&bd, &sd, &pVertexBuffer));

	//�p�C�v���C���Ƀo�C���h
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	pDeviceContext->IASetVertexBuffers(0u,1u, &pVertexBuffer, &stride, &offset);

	GFX_THROW_INFO_ONLY(pDeviceContext->Draw(3u, 0u));
}
