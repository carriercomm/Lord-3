#ifndef __LORD_MEMTRACKER_H__
#define __LORD_MEMTRACKER_H__

LORD_NAMESPACE_BEGIN

#ifdef LORD_MEMORY_TRACKER

/** This class tracks the allocations and deallocations made, and
	is able to report memory statistics and leaks.
@note
	This class is only available in debug builds.
*/
class LORD_CORE_API MemTracker
{
protected:
	// Allocation record
	struct Alloc
	{
		size_t bytes;
		unsigned int pool;
		std::string filename;
		size_t line;
		std::string function;

		Alloc():bytes(0), line(0){}
		Alloc(size_t sz, unsigned int p, const char *file, size_t ln, const char *func):
		bytes(sz), 
		pool(p), 
		line(ln)
		{
			if (file)
				filename = file;
			if (func)
				function = func;
		}
	};

	std::string mLeakFileName;
	bool mDumpToStdOut;
	typedef HashMap<void*, Alloc> AllocationMap;
	AllocationMap mAllocations;

	size_t mTotalAllocations;
	typedef std::vector<size_t> AllocationsByPool;
	AllocationsByPool mAllocationsByPool;

	void reportLeaks();

	// protected ctor
	MemTracker():
	mLeakFileName(LORD_MEMORY_LEAKS_FILENAME),
	mDumpToStdOut(false),
	mTotalAllocations(0)
	{
	}
public:

	/** Set the name of the report file that will be produced on exit. */
	void setReportFileName(const std::string &name)
	{
		mLeakFileName = name;
	}
	// Return the name of the file which will contain the report at exit
	const std::string& getReportFileName() const
	{
		return mLeakFileName;
	}
	// Sets whether the memory report should be sent to stdout
	void setReportToStdOut(bool rep)
	{
		mDumpToStdOut = rep;
	}
	// Gets whether the memory report should be sent to stdout
	bool getReportToStdOut() const
	{
		return mDumpToStdOut;
	}

	// Get the total amount of memory allocated currently.
	size_t getTotalMemoryAllocated() const;
	// Get the amount of memory allocated in a given pool
	size_t getMemoryAllocatedForPool(unsigned int pool) const;


	/** Record an allocation that has been made. Only to be called by
		the memory management subsystem.
		@param ptr The pointer to the memory
		@param sz The size of the memory in bytes
		@param pool The memory pool this allocation is occurring from
		@param file The file in which the allocation is being made
		@param ln The line on which the allocation is being made
		@param func The function in which the allocation is being made
	*/
	void _recordAlloc(void *ptr, size_t sz, unsigned int pool = 0,
					  const char *file = NULL, size_t ln = 0, const char *func = NULL);
	// Record the deallocation of memory.
	void _recordDealloc(void *ptr);

	~MemTracker()
	{
		reportLeaks();
	}

	// Static utility method to get the memory tracker instance
	static MemTracker& get();

};

#endif

LORD_NAMESPACE_END

#endif