#ifndef _WINDOWMESSAGEMAP_H_
#define _WINDOWMESSAGEMAP_H_

#include<unordered_map>
#include<Windows.h>

//�v���V�[�W���Ŏ擾����Msg���Awparam,lparam�����O�ɕ\������
class WindowMessageMap
{
public:
	WindowMessageMap();
	//�߂�lstring ()�ϐ�()�ŌĂ΂��
	std::string operator()(DWORD msg, LPARAM lp, WPARAM wp);
private:
	std::unordered_map<DWORD, std::string> map;
};
#endif

