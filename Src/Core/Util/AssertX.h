#ifndef __LORD_ASSERTX_H__
#define __LORD_ASSERTX_H__

#include "StringUtil.h"

LORD_NAMESPACE_BEGIN

// Assert function return values
enum ErrRet
{
	ERRRET_IGNORE = 0,
	ERRRET_CONTINUE,
	ERRRET_BREAKPOINT,
	ERRRET_ABORT
};

//- Global functions ----------------------------------------------------------
LORD_CORE_API ErrRet NotifyAssert(const tchar *condition, const char *fileName, int lineNumber, const tchar *formats, ...);

#if (LORD_PLATFORM == LORD_PLATFORM_WINDOWS)

#define LordAssertX(x, formats, ...) { \
static bool _ignoreAssert = false; \
if (!_ignoreAssert && !(x)) \
{ \
	ErrRet _err_result = NotifyAssert(_T(#x), __FILE__, __LINE__, formats, ##__VA_ARGS__); \
	if (_err_result == ERRRET_IGNORE) \
	{ \
		_ignoreAssert = true; \
	} \
	else if (_err_result == ERRRET_BREAKPOINT) \
	{ \
		_asm{int 3}; \
	} \
}}

#else

#define LordAssertX(x, formats, ...) { \
static bool _ignoreAssert = false; \
if (!_ignoreAssert && !(x)) \
{ \
	std::string comment = StringUtil::ConvMBS(StringUtil::Format(formats, ##__VA_ARGS__)); \
	std::string msg; \
	if(!comment.empty()){ msg = "Comment:" + comment + "\n"; } \
	fprintf (stderr, "%s:%u: failed assertion `%s'\n%s", __FILE__, __LINE__, (#x), msg.c_str()); \
	__asm__("int $3"); \
	exit(-1);\
}}

#endif

#define LordAssert(x)		LordAssertX(x, _T(""))

LORD_NAMESPACE_END

#endif
