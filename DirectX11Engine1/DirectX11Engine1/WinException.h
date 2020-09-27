#ifndef _WINEXCEPTION_H_
#define _WINEXCEPTION_H_

#include<exception>
#include<string>

//エラークラスの基底
class WinException:public std::exception
{
public:
	//コンストラクタ
	WinException(int line, const char* file)noexcept;
	//エラー内容の表示
	const char* what()const noexcept override;
	//エラータイプ 継承先で変化する
	virtual const char* GetType()const noexcept;
	//エラーが出た行を返す
	int GetLine()const noexcept;
	//ファイル名取得
	const std::string& GetFile()const noexcept;
	//エラーの行とファイル名を格納したstringを返す
	std::string GetOriginString()const noexcept;
private:
	int line;
	std::string file;
protected:
	//mutable : constメソッド内で書き換えが可能になる
	mutable std::string whatBuffer;

};

#endif