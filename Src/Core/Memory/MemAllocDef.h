#ifndef __LORD_MEMALLOCDEF_H__
#define __LORD_MEMALLOCDEF_H__

#include "MemAllocObj.h"
#include "MemNedPooling.h"


LORD_NAMESPACE_BEGIN

#if (LORD_MEMORY_ALLOCATOR == LORD_MEMORY_ALLOCATOR_NEDPOOLING)

// configure default allocators based on the options above
// notice how we're not using the memory categories here but still roughing them out
// in your allocators you might choose to create different policies per category

// configurable category, for general malloc
// notice how we ignore the category here, you could specialize
class CategorisedAllocPolicy : public NedPoolingPolicy{};
template <size_t align = 16> class CategorisedAlignAllocPolicy : public NedPoolingAlignedPolicy<align>{};
#endif

#if (LORD_MEMORY_ALLOCATOR == LORD_MEMORY_ALLOCATOR_NED)

// configure default allocators based on the options above
// notice how we're not using the memory categories here but still roughing them out
// in your allocators you might choose to create different policies per category

// configurable category, for general malloc
// notice how we ignore the category here, you could specialize
class CategorisedAllocPolicy : public NedAllocPolicy{};
template <size_t align = 16> class CategorisedAlignAllocPolicy : public NedAlignedAllocPolicy<align>{};

#endif


// Useful shortcuts
//typedef CategorisedAllocPolicy<MEMCATEGORY_OBJECT> GeneralAllocPolicy;
typedef CategorisedAlignAllocPolicy<16> GeneralAllocPolicy;


// Now define all the base classes for each allocation
typedef AllocatedObject<GeneralAllocPolicy> GeneralAllocatedObject;

// Per-class allocators defined here
// NOTE: small, non-virtual classes should not subclass an allocator
// the virtual function table could double their size and make them less efficient
// use primitive or STL allocators / deallocators for those
typedef GeneralAllocatedObject		ObjectAlloc;

// Containers (by-value only)
// Will  be of the form:
// typedef STLAllocator<T, DefaultAllocPolicy, Category> TAlloc;
// for use in vector<T, TAlloc>::type 

//////////////////////////////////////////////////////////////////////////

/** Utility function for constructing an array of objects with placement new,
	without using new[] (which allocates an undocumented amount of extra memory
	and so isn't appropriate for custom allocators).
*/
template<typename T>
T* LordConstruct(T* basePtr, size_t count)
{
	for (size_t i = 0; i < count; ++i)
	{
		new ((void*)(basePtr+i)) T();
	}
	return basePtr;
}

LORD_NAMESPACE_END

#if (LORD_MODE == LORD_MODE_DEBUG)

/// Allocate a block of raw memory.
#	define LORD_MALLOC(bytes) ::LORD::CategorisedAllocPolicy::allocateBytes(bytes, __FILE__, __LINE__, __FUNCTION__)
/// Allocate a block of memory for a primitive type.
#	define LORD_ALLOC_T(T, count) static_cast<T*>(::LORD::CategorisedAllocPolicy::allocateBytes(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__))
/// Free the memory allocated with LORD_MALLOC or LORD_ALLOC_T.
#	define LORD_FREE(ptr) ::LORD::CategorisedAllocPolicy::deallocateBytes((void*)ptr)

/// Allocate space for one primitive type, external type or non-virtual type with constructor parameters
#	define LORD_NEW_T(T) new (::LORD::CategorisedAllocPolicy::allocateBytes(sizeof(T), __FILE__, __LINE__, __FUNCTION__)) T
/// Allocate a block of memory for 'count' primitive types - do not use for classes that inherit from AllocatedObject
#	define LORD_NEW_ARRAY_T(T, count) ::LORD::LordConstruct(static_cast<T*>(::LORD::CategorisedAllocPolicy::allocateBytes(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__)), count) 
/// Free the memory allocated with LORD_NEW_T.
#	define LORD_DELETE_T(ptr, T) if(ptr){(ptr)->~T(); ::LORD::CategorisedAllocPolicy::deallocateBytes((void*)ptr);}
/// Free the memory allocated with LOR_NEW_ARRAY_T.
#	define LORD_DELETE_ARRAY_T(ptr, T, count) if(ptr){for (size_t b = 0; b < count; ++b) { (ptr)[b].~T();} ::LORD::CategorisedAllocPolicy::deallocateBytes((void*)ptr);}

// aligned allocation
/// Allocate a block of raw memory aligned to SIMD boundaries.
#	define LORD_MALLOC_SIMD(bytes) ::LORD::CategorisedAlignAllocPolicy::allocateBytes(bytes, __FILE__, __LINE__, __FUNCTION__)
/// Allocate a block of raw memory aligned to user defined boundaries.
#	define LORD_MALLOC_ALIGN(bytes, align) ::LORD::CategorisedAlignAllocPolicy<align>::allocateBytes(bytes, __FILE__, __LINE__, __FUNCTION__)
/// Allocate a block of memory for a primitive type aligned to SIMD boundaries.
#	define LORD_ALLOC_T_SIMD(T, count) static_cast<T*>(::LORD::CategorisedAlignAllocPolicy::allocateBytes(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__))
/// Allocate a block of memory for a primitive type aligned to user defined boundaries.
#	define LORD_ALLOC_T_ALIGN(T, count, align) static_cast<T*>(::LORD::CategorisedAlignAllocPolicy<align>::allocateBytes(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__))
/// Free the memory allocated with either LORD_MALLOC_SIMD or LORD_ALLOC_T_SIMD.
#	define LORD_FREE_SIMD(ptr) ::LORD::CategorisedAlignAllocPolicy::deallocateBytes(ptr)
/// Free the memory allocated with either LORD_MALLOC_ALIGN or LORD_ALLOC_T_ALIGN.
#	define LORD_FREE_ALIGN(ptr, align) ::LORD::CategorisedAlignAllocPolicy<align>::deallocateBytes(ptr)

/// Allocate space for one primitive type, external type or non-virtual type aligned to SIMD boundaries
#	define LORD_NEW_T_SIMD(T) new (::LORD::CategorisedAlignAllocPolicy::allocateBytes(sizeof(T), __FILE__, __LINE__, __FUNCTION__)) T
/// Allocate a block of memory for 'count' primitive types aligned to SIMD boundaries - do not use for classes that inherit from AllocatedObject
#	define LORD_NEW_ARRAY_T_SIMD(T, count) ::LORD::LordConstruct(static_cast<T*>(::LORD::CategorisedAlignAllocPolicy::allocateBytes(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__)), count) 
/// Free the memory allocated with LOR_NEW_T_SIMD.
#	define LORD_DELETE_T_SIMD(ptr, T) if(ptr){(ptr)->~T(); ::LORD::CategorisedAlignAllocPolicy::deallocateBytes(ptr);}
/// Free the memory allocated with LORD_NEW_ARRAY_T_SIMD.
#	define LORD_DELETE_ARRAY_T_SIMD(ptr, T, count) if(ptr){for (size_t b = 0; b < count; ++b) { (ptr)[b].~T();} ::LORD::CategorisedAlignAllocPolicy::deallocateBytes(ptr);}
/// Allocate space for one primitive type, external type or non-virtual type aligned to user defined boundaries
#	define LORD_NEW_T_ALIGN(T, align) new (::LORD::CategorisedAlignAllocPolicy<align>::allocateBytes(sizeof(T), __FILE__, __LINE__, __FUNCTION__)) T
/// Allocate a block of memory for 'count' primitive types aligned to user defined boundaries - do not use for classes that inherit from AllocatedObject
#	define LORD_NEW_ARRAY_T_ALIGN(T, count, align) ::LORD::LordConstruct(static_cast<T*>(::LORD::CategorisedAlignAllocPolicy<align>::allocateBytes(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__)), count) 
/// Free the memory allocated with LORD_NEW_T_ALIGN.
#	define LORD_DELETE_T_ALIGN(ptr, T, align) if(ptr){(ptr)->~T(); ::LORD::CategorisedAlignAllocPolicy<align>::deallocateBytes(ptr);}
/// Free the memory allocated with LORD_NEW_ARRAY_T_ALIGN.
#	define LORD_DELETE_ARRAY_T_ALIGN(ptr, T, count, align) if(ptr){for (size_t _b = 0; _b < count; ++_b) { (ptr)[_b].~T();} ::LORD::CategorisedAlignAllocPolicy<align>::deallocateBytes(ptr);}

// new / delete for classes deriving from AllocatedObject (alignment determined by per-class policy)
// Also hooks up the file/line/function params
// Can only be used with classes that derive from AllocatedObject since customized new/delete needed
#	define LORD_NEW new (__FILE__, __LINE__, __FUNCTION__)
#	define LORD_DELETE delete


#else // else - #ifdef LORD_RUNMODE_DEBUG

/// Allocate a block of raw memory.
#	define LORD_MALLOC(bytes) ::LORD::CategorisedAllocPolicy::allocateBytes(bytes)
/// Allocate a block of memory for a primitive type.
#	define LORD_ALLOC_T(T, count) static_cast<T*>(::LORD::CategorisedAllocPolicy::allocateBytes(sizeof(T)*(count)))
/// Free the memory allocated with LORD_MALLOC or LORD_ALLOC_T. Category is required to be restated to ensure the matching policy is used
#	define LORD_FREE(ptr) ::LORD::CategorisedAllocPolicy::deallocateBytes((void*)ptr)

/// Allocate space for one primitive type, external type or non-virtual type with constructor parameters
#	define LORD_NEW_T(T) new (::LORD::CategorisedAllocPolicy::allocateBytes(sizeof(T))) T
/// Allocate a block of memory for 'count' primitive types - do not use for classes that inherit from AllocatedObject
#	define LORD_NEW_ARRAY_T(T, count) ::LORD::LordConstruct(static_cast<T*>(::LORD::CategorisedAllocPolicy::allocateBytes(sizeof(T)*(count))), count) 
/// Free the memory allocated with LORD_NEW_T.
#	define LORD_DELETE_T(ptr, T) if(ptr){(ptr)->~T(); ::LORD::CategorisedAllocPolicy::deallocateBytes((void*)ptr);}
/// Free the memory allocated with LORD_NEW_ARRAY_T.
#	define LORD_DELETE_ARRAY_T(ptr, T, count) if(ptr){for (size_t b = 0; b < count; ++b) { (ptr)[b].~T();} ::LORD::CategorisedAllocPolicy::deallocateBytes((void*)ptr);}

// aligned allocation
/// Allocate a block of raw memory aligned to SIMD boundaries.
#	define LORD_MALLOC_SIMD(bytes) ::LORD::CategorisedAlignAllocPolicy::allocateBytes(bytes)
/// Allocate a block of raw memory aligned to user defined boundaries.
#	define LORD_MALLOC_ALIGN(bytes, align) ::LORD::CategorisedAlignAllocPolicy<align>::allocateBytes(bytes)
/// Allocate a block of memory for a primitive type aligned to SIMD boundaries.
#	define LORD_ALLOC_T_SIMD(T, count) static_cast<T*>(::LORD::CategorisedAlignAllocPolicy::allocateBytes(sizeof(T)*(count)))
/// Allocate a block of memory for a primitive type aligned to user defined boundaries.
#	define LORD_ALLOC_T_ALIGN(T, count, align) static_cast<T*>(::LORD::CategorisedAlignAllocPolicy<align>::allocateBytes(sizeof(T)*(count)))
/// Free the memory allocated with either LORD_MALLOC_SIMD or LORD_ALLOC_T_SIMD.
#	define LORD_FREE_SIMD(ptr) ::LORD::CategorisedAlignAllocPolicy::deallocateBytes((void*)ptr)
/// Free the memory allocated with either LORD_MALLOC_ALIGN or LORD_ALLOC_T_ALIGN.
#	define LORD_FREE_ALIGN(ptr, align) ::LORD::CategorisedAlignAllocPolicy<align>::deallocateBytes((void*)ptr)

/// Allocate space for one primitive type, external type or non-virtual type aligned to SIMD boundaries
#	define LORD_NEW_T_SIMD(T) new (::LORD::CategorisedAlignAllocPolicy::allocateBytes(sizeof(T))) T
/// Allocate a block of memory for 'count' primitive types aligned to SIMD boundaries - do not use for classes that inherit from AllocatedObject
#	define LORD_NEW_ARRAY_T_SIMD(T, count) ::LORD::LordConstruct(static_cast<T*>(::LORD::CategorisedAlignAllocPolicy::allocateBytes(sizeof(T)*(count))), count) 
/// Free the memory allocated with LORD_NEW_T_SIMD.
#	define LORD_DELETE_T_SIMD(ptr, T) if(ptr){(ptr)->~T(); ::LORD::CategorisedAlignAllocPolicy::deallocateBytes((void*)ptr);}
/// Free the memory allocated with LORD_NEW_ARRAY_T_SIMD.
#	define LORD_DELETE_ARRAY_T_SIMD(ptr, T, count) if(ptr){for (size_t b = 0; b < count; ++b) { (ptr)[b].~T();} ::LORD::CategorisedAlignAllocPolicy::deallocateBytes((void*)ptr);}
/// Allocate space for one primitive type, external type or non-virtual type aligned to user defined boundaries
#	define LORD_NEW_T_ALIGN(T, align) new (::LORD::CategorisedAlignAllocPolicy<align>::allocateBytes(sizeof(T))) T
/// Allocate a block of memory for 'count' primitive types aligned to user defined boundaries - do not use for classes that inherit from AllocatedObject
#	define LORD_NEW_ARRAY_T_ALIGN(T, count, align) ::LORD::LordConstruct(static_cast<T*>(::LORD::CategorisedAlignAllocPolicy<align>::allocateBytes(sizeof(T)*(count))), count) 
/// Free the memory allocated with LORD_NEW_T_ALIGN.
#	define LORD_DELETE_T_ALIGN(ptr, T, align) if(ptr){(ptr)->~T(); ::LORD::CategorisedAlignAllocPolicy<align>::deallocateBytes((void*)ptr);}
/// Free the memory allocated with LORD_NEW_ARRAY_T_ALIGN.
#	define LORD_DELETE_ARRAY_T_ALIGN(ptr, T, count, align) if(ptr){for (size_t _b = 0; _b < count; ++_b) { (ptr)[_b].~T();} ::LORD::CategorisedAlignAllocPolicy<align>::deallocateBytes((void*)ptr);}

// new / delete for classes deriving from AllocatedObject (alignment determined by per-class policy)
#	define LORD_NEW new 
#	define LORD_DELETE delete

#endif // end - #ifdef LORD_RUNMODE_DEBUG

LORD_NAMESPACE_BEGIN

/** Function which invokes OGRE_DELETE on a given pointer. 
@remarks
	Useful to pass custom deletion policies to external libraries (e. g. boost).
*/
template<typename T>
void deletePtr(T* ptr)
{
	LORD_DELETE ptr;
}

LORD_NAMESPACE_END

#endif