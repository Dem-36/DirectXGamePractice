#include "Graphics.h"
#include"AdapterReader.h"
#include<vector>
#include<d3dcompiler.h>

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

	//���_���ƐF���
	struct Vertex {

		struct {
			float x;
			float y;
		}position;
		struct {
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		}color;
	};

	//���_�o�b�t�@�̍쐬
	Vertex vertices[] = {
		{0.0f,0.5f,255,0,0,0},
		{0.5f,-0.5f,0,255,0,0},
		{-0.5f,-0.5f,0,0,255,0},

		{0.0f,0.5f,255,0,0,0},
		{-0.5f,-0.5f,0,255,0,0},
		{-0.3f,0.3f,0,0,255,0},

		{0.0f,0.5f,255,0,0,0},
		{0.3f,0.3f,0,255,0,0},
		{0.5f,-0.5f,0,0,255,0},

		{0.0f,-0.8f,255,0,0,0},
		{-0.5f,-0.5f,0,255,0,0},
		{0.5f,-0.5f,0,0,255,0},

	};

	//���_�o�b�t�@�̍쐬
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
	pDeviceContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);

	//create pixel shader
	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	wrl::ComPtr<ID3DBlob> pBlob;
	GFX_THROW_INFO(D3DReadFileToBlob(L"shaders\\PixelShader.cso", &pBlob));
	GFX_THROW_INFO(pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader));

	pDeviceContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);

	//create vertex shader
	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	GFX_THROW_INFO(D3DReadFileToBlob(L"shaders\\VertexShader.cso", &pBlob));
	GFX_THROW_INFO(pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader));

	//�o�C���h
	pDeviceContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);

	//InputLayout�̍쐬
	//���_�o�b�t�@�ƒ��_�V�F�[�_�[�̓��͏����֘A�t����
	//D3D11_APPEND_ALIGNED_ELEMENT = �o�C�g���������I�Ɍv�Z���Ă����(����Ȃ�O�̂�����8u�ƂȂ�)
	wrl::ComPtr<ID3D11InputLayout> pInoutLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] = {
		{"Position",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"Color",0,DXGI_FORMAT_R8G8B8A8_UNORM,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	//�쐬
	GFX_THROW_INFO(pDevice->CreateInputLayout(
		ied,
		(UINT)std::size(ied),
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		&pInoutLayout
	));

	pDeviceContext->IASetInputLayout(pInoutLayout.Get());

	pDeviceContext->OMSetRenderTargets(1u, pRTV.GetAddressOf(), nullptr);

	//D3D11_PRIMITIVE_TOPOLOGY_LINELIST�Ő��ɂȂ�
	//D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP�Ő���אڂ��Ă�ƔF���������
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�r���[�|�[�g�ݒ�(�`��͈͎w��)
	D3D11_VIEWPORT vp;
	vp.Width = 800;
	vp.Height = 600;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	//�ݒ�
	pDeviceContext->RSSetViewports(1u, &vp);

	GFX_THROW_INFO_ONLY(pDeviceContext->Draw((UINT)std::size(vertices), 0u));
}
