#include "DxgiInfoManager.h"
#include"Window.h"
#include"Graphics.h"
#include<memory>

#pragma comment(lib,"dxguid.lib")

#define GFX_THROW_NOINFO(hrcall) if(FAILED( hr = (hrcall) ) ) throw GraphicsException::HrException(__LINE__,__FILE__,hr )

DxgiInfoManager::DxgiInfoManager()
{
	//DXGIGetDebugInterface�̊֐��V�O�l�`�����`(dxgidebug.h�ł��łɒ�`����Ă��邽��)
	typedef HRESULT(WINAPI* DXGIGetDebugInterface)(REFIID, void**);

	//�֐�DXGIGetDebugInterface���܂�dll�����[�h
	const auto hModDxgiDebug = LoadLibraryEx("dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
	if (hModDxgiDebug == nullptr) {
		throw WND_LAST_EXCEPT();
	}

	//dll��DXGIGetDebugInterface�̃A�h���X���擾
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
	//GetMessages�i�j�̎��̂��ׂĂ����̌Ăяo����ɐ������ꂽ�G���[�݂̂��擾����悤��
	//�C���f�b�N�X�inext�j��ݒ肵�܂�
	next = pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
}

std::vector<std::string> DxgiInfoManager::GetMessages() const
{
	std::vector<std::string> messages;
	const auto end = pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	for (auto i = next; i < end; i++) {
		HRESULT hr;
		SIZE_T messageLength;
		//���b�Z�[�Wi�̃T�C�Y���o�C�g�P�ʂŎ擾���܂�
		GFX_THROW_NOINFO(pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, nullptr, &messageLength));
		//���b�Z�[�W�Ƀ����������蓖�Ă�
		auto bytes = std::make_unique<byte[]>(messageLength);
		auto pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());
		//���b�Z�[�W���擾���A���̐������x�N�^�[�Ƀv�b�V�����܂�
		GFX_THROW_NOINFO(pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, pMessage, &messageLength));
		messages.emplace_back(pMessage->pDescription);
	}
	return messages;
}
