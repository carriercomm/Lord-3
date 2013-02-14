#ifndef __LORD_MEMNEDPOOLING_H__
#define __LORD_MEMNEDPOOLING_H__

#ifdef LORD_MEMORY_ALLOCATOR_NEDPOOLING

#include "MemTracker.h"

LORD_NAMESPACE_BEGIN

//Non-templated utility class just to hide nedmalloc.
class LORD_CORE_API NedPoolingImpl
{
public:
	static void*	allocBytes(size_t count, const char *file, int line, const char *func);
	static void		deallocBytes(void *ptr);
	static void*	allocBytesAligned(size_t align, size_t count, const char *file, int line, const char *func);
	static void		deallocBytesAligned(size_t align, void *ptr);
};

/**	An allocation policy for use with AllocatedObject and
 STLAllocator. This is the class that actually does the allocation
 and deallocation of physical memory, and is what you will want to
 provide a custom version of if you wish to change how memory is allocated.
 @par
 This allocation policy uses nedmalloc (http://nedprod.com/programs/portable/nedmalloc/index.html).
 */
class LORD_CORE_API NedPoolingPolicy
{
public:
	static inline void* allocateBytes(size_t count, const char *file = NULL, int line = 0, const char *func = NULL)
	{
		return NedPoolingImpl::allocBytes(count, file, line, func);
	}
	static inline void deallocateBytes(void *ptr)
	{
		NedPoolingImpl::deallocBytes(ptr);
	}
	// Get the maximum size of a single allocation
	static inline size_t getMaxAllocationSize()
	{
		return (std::numeric_limits<size_t>::max)();
	}
	
private:
	// No instantiation
	NedPoolingPolicy()
	{
	}
};

/**	An allocation policy for use with AllocatedObject and
 STLAllocator, which aligns memory at a given boundary (which should be
 a power of 2). This is the class that actually does the allocation
 and deallocation of physical memory, and is what you will want to
 provide a custom version of if you wish to change how memory is allocated.
 @par
 This allocation policy uses nedmalloc (http://nedprod.com/programs/portable/nedmalloc/index.html).
 @note
 template parameter Alignment equal to zero means use default
 platform dependent alignment.
 */
template <size_t Alignment = 0>
class NedPoolingAlignedPolicy
{
public:
	// compile-time check alignment is available.
	typedef int IsValidAlignment[Alignment <= 128 && ((Alignment & (Alignment-1)) == 0) ? +1 : -1];
	
	static inline void* allocateBytes(size_t count, const char *file = NULL, int line = 0, const char *func = NULL)
	{
		return NedPoolingImpl::allocBytesAligned(Alignment, count, file, line, func);
	}
	
	static inline void deallocateBytes(void *ptr)
	{
		NedPoolingImpl::deallocBytesAligned(Alignment, ptr);
	}
	
	// Get the maximum size of a single allocation
	static inline size_t getMaxAllocationSize()
	{
		return (std::numeric_limits<size_t>::max)();
	}
private:
	// no instantiation allowed
	NedPoolingAlignedPolicy()
	{
	}
};

LORD_NAMESPACE_END

#endif // end - #ifdef LORD_MEMORY_ALLOCATOR_NEDPOOLING

#endif