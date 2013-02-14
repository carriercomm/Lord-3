#include "CoreStd.h"
#include "Util/AssertX.h"
#include "MemTracker.h"

#if (LORD_PLATFORM == LORD_PLATFORM_WINDOWS)
#	define WIN32_LEAN_AND_MEAN
#	define _CRT_SECURE_NO_WARNINGS
#	include <Windows.h>
#	include <Windowsx.h>
#	define LordOutputCString(str) ::OutputDebugStringA(str)
#	define LordOutputCString(str) ::OutputDebugStringW(str)
#else
#	define LordOutputCString(str) std::cerr << str
#	define LordOutputCString(str) std::cerr << str
#endif

LORD_NAMESPACE_BEGIN

#ifdef LORD_MEMORY_TRACKER

MemTracker& MemTracker::get()
{
	static MemTracker tracker;
	return tracker;
}

void MemTracker::_recordAlloc(void *ptr, size_t sz, unsigned int pool, 
								 const char *file, size_t ln, const char *func)
{
	const tchar *msg = _T("Double allocation with same address - this probably means you have a mismatched allocation / deallocation style.");
	LordAssertX(mAllocations.find(ptr) == mAllocations.end(), msg);

	mAllocations[ptr] = Alloc(sz, pool, file, ln, func);
	if(pool >= mAllocationsByPool.size())
		mAllocationsByPool.resize(pool+1, 0);
	mAllocationsByPool[pool] += sz;
	mTotalAllocations += sz;
}

void MemTracker::_recordDealloc(void* ptr)
{
	// deal cleanly with null pointers
	if (!ptr)
		return;

	AllocationMap::iterator i = mAllocations.find(ptr);

	const tchar *msg = _T("Unable to locate allocation unit - this probably means you have a mismatched allocation / deallocation style.");
	LordAssertX(i != mAllocations.end(), msg);
	// update category stats
	mAllocationsByPool[i->second.pool] -= i->second.bytes;
	// global stats
	mTotalAllocations -= i->second.bytes;
	mAllocations.erase(i);
}

size_t MemTracker::getTotalMemoryAllocated() const
{
	return mTotalAllocations;
}

size_t MemTracker::getMemoryAllocatedForPool(unsigned int pool) const
{
	return mAllocationsByPool[pool];
}

void MemTracker::reportLeaks()
{		
	std::stringstream os;

	if (mAllocations.empty())
	{
		os << "Lord Memory: No memory leaks." << std::endl;
	}
	else
	{			
		os << "Lord Memory: Detected memory leaks !!! " << std::endl;
		os << "Lord Memory: (" << mAllocations.size() << ") Allocation(s) with total " << mTotalAllocations << " bytes." << std::endl;
		os << "Lord Memory: Dumping allocations -> " << std::endl;


		for (AllocationMap::const_iterator i = mAllocations.begin(); i != mAllocations.end(); ++i)
		{
			const Alloc& alloc = i->second;
			if (!alloc.filename.empty())				
				os << alloc.filename;
			else
				os << "(unknown source):";

			os << "(" << alloc.line << ") : {" << alloc.bytes << " bytes}" << " function: " << alloc.function << std::endl; 				

		}			
		os << std::endl;			
	}

	if (mDumpToStdOut)		
		std::cout << os.str();		

	std::ofstream of;
	std::locale loc = std::locale::global(std::locale(""));
	of.open(mLeakFileName.c_str());
	std::locale::global(loc);
	of << os.str();
	of.close();

	LordOutputCString(os.str().c_str());
}
#endif // LORD_DEBUG_MODE

LORD_NAMESPACE_END