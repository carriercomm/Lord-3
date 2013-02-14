#ifndef __LORD_MEMORY_H__
#define __LORD_MEMORY_H__

#include "MemAllocDef.h"

// Global Interface Definitions

#define LordNew(T)								LORD_NEW_T(T)
#define LordNewArray(T, count)					LORD_NEW_ARRAY_T(T, count)
#define LordDelete(ptr)							delete (ptr)
#define LordDeleteArray(ptr)					delete [](ptr)
#define LordSafeDelete(ptr)						{ if(ptr) { LordDelete(ptr); (ptr) = NULL; } }
#define LordSafeDeleteArray(ptr)				{ if(ptr) { LordDeleteArray(ptr); (ptr) = NULL; } }

#define LordNewT(T)								LORD_NEW_T(T)
#define LordNewArrayT(T, count)					LORD_NEW_ARRAY_T(T, count)
#define LordDeleteT(ptr, T)						LORD_DELETE_T(ptr, T)
#define LordDeleteArrayT(ptr, T, count)			LORD_DELETE_ARRAY_T(ptr, T, count)
#define LordSafeDeleteT(ptr, T)					{ if(ptr) { LordDeleteT(ptr, T); (ptr) = NULL; } }
#define LordSafeDeleteArrayT(ptr, T, count)		{ if(ptr) { LordDeleteArrayT(ptr, T, count); (ptr) = NULL; } }

#define LordMalloc(bytes)						LORD_MALLOC(bytes)
#define LordFree(ptr)							LORD_FREE(ptr)
#define LordSafeFree(ptr)						{ if(ptr) { LordFree(ptr); (ptr) = NULL; } }

// for COM Object
#ifdef SafeRelease
#undef SafeRelease
#endif
#define SafeRelease(ptr)						{ if(ptr) { (ptr)->Release(); (ptr) = NULL; } }

#endif