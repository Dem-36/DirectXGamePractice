#ifndef _STRINGCONVERTER_H_
#define _STRINGCONVERTER_H_
#include<string>

/// <summary>
/// stringをwstringに変換する
/// </summary>
class StringConverter
{
public:
	static std::wstring StringToWide(const std::string& str);
};
#endif
