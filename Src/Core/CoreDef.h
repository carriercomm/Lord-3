#ifndef __LORD_COREDEF_H__
#define __LORD_COREDEF_H__

// Lord Engine version
#define LORD_CORE_VER 1.0

// Initial compiler-related stuff to set.
#define LORD_COMPILER_MSVC		1
#define LORD_COMPILER_CLANG		2
#define LORD_COMPILER_GNUC		3

// Initial platform stuff to set.
#define LORD_PLATFORM_WINDOWS   1
#define LORD_PLATFORM_LINUX     2
#define LODD_PLATFORM_MAC_OSX   3
#define LORD_PLATFORM_MAC_IOS   4
#define LORD_PLATFORM_ANDROID   5

// CPU Architecture
#define LORD_ARCH_32BIT         1
#define LORD_ARCH_64BIT         2

// Endian
#define LORD_ENDIAN_LITTLE      1
#define LORD_ENDIAN_BIG         2

// Charset
#define LORD_CHARSET_UNICODE    1
#define LORD_CHARSET_MULTIBYTE  2

// Precision
#define LORD_PREC_FLOAT         1
#define LORD_PREC_DOUBLE        2

// Mode
#define LORD_MODE_DEBUG         1
#define LORD_MODE_RELEASE       2

// Memory Allocator
#define LORD_MEMORY_ALLOCATOR_NED           1
#define LORD_MEMORY_ALLOCATOR_NEDPOOLING    2

// Compiler type and version recognition
#if defined( _MSC_VER )
#   define LORD_COMPILER            LORD_COMPILER_MSVC
#	if _MSC_VER >= 1700
#		define LORD_COMPILER_VERSION 110
#	elif _MSC_VER >= 1600
#		define LORD_COMPILER_VERSION 100
#	elif _MSC_VER >= 1500
#		define LORD_COMPILER_VERSION 90
#	elif _MSC_VER >= 1400
#		define LORD_COMPILER_VERSION 80
#	elif _MSC_VER >= 1300
#		define LORD_COMPILER_VERSION 70
#	endif
#elif defined( __clang__ )
#   define LORD_COMPILER			LORD_COMPILER_CLANG
#   define LORD_COMPILER_VERSION	(((__clang_major__)*100) + \
(__clang_minor__*10) + \
__clang_patchlevel__)
#elif defined( __GNUC__ )
#   define LORD_COMPILER            LORD_COMPILER_GNUC
#   define LORD_COMPILER_VERSION    (((__GNUC__)*100) + \
(__GNUC_MINOR__*10) + \
__GNUC_PATCHLEVEL__)
#else
#   pragma error "Unknown compiler. Abort! Abort!"
#endif

// Platform recognition
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#	define LORD_PLATFORM    LORD_PLATFORM_WINDOWS
#elif defined(_WIN64) || defined(__WIN64__) || defined(WIN64)
#	define LORD_PLATFORM    LORD_PLATFORM_WINDOWS
#elif defined(linux) || defined(__linux) || defined(__linux__)
#	define LORD_PLATFORM_LINUX
#elif defined( __APPLE_CC__)
// Device                                                     Simulator
// Both requiring OS version 4.0 or greater
#   if __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ >= 40000 || __IPHONE_OS_VERSION_MIN_REQUIRED >= 40000
#       define LORD_PLATFORM        LORD_PLATFORM_MAC_IOS
#   else
#       define LORD_PLATFORM        LORD_PLATFORM_MAC_OSX
#   endif
#elif defined(__ANDROID__)
#	define LORD_PLATFORM    LORD_PLATFORM_ANDROID
#else
#	error Couldn't recognize platform
#endif

// CPU architechture type recognition
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
#	define LORD_ARCHITECTURE         LORD_ARCH_64BIT
#else
#	define LORD_ARCHITECTURE         LORD_ARCH_32BIT
#endif

// Disable MSVC warning
#if (LORD_COMPILER == LORD_COMPILER_MSVC)
#	pragma warning(disable: 4251 4275 4819)
#	ifndef _CRT_SECURE_NO_DEPRECATE
#		define _CRT_SECURE_NO_DEPRECATE
#	endif
#	ifndef _SCL_SECURE_NO_DEPRECATE
#		define _SCL_SECURE_NO_DEPRECATE
#	endif
#endif

// Endian Settings
static union { char c[4]; unsigned long nVar; } _LordEndian = {{ 'L', '?', '?', 'B' } };
static const int _LordEndianFlag = ((char)_LordEndian.nVar == 'L'? LORD_ENDIAN_LITTLE : LORD_ENDIAN_BIG);
#define LORD_ENDIAN     _LordEndianFlag

// Charset Settings
#if defined(_UNICODE) || defined(UNICODE)
#	define LORD_CHARSET     LORD_CHARSET_UNICODE
#else
#	define LORD_CHARSET     LORD_CHARSET_MULTIBYTE
#endif

// Asserts expression is true at compile-time
#define LORD_COMPILER_ASSERT(x)	typedef int COMPILER_ASSERT_[!!(x)]

// Precision define
#define LORD_PRECISION      LORD_PREC_FLOAT
//#define LORD_PRECISION    LORD_PREC_DOUBLE

// mode
#if defined(_DEBUG) || defined(DEBUG)
#	define LORD_MODE        LORD_MODE_DEBUG
#else
#	define LORD_MODE        LORD_MODE_RELEASE
#endif

// Namespace define
#define LORD_NAMESPACE_BEGIN	namespace LORD {
#define LORD_NAMESPACE_END		}
#define USING_LORD_NAMESPACE	using namespace LORD;


#define LORD_ALIGN16 __declspec(align(16))
#define LORD_SIMD_ALIGNMENT 16

// Lord Engine Memory Managed
#if (LORD_MODE == LORD_MODE_DEBUG)
#define LORD_MEMORY_TRACKER
#endif

// Lord memory allocator
//#define LORD_MEMORY_ALLOCATOR   LORD_MEMORY_ALLOCATOR_NED
#define LORD_MEMORY_ALLOCATOR   LORD_MEMORY_ALLOCATOR_NEDPOOLING

// Log
#define LORD_LOG_FILENAME			"Lord.log"
#define LORD_MEMORY_LEAKS_FILENAME	"MemoryLeaks.log"

#endif