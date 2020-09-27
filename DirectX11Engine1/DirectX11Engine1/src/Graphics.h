#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include"DisableUnusedDefine.h"
#include"GraphicsException.h"
#include"DxgiInfoManager.h"
#include<d3d11.h>
#include<wrl.h>

class Graphics
{
public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator = (const Graphics&) = delete;
	~Graphics() = default;
	void EndFrame();

	//画面のクリア
	void ClearBuffer(float r, float g, float b)noexcept;
private:
#ifndef NDEBUG
	DxgiInfoManager infoManager;
#endif
	//DirectX11の機能にアクセスするのに必要なデバイス
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice = nullptr;
	//レンダリング結果を出力するためのデバイス
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain = nullptr;
	//描画処理を行う
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pDeviceContext = nullptr;
	//レンダリングパイプラインから出力されるピクセル情報を保存するもの
	//これをゲーム画面に反映させる
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRTV = nullptr;
};

#endif