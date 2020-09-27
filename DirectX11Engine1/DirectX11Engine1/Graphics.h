#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include"DisableUnusedDefine.h"
#include<d3d11.h>

class Graphics
{
public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator = (const Graphics&) = delete;
	~Graphics();
	void EndFrame();

	//��ʂ̃N���A
	void ClearBuffer(float r, float g, float b)noexcept;
private:
	//DirectX11�̋@�\�ɃA�N�Z�X����̂ɕK�v�ȃf�o�C�X
	ID3D11Device* pDevice = nullptr;
	//�����_�����O���ʂ��o�͂��邽�߂̃f�o�C�X
	IDXGISwapChain* pSwapChain = nullptr;
	//�`�揈�����s��
	ID3D11DeviceContext* pDeviceContext = nullptr;
	//�����_�����O�p�C�v���C������o�͂����s�N�Z������ۑ��������
	//������Q�[����ʂɔ��f������
	ID3D11RenderTargetView* pRTV = nullptr;
};

#endif