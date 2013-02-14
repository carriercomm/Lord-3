#ifndef __LORD_STRINGUTIL_H__
#define __LORD_STRINGUTIL_H__

LORD_NAMESPACE_BEGIN

template<Byte count>
struct SVaPassNext
{
	SVaPassNext<count-1>	big;
	Dword					dw;
};

template<> struct SVaPassNext<0>{};
//SVaPassNext - is generator of structure of any size at compile time.

class CVaPassNext
{
public:
	SVaPassNext<50> svapassnext;
	CVaPassNext(va_list &args)
	{
		try
		{
			//to avoid access violation
			memcpy(&svapassnext, args, sizeof(svapassnext));
		}
		catch (...) {}
	}
};
#define va_pass(valist) CVaPassNext(valist).svapassnext

//////////////////////////////////////////////////////////////////////////

class LORD_CORE_API StringUtil
{
private:
	StringUtil();
	~StringUtil();

public:
    static String			Replace(const String &str, const String &src, const String &dst);
    static String			Replace(const String &str, tchar src, tchar dst);
    static bool				ReplaceRet(String &str, const String &src, const String &dst);
    static void				Trim(String &str, bool bLeft = true, bool bRight = true);
    static StringArray		Split(const String &str, const String &delims, Dword maxSplits);
    static void				LowerCase(String &str);
    static void				UpperCase(String &str);
    static String			Format(const tchar *formats, ...);
	static bool				StartWith(const String &str, const String &pattern);
	static bool				EndWith(const String &str, const String &pattern);
    static bool				Equal(const String &str1, const String &str2, bool bCaseSensitive = true);
	
	static std::string		WCS2MBS(const std::wstring &str);
	static std::wstring		MBS2WCS(const std::string &str);
	static std::string		ConvMBS(const std::wstring &str);
	static std::string		ConvMBS(const std::string &str);
	static std::wstring		ConvWCS(const std::string &str);
	static std::wstring		ConvWCS(const std::wstring &str);
	static String			ConvStr(const std::wstring &str);
	static String			ConvStr(const std::string &str);
	
	static String			ToString(Real val, Word precision = 6, Word width = 0, tchar fill = _T(' '));
	static String			ToString(int val, Word width = 0, tchar fill = _T(' '));
	static String			ToString(long val, Word width = 0, tchar fill = _T(' '));
	static String			ToString(bool val, bool bYesNo = false);
	
	static float			ParseFloat(const String &val, float defaultValue = 0.0f);
	static double			ParseDouble(const String &val, double defaultValue = 0.0);
	static Real				ParseReal(const String &val, Real defaultValue = (Real)0.0);
	static int				ParseInt(const String &val, int defaultValue = 0);
	static long				ParseLong(const String &val, long defaultValue = 0);
	static bool				ParseBool(const String &val, bool defaultValue = false);
	static Dword			ParseDword(const String &val, Dword defaultValue = 0xffffffff);
	
	static bool				IsNumber(const String &val);
	static String			Hex2Char(Dword val);
};

LORD_NAMESPACE_END

#endif