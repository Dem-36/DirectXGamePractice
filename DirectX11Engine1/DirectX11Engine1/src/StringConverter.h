#ifndef _STRINGCONVERTER_H_
#define _STRINGCONVERTER_H_
#include<string>

/// <summary>
/// string‚ðwstring‚É•ÏŠ·‚·‚é
/// </summary>
class StringConverter
{
public:
	static std::wstring StringToWide(const std::string& str);
};
#endif
