#ifndef __LORD_TYPEDEF_H__
#define __LORD_TYPEDEF_H__

LORD_NAMESPACE_BEGIN

typedef signed char			i8;			//!< ¨C128 to 127
typedef short				i16;		//!< ¨C32,768 to 32,767
typedef int					i32;		//!< ¨C2,147,483,648 to 2,147,483,647
typedef long long			i64;		//!< ¨C9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
typedef unsigned char		ui8;
typedef unsigned short		ui16;
typedef unsigned int		ui32;
typedef unsigned long long	ui64;

typedef unsigned int		uint;
typedef float				real32;		//!< .4E +/- 38 (7 digits)
typedef double				real64;		//!< 1.7E +/- 308 (15 digits)

typedef unsigned int		Dword;
typedef int					Bool;
typedef unsigned char		Byte;
typedef unsigned short		Word;

#if (LORD_CHARSET == LORD_CHARSET_UNICODE)

    typedef wchar_t				tchar;
#	ifndef _T
#		define _T(a)		L##a
#	endif

#else

	typedef char				tchar;
#	ifndef _T
#		define _T(a)		a
#	endif

#endif


#if (LORD_PRECISION == LORD_PREC_DOUBLE)
    typedef double			Real;
#else
    typedef float			Real;
#endif

// STL Type Define
//#if (LORD_COMPILER == LORD_COMPILER_MSVC)
//#   define HashMap ::std::tr1::unordered_map
//#   define HashSet ::std::tr1::unordered_set
//#else
//#   define HashMap ::std::tr1::unordered_map
//#   define HashSet ::std::tr1::unordered_set
//#endif

#if ((LORD_COMPILER == LORD_COMPILER_GNUC) && (LORD_COMPILER_VERSION >= 310) && !defined(STLPORT))
#   if LORD_COMPILER_VERSION >= 430
#       define HashMap ::std::tr1::unordered_map
#		define HashSet ::std::tr1::unordered_set
#    else
#       define HashMap ::__gnu_cxx::hash_map
#       define HashSet ::__gnu_cxx::hash_set
#    endif
#elif LORD_COMPILER == LORD_COMPILER_CLANG
#    if defined(_LIBCPP_VERSION)
#       define HashMap ::std::unordered_map
#       define HashSet ::std::unordered_set
#    else
#       define HashMap ::std::tr1::unordered_map
#       define HashSet ::std::tr1::unordered_set
#    endif
#else
#   if LORD_COMPILER == LORD_COMPILER_MSVC
#       if LORD_COMPILER_VERSION >= 100 // VC++ 10.0
#			define HashMap ::std::tr1::unordered_map
#           define HashSet ::std::tr1::unordered_set
#		elif LORD_COMPILER_VERSION > 70 && !defined(_STLP_MSVC)
#           define HashMap ::stdext::hash_map
#           define HashSet ::stdext::hash_set
#       else
#           define HashMap ::std::hash_map
#           define HashSet ::std::hash_set
#       endif
#   else
#       define HashMap ::std::hash_map
#       define HashSet ::std::hash_set
#   endif
#endif

#if (LORD_CHARSET == LORD_CHARSET_UNICODE)
    typedef ::std::wstring			String;
    typedef ::std::wstringstream	StringStream;
    typedef ::std::wfstream			FStream;
    typedef ::std::wifstream		IFStream;
    typedef ::std::wofstream		OFStream;
#else
    typedef ::std::string			String;
    typedef ::std::stringstream		StringStream;
    typedef ::std::fstream			FStream;
    typedef ::std::ifstream			IFStream;
    typedef ::std::ofstream			OFStream;
#endif
    typedef ::std::vector<String>		StringArray;

LORD_NAMESPACE_END

#endif
