#include "CoreStd.h"
#include "StringUtil.h"
//#include "Util/Assert.h"

#if (LORD_PLATFORM == LORD_PLATFORM_WINDOWS)
#	define WIN32_LEAN_AND_MEAN
#	define _CRT_SECURE_NO_WARNINGS
#	include <Windows.h>
#endif

LORD_NAMESPACE_BEGIN

static tchar _HexToChar[] =
{
	_T('0'), _T('1'), _T('2'), _T('3'), _T('4'), _T('5'), _T('6'), _T('7'), _T('8'), _T('9'), _T('a'), _T('b'), _T('c'), _T('d'), _T('e'), _T('f')
};

StringUtil::StringUtil()
{
}

StringUtil::~StringUtil()
{
}

String StringUtil::Replace(const String &str, const String &src, const String &dst)
{    
	if (src == dst)
		return str;
    
	String out = str;
	size_t pos = str.find(src, 0);
	while (pos != String::npos)
	{
		out.replace(pos, src.size(), dst);
		pos = out.find(src, pos+dst.size());
	}
    
	return out;
}

String StringUtil::Replace(const String &str, tchar src, tchar dst)
{
	String out = str;
	tchar *buf = &(*out.begin());
	while (*buf)
	{
		if (*buf == src)
			*buf = dst;
		buf++;
	}
    
	return out;
}

bool StringUtil::ReplaceRet(String &str, const String &src, const String &dst)
{    
	if (src == dst)
		return false;
    
	bool bReplaced = false;
	size_t pos = str.find(src, 0);
	
	if(pos != String::npos)
	{
		str.replace(pos, src.size(), dst);
		bReplaced = true;
	}
    
	return bReplaced;
}

void StringUtil::Trim(String &str, bool bLeft, bool bRight)
{
	/*
     size_t lspaces, rspaces, len = length(), i;
     
     lspaces = rspaces = 0;
     
     if( left )
     {
     // Find spaces / tabs on the left
     for( i = 0;
     i < len && ( at(i) == ' ' || at(i) == '\t' || at(i) == '\r');
     ++lspaces, ++i );
     }
     
     if( right && lspaces < len )
     {
     // Find spaces / tabs on the right
     for( i = len - 1;
     i >= 0 && ( at(i) == ' ' || at(i) == '\t' || at(i) == '\r');
     rspaces++, i-- );
     }
     
     *this = substr(lspaces, len-lspaces-rspaces);
     */
	static const String delims = _T(" \t\r\n");
	if(bRight)
		str.erase(str.find_last_not_of(delims)+1); // trim right
	if(bLeft)
		str.erase(0, str.find_first_not_of(delims)); // trim left
}

StringArray StringUtil::Split(const String &str, const String &delims, Dword maxSplits)
{
	StringArray ret;
	// Pre-allocate some space for performance
	ret.reserve(maxSplits ? maxSplits+1 : 10);    // 10 is guessed capacity for most case
    
	Dword numSplits = 0;
    
	// Use STL methods
	size_t start, pos;
	start = 0;
	do
	{
		pos = str.find_first_of(delims, start);
		if (pos == start)
		{
			// Do nothing
			start = pos + 1;
		}
		else if (pos == String::npos || (maxSplits && numSplits == maxSplits))
		{
			// Copy the rest of the string
			ret.push_back( str.substr(start) );
			break;
		}
		else
		{
			// Copy up to delimiter
			ret.push_back( str.substr(start, pos - start) );
			start = pos + 1;
		}
		// parse up to next real data
		start = str.find_first_not_of(delims, start);
		++numSplits;
        
	} while (pos != String::npos);
    
	return ret;
}

void StringUtil::LowerCase(String &str)
{
	std::transform(str.begin(), str.end(), str.begin(), tolower);
}

void StringUtil::UpperCase(String &str)
{
	std::transform(str.begin(), str.end(), str.begin(), toupper);
}

String StringUtil::Format(const tchar *formats, ... )
{
	tchar szBuffer[4096];
    
	va_list args;
	va_start(args, formats);
#if (LORD_CHARSET == LORD_CHARSET_UNICODE)
    vswprintf(szBuffer, formats, args);
#else
    vsprintf(szBuffer, formats, args);
#endif
	va_end(args);
    
	return szBuffer;
}

bool StringUtil::StartWith(const String &str, const String &pattern)
{
	size_t thisLen = str.length();
	size_t patternLen = pattern.length();
	if (thisLen < patternLen || patternLen == 0)
		return false;
    
	String startOfThis = str.substr(0, patternLen);
    
	return (startOfThis == pattern);
}

bool StringUtil::EndWith(const String &str, const String &pattern)
{
	size_t thisLen = str.length();
	size_t patternLen = pattern.length();
	if (thisLen < patternLen || patternLen == 0)
		return false;
    
	String endOfThis = str.substr(thisLen - patternLen, patternLen);
    
	return (endOfThis == pattern);
}

bool StringUtil::Equal(const String &str1, const String &str2, bool bCaseSensitive/*= true*/)
{
	if (bCaseSensitive)
	{
		return (str1 == str2);
	}
	else
	{
		String lstr1 = str1;
		String lstr2 = str2;
		LowerCase(lstr1);
		LowerCase(lstr2);
		return (lstr1 == lstr2);
	}
}

std::string StringUtil::WCS2MBS(const std::wstring &str)
{	
#	if (LORD_PLATFORM == LORD_PLATFORM_WINDOWS)
	int size = WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, NULL, 0);
#	else
	size_t size = wcstombs(NULL, str.c_str(), 0);
#	endif
	
	std::string mbstr(size, wchar_t(0));
#	if (LORD_PLATFORM == LORD_PLATFORM_WINDOWS)
	WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, const_cast<char*>(mbstr.c_str()), size);
#	else
	wcstombs(const_cast<char*>(mbstr.c_str()), const_cast<wchar_t*>(str.c_str()), (size+1)*4);
#	endif
	
	return mbstr;
}

std::wstring StringUtil::MBS2WCS(const std::string &str)
{
#	if (LORD_PLATFORM == LORD_PLATFORM_WINDOWS)
	int size = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
#	else
	size_t size = mbstowcs(NULL, str.c_str(), 0);
#	endif
	
	std::wstring wstr(size, wchar_t(0));
#	if (LORD_PLATFORM == LORD_PLATFORM_WINDOWS)
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, const_cast<wchar_t*>(wstr.c_str()), size);
#	else
	mbstowcs(const_cast<wchar_t*>(wstr.c_str()), str.c_str(), (size+1)*4);
#	endif
	return wstr;
}

std::string StringUtil::ConvMBS(const std::wstring &str)
{
	return StringUtil::WCS2MBS(str);
}

std::string StringUtil::ConvMBS(const std::string &str)
{
	return str;
}

std::wstring StringUtil::ConvWCS(const std::string &str)
{
	return StringUtil::MBS2WCS(str);
}

std::wstring StringUtil::ConvWCS(const std::wstring &str)
{
	return str;
}

String StringUtil::ConvStr(const std::wstring &str)
{
#if (LORD_CHARSET == LORD_CHARSET_UNICODE)
	return str;
#else
	
#	if (LORD_PLATFORM == LORD_PLATFORM_WINDOWS)
	int size = WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, NULL, 0);
#	else
	size_t size = wcstombs(NULL, str.c_str(), 0);
#	endif
	
	std::string mbstr(size, wchar_t(0));
#	if (LORD_PLATFORM == LORD_PLATFORM_WINDOWS)
	WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, const_cast<char*>(mbstr.c_str()), size);
#	else
	wcstombs(const_cast<char*>(mbstr.c_str()), const_cast<wchar_t*>(str.c_str()), (size+1)*4);
#	endif
	
	return mbstr;
	
#endif
}

String StringUtil::ConvStr(const std::string &str)
{
#if (LORD_CHARSET == LORD_CHARSET_UNICODE)
	
#	if (LORD_PLATFORM == LORD_PLATFORM_WINDOWS)
	int size = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
#	else
	size_t size = mbstowcs(NULL, str.c_str(), 0);
#	endif
	
	std::wstring wstr(size, wchar_t(0));
#	if (LORD_PLATFORM == LORD_PLATFORM_WINDOWS)
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, const_cast<wchar_t*>(wstr.c_str()), size);
#	else
	mbstowcs(const_cast<wchar_t*>(wstr.c_str()), str.c_str(), (size+1)*4);
#	endif
	return wstr;
	
#else
	return str;
#endif
}

String StringUtil::ToString(Real val, Word precision, Word width, tchar fill)
{
	StringStream ss;
	ss.precision(precision);
	ss.width(width);
	ss.fill(fill);
	ss << val;
	return ss.str();
}

String StringUtil::ToString(int val, Word width, tchar fill)
{
	StringStream ss;
	ss.width(width);
	ss.fill(fill);
	ss << val;
	return ss.str();
}

String StringUtil::ToString(long val, Word width, tchar fill)
{
	StringStream ss;
	ss.width(width);
	ss.fill(fill);
	ss << val;
	return ss.str();
}

String StringUtil::ToString(bool val, bool bYesNo)
{
	if (val)
	{
		if (bYesNo)
			return _T("yes");
		else
			return _T("true");
	}
	else
	{
		if (bYesNo)
			return _T("no");
		else
			return _T("false");
	}
}

float StringUtil::ParseFloat(const String &val, float defaultValue)
{
	// Use istringstream for direct correspondence with to_string
	StringStream str(val);
	float ret = defaultValue;
	str >> ret;
	
	return ret;
}

double StringUtil::ParseDouble(const String &val, double defaultValue)
{
	// Use istringstream for direct correspondence with to_string
	StringStream str(val);
	double ret = defaultValue;
	str >> ret;
	
	return ret;
}

Real StringUtil::ParseReal(const String &val, Real defaultValue)
{
	// Use istringstream for direct correspondence with to_string
	StringStream str(val);
	Real ret = defaultValue;
	str >> ret;
	
	return ret;
}

int StringUtil::ParseInt(const String &val, int defaultValue)
{
	// Use istringstream for direct correspondence with to_string
	StringStream str(val);
	int ret = defaultValue;
	str >> ret;
	
	return ret;
}

long StringUtil::ParseLong(const String &val, long defaultValue)
{
	// Use istringstream for direct correspondence with to_string
	StringStream str(val);
	long ret = defaultValue;
	str >> ret;
	
	return ret;
}

bool StringUtil::ParseBool(const String &val, bool defaultValue)
{
	if (StringUtil::Equal(val, _T("true"), false) ||
		StringUtil::Equal(val, _T("yes"), false) ||
		StringUtil::Equal(val, _T("1"), false))
		return true;
	else if(StringUtil::Equal(val, _T("false"), false) ||
			StringUtil::Equal(val, _T("no"), false) ||
			StringUtil::Equal(val, _T("0"), false))
		return false;
	else
		return defaultValue;
}

Dword StringUtil::ParseDword(const String &val, Dword defaultValue /*= 0xffffffff*/)
{
	StringStream ss(val.c_str());
	Dword ret = defaultValue;
	ss >> std::hex >> ret;
	return ret;
}

bool StringUtil::IsNumber(const String &val)
{
	StringStream str(val);
	float tst;
	str >> tst;
	return !str.fail() && str.eof();
}

String StringUtil::Hex2Char(Dword val)
{
	String out;
	out.resize(4*2+1);// one byte - two characters
	
	tchar *to = (tchar*)out.c_str();
	Byte *from = (Byte*)(&val) + 3;
	
	for (int i = 0; i < 4; ++i) {
		*(to++) = _HexToChar[(*from) >> 4]; // 4 high bits.
		*(to++) = _HexToChar[(*from) & 0x0f]; // 4 low bits.
		
		--from;
	}
	
	return out;
}

LORD_NAMESPACE_END