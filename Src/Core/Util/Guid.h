#ifndef __LORD_GUID_H__
#define __LORD_GUID_H__

LORD_NAMESPACE_BEGIN

class LORD_CORE_API Guid
{
public:
	struct GuidData
	{
		Dword	data1;
		Word	data2;
		Word	data3;
		Byte	data4[8];
	};
	
	Guid();
	Guid(const GuidData &guidData);
	
public:
	bool			operator == (const Guid &rhs) const;
	bool			operator != (const Guid &rhs) const;
	
public:
	void			regen();
	String			toString();
	
protected:
	GuidData		m_guidData;
};

LORD_NAMESPACE_END

#endif