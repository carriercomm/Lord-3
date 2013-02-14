#include "CoreStd.h"
#include "Guid.h"
#include "StringUtil.h"

#if (LORD_PLATFORM == LORD_PLATFORM_WINDOWS)
#	include <objbase.h>
#else
#	include <uuid/uuid.h>
#endif

LORD_NAMESPACE_BEGIN

Guid::Guid()
{
}

Guid::Guid(const GuidData &guidData)
{
	memcpy(&m_guidData, &guidData, sizeof(GuidData));
}

bool Guid::operator == (const Guid &rhs) const
{
	if(m_guidData.data1 != rhs.m_guidData.data1)
		return false;
	if(m_guidData.data2 != rhs.m_guidData.data2)
		return false;
	if(m_guidData.data3 != rhs.m_guidData.data3)
		return false;
	
	for(int i = 0; i < 8; ++i)
	{
		if(m_guidData.data4[i] != rhs.m_guidData.data4[i])
			return false;
	}
	
	return true;
}

bool Guid::operator != (const Guid &rhs) const
{
	return !(*this == rhs);
}

void Guid::regen()
{
#if (LORD_PLATFORM == LORD_PLATFORM_WINDOWS)
	CoCreateGuid((GUID*)&m_guidData);
#else
	uuid_generate(reinterpret_cast<Byte*>(&m_guidData));
#endif
}

String Guid::toString()
{
	return StringUtil::Format(	_T("%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X"),
								m_guidData.data1, m_guidData.data2, m_guidData.data3,
								m_guidData.data4[0], m_guidData.data4[1],
								m_guidData.data4[2], m_guidData.data4[3],
								m_guidData.data4[4], m_guidData.data4[5],
								m_guidData.data4[6], m_guidData.data4[7]);
}

LORD_NAMESPACE_END