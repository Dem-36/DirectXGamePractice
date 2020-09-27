#ifndef _WINDOWMESSAGEMAP_H_
#define _WINDOWMESSAGEMAP_H_

#include<unordered_map>
#include"DisableUnusedDefine.h"

//プロシージャで取得するMsg情報、wparam,lparamをログに表示する
class WindowMessageMap
{
public:
	WindowMessageMap()noexcept;
	//戻り値string ()変数()で呼ばれる
	std::string operator()(DWORD msg, LPARAM lp, WPARAM wp)const noexcept;
private:
	std::unordered_map<DWORD, std::string> map;
};
#endif

