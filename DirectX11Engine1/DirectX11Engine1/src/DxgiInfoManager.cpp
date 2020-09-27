#include "DxgiInfoManager.h"
#include"Window.h"
#include"Graphics.h"
#include<memory>

#pragma comment(lib,"dxguid.lib")

#define GFX_THROW_NOINFO(hrcall) if(FAILED( hr = (hrcall) ) ) throw GraphicsException::HrException(__LINE__,__FILE__,hr )

DxgiInfoManager::DxgiInfoManager()
{
	//DXGIGetDebugInterfaceの関数シグネチャを定義(dxgidebug.hですでに定義されているため)
	typedef HRESULT(WINAPI* DXGIGetDebugInterface)(REFIID, void**);

	//関数DXGIGetDebugInterfaceを含むdllをロード
	const auto hModDxgiDebug = LoadLibraryEx("dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
	if (hModDxgiDebug == nullptr) {
		throw WND_LAST_EXCEPT();
	}

	//dllでDXGIGetDebugInterfaceのアドレスを取得
	const auto DxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(
		reinterpret_cast<void*>(GetProcAddress(hModDxgiDebug, "DXGIGetDebugInterface"))
		);
	if (DxgiGetDebugInterface == nullptr) {
		throw WND_LAST_EXCEPT();
	}

	HRESULT hr;
	GFX_THROW_NOINFO(DxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), &pDxgiInfoQueue));
}

void DxgiInfoManager::Set() noexcept
{
	//GetMessages（）の次のすべてがこの呼び出し後に生成されたエラーのみを取得するように
	//インデックス（next）を設定します
	next = pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
}

std::vector<std::string> DxgiInfoManager::GetMessages() const
{
	std::vector<std::string> messages;
	const auto end = pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	for (auto i = next; i < end; i++) {
		HRESULT hr;
		SIZE_T messageLength;
		//メッセージiのサイズをバイト単位で取得します
		GFX_THROW_NOINFO(pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, nullptr, &messageLength));
		//メッセージにメモリを割り当てる
		auto bytes = std::make_unique<byte[]>(messageLength);
		auto pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());
		//メッセージを取得し、その説明をベクターにプッシュします
		GFX_THROW_NOINFO(pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, pMessage, &messageLength));
		messages.emplace_back(pMessage->pDescription);
	}
	return messages;
}
