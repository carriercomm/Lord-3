#include "CoreStd.h"
#include "MemAllocDef.h"
#include "MemAllocObj.h"

LORD_NAMESPACE_BEGIN

/*
 The problem is that operator new/delete are *implicitly* static. We have to
 instantiate them for each combination exactly once throughout all the compilation
 units that are linked together, and this appears to be the only way to do it.
 */

template class AllocatedObject<GeneralAllocPolicy>;

LORD_NAMESPACE_END