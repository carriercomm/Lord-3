#ifndef __LORD_CORESTD_H__
#define __LORD_CORESTD_H__

#include "CoreDef.h"

#if (LORD_PLATFORM == LORD_PLATFORM_WINDOWS)
#	ifdef LORD_CORE_EXPORTS
#		define LORD_CORE_API __declspec(dllexport)
#	else
#		define LORD_CORE_API __declspec(dllimport)
#	endif
#else
#	define LORD_CORE_API
#endif

// STD including
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wchar.h>
#include <typeinfo>
#include <math.h>
#include <float.h>
#include <assert.h>
#include <time.h>

// STL including
#include <limits>
#include <string>
#include <vector>
#include <stack>
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <exception>

// Note - not in the original STL, but exists in SGI STL and STLport
// For gcc 4.3 see http://gcc.gnu.org/gcc-4.3/changes.html
#if (LORD_COMPILER == LORD_COMPILER_GNUC) && !defined(STLPORT)
#   if (LORD_COMPILER_VERSION >= 430)
#       include <tr1/unordered_map>
#       include <tr1/unordered_set>
#   else
#       include <ext/hash_map>
#       include <ext/hash_set>
#   endif
#elif (LORD_COMPILER == LORD_COMPILER_CLANG)
#   if defined(_LIBCPP_VERSION)
#       include <unordered_map>
#       include <unordered_set>
#   else
#       include <tr1/unordered_map>
#       include <tr1/unordered_set>
#   endif
#else
#   if ((LORD_COMPILER == LORD_COMPILER_MSVC) && !defined(STLPORT) && (LORD_COMPILER_VERSION >= 100)) // VC++ 10.0
#    	include <unordered_map>
#    	include <unordered_set>
#	else
#   	include <hash_set>
#   	include <hash_map>
#	endif
#endif

// Data Type define
#include "TypeDef.h"

#endif