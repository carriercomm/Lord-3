inline 
VEC4::VEC4()
{
	// do nothing
}

inline 
VEC4::VEC4(const Real x, const Real y, const Real z, const Real w)
{
	set(x, y, z, w);
}

inline 
VEC4::VEC4(const Real value)
{
	set(value);
}

inline 
VEC4::VEC4(const VEC3 &vec3, Real w)
{
	set(vec3.x, vec3.y, vec3.z, w);
}

inline 
VEC4::VEC4(const VEC4 &vec)
{
	set(vec.x, vec.y, vec.z, vec.w);
}

inline 
VEC4::operator VEC2 ()
{
	return VEC2(x, y);
}

inline 
VEC4::operator const VEC2 () const
{
	return VEC2(x, y);
}

inline 
VEC4::operator VEC3 ()
{
	return VEC3(x, y, z);
}

inline 
VEC4::operator const VEC3 () const
{
	return VEC3(x, y, z);
}

inline 
VEC4& VEC4::operator = (const VEC4 &rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	w = rhs.w;

	return *this;
}

inline 
VEC4& VEC4::operator = (const Real value)
{
	set(value);
	return *this;
}

inline 
	VEC4& VEC4::operator += (const VEC4 &rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
	return *this;
}

inline 
VEC4& VEC4::operator += (const Real value)
{
	x += value;
	y += value;
	z += value;
	w += value;
	return *this;
}

inline 
VEC4& VEC4::operator -= (const VEC4 &rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;

	return *this;
}

inline 
VEC4& VEC4::operator -= (const Real value)
{
	x -= value;
	y -= value;
	z -= value;
	w -= value;

	return *this;
}

inline 
VEC4& VEC4::operator *= (const VEC4 &rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	w *= rhs.w;

	return *this;
}

inline 
VEC4& VEC4::operator *= (const Real value)
{
	x *= value;
	y *= value;
	z *= value;
	w *= value;

	return *this;
}

inline 
VEC4& VEC4::operator /= (const VEC4 &rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	w /= rhs.w;

	return *this;
}

inline 
VEC4&  VEC4::operator /= (const Real value)
{
	x /= value;
	y /= value;
	z /= value;
	w /= value;

	return *this;
}

inline 
Real& VEC4::operator [] (int index)
{
	LordAssertX(index >= 0 && index < 4, _T("Access out of bounds"));
	return m[index];
}

inline 
const Real& VEC4::operator [] (int index) const
{
	LordAssertX(index >= 0 && index < 4, _T("Access out of bounds"));
	return m[index];
}

inline 
Real* VEC4::ptr()
{
	return &x;
}

inline 
const Real* VEC4::ptr() const
{
	return &x;
}

inline 
void VEC4::zero()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
	w = 0.0;
}

inline 
void VEC4::invalid()
{
	*this = INVALID;
}

inline 
void VEC4::set(Real x, Real y, Real z, Real w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

inline 
void VEC4::set(Real value)
{
	this->x = value;
	this->y = value;
	this->z = value;
	this->w = value;
}

inline 
void VEC4::set(Real *p)
{
	this->x = p[0];
	this->y = p[1];
	this->z = p[2];
	this->w = p[3];
}

inline 
void VEC4::setVec3(const VEC3 &vec3, Real w)
{
	x = vec3.x;
	y = vec3.y;
	z = vec3.z;
	w = w;
}

inline 
VEC3 VEC4::getVec3()
{
	return VEC3(x, y, z);
}

inline 
Real VEC4::dot(const VEC4 &rhs) const
{
	return (x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w);
}

inline 
void VEC4::inverse()
{
	x = 1.0f / x;
	y = 1.0f / y;
	z = 1.0f / z;
	w = 1.0f / w;
}

inline 
void VEC4::sqrt()
{
	x = Math::Sqrt(x);
	y = Math::Sqrt(y);
	z = Math::Sqrt(z);
	w = Math::Sqrt(w);
}

inline 
void VEC4::invSqrt()
{
	x = 1.0f / Math::Sqrt(x);
	y = 1.0f / Math::Sqrt(y);
	z = 1.0f / Math::Sqrt(z);
	w = 1.0f / Math::Sqrt(w);
}

inline 
Real VEC4::len() const
{
	Real vecLen;

	Real sum = x * x + y * y + z * z + w * w;
	vecLen = Math::Sqrt(sum);

	return vecLen;
}

inline 
Real VEC4::lenSqr() const
{
	return x * x + y * y + z * z + w * w;
}

inline 
void VEC4::normalize()
{
	Real length = len();
	x /= length;
	y /= length;
	z /= length;
	w /= length;
}

inline 
Real VEC4::normalizeLen()
{
	Real length = len();
	x /= length;
	y /= length;
	z /= length;
	w /= length;

	return length;
}

inline 
VEC4& VEC4::abs()
{
	x = Math::Abs(x);
	y = Math::Abs(y);
	z = Math::Abs(z);
	w = Math::Abs(w);

	return *this;
}

inline 
VEC4& VEC4::neg()
{
	x = -x;
	y = -y;
	z = -z;
	w = -w;

	return *this;
}

inline 
VEC4& VEC4::saturate()
{
	if ( x > 1.0 ) x = 1.0;
	if ( y > 1.0 ) y = 1.0;
	if ( z > 1.0 ) z = 1.0;
	if ( w > 1.0 ) w = 1.0;

	if ( x < 0.0 ) x = 0.0;
	if ( y < 0.0 ) y = 0.0;
	if ( z < 0.0 ) z = 0.0;
	if ( w < 0.0 ) w = 0.0;

	return *this;
}

inline 
VEC4& VEC4::clampZero()
{
	if ( x < 0.0 ) x = 0.0;
	if ( y < 0.0 ) y = 0.0;
	if ( z < 0.0 ) z = 0.0;
	if ( w < 0.0 ) w = 0.0;

	return *this;
}

inline 
VEC4& VEC4::clampOne()
{
	if ( x > 1.0 ) x = 1.0;
	if ( y > 1.0 ) y = 1.0;
	if ( z > 1.0 ) z = 1.0;
	if ( w > 1.0 ) w = 1.0;

	return *this;
}

inline 
VEC4& VEC4::floor()
{
	x = Math::Floor(x);
	y = Math::Floor(y);
	z = Math::Floor(z);
	w = Math::Floor(w);

	return *this;
}

inline 
VEC4& VEC4::ceil()
{
	x = Math::Ceil(x);
	y = Math::Ceil(y);
	z = Math::Ceil(z);
	w = Math::Ceil(w);

	return *this;
}

inline 
VEC4 VEC4::midPoint(const VEC4& vec) const
{
	return VEC4((x + vec.x) * 0.5f, (y + vec.y) * 0.5f, (z + vec.z) * 0.5f, 1.0);
}

inline 
void VEC4::makeFloor(const VEC4 &cmp)
{
	if( cmp.x < x ) x = cmp.x;
	if( cmp.y < y ) y = cmp.y;
	if( cmp.z < z ) z = cmp.z;
	if( cmp.w < w ) w = cmp.w;
}

inline 
void VEC4::makeCeil(const VEC4 &cmp)
{
	if( cmp.x > x ) x = cmp.x;
	if( cmp.y > y ) y = cmp.y;
	if( cmp.z > z ) z = cmp.z;
	if( cmp.w > w ) w = cmp.w;
}

inline 
bool VEC4::isInvalid() const
{
	return Math::IsInvalid(x) || Math::IsInvalid(y) || Math::IsInvalid(z) || Math::IsInvalid(w);
}

inline 
Real VEC4::Dot(const VEC4 &a, const VEC4 &b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

inline 
void VEC4::Lerp(VEC4 &outVec, const VEC4 &a, const VEC4 &b, const Real t)
{
	outVec = a + (b - a) * t;
}

inline 
void VEC4::Max(VEC4 &outVec, const VEC4 &a, const VEC4 &b)
{
	outVec.x = a.x > b.x ? a.x : b.x;
	outVec.y = a.y > b.y ? a.y : b.y;
	outVec.z = a.z > b.z ? a.z : b.z;
	outVec.w = a.w > b.w ? a.w : b.w;
}

inline 
void VEC4::Min(VEC4 &outVec, const VEC4 &a, const VEC4 &b)
{
	outVec.x = a.x < b.x ? a.x : b.x;
	outVec.y = a.y < b.y ? a.y : b.y;
	outVec.z = a.z < b.z ? a.z : b.z;
	outVec.w = a.w < b.w ? a.w : b.w;
}

inline 
void VEC4::Inverse(VEC4 &outVec, const VEC4 &a)
{
	outVec = a;
	outVec.inverse();
}

inline 
void VEC4::Sqrt(VEC4 &outVec, const VEC4 &a)
{
	outVec = a;
	outVec.sqrt();
}

inline 
void VEC4::InvSqrt(VEC4 &outVec, const VEC4 &a)
{
	outVec = a;
	outVec.invSqrt();
}

inline 
void VEC4::Normalize(VEC4 &outVec, const VEC4 &a)
{
	outVec = a;
	outVec.normalize();
}

inline 
Real VEC4::NormalizeLen(VEC4 &outVec, const VEC4 &a)
{
	outVec = a;
	Real vecLen = outVec.normalizeLen();
	return vecLen;
}

inline 
void VEC4::Abs(VEC4 &outVec, const VEC4 &a)
{
	outVec = a;
	outVec.abs();
}

inline 
void VEC4::Neg(VEC4 &outVec, const VEC4 &a)
{
	outVec = a;
	outVec.neg();
}

inline 
void VEC4::Saturate(VEC4 &outVec, const VEC4 &a)
{
	outVec= a;
	outVec.saturate();
}

inline 
const VEC4 operator + (const VEC4 &rhs)
{
	return rhs;
}

inline 
const VEC4 operator - (const VEC4 &rhs)
{
	return VEC4(-rhs.x, -rhs.y, -rhs.z, -rhs.w);
}

inline 
bool operator == (const VEC4 &a, const VEC4 &b)
{
	return (a.x==b.x && a.y==b.y && a.z==b.z && a.w==b.w);
}

inline 
bool operator != (const VEC4 &a, const VEC4 &b)
{
	return !(a.x==b.x && a.y==b.y && a.z==b.z && a.w==b.w);
}

inline 
const VEC4 operator + (const VEC4 &a, const VEC4 &b)
{
	VEC4 c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	c.w = a.w + b.w;

	return c;
}

inline 
const VEC4 operator - (const VEC4 &a, const VEC4 &b)
{
	VEC4 c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	c.w = a.w - b.w;

	return c;
}

inline 
const VEC4 operator * (const Real f, const VEC4 &v)
{
	VEC4 result;

	result.x = f * v.x;
	result.y = f * v.y;
	result.z = f * v.z;
	result.w = f * v.w;

	return result;
}

inline 
const VEC4 operator * (const VEC4 &v, const Real f)
{
	VEC4 result;

	result.x = f * v.x;
	result.y = f * v.y;
	result.z = f * v.z;
	result.w = f * v.w;

	return result;
}

inline 
const VEC4 operator * (const VEC4 a, const VEC4 &b)
{
	return VEC4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

inline 
const VEC4 operator / (const VEC4 &a, const Real f)
{
	VEC4 c;

	c.x = a.x / f;
	c.y = a.y / f;
	c.z = a.z / f;
	c.w = a.w / f;

	return c;
}

inline 
const VEC4 operator / (const Real f, const VEC4 &a)
{
	VEC4 c;

	c.x = f / a.x;
	c.y = f / a.y;
	c.z = f / a.z;
	c.w = f / a.w;

	return c;
}

inline 
const VEC4 operator / (const VEC4 a, const VEC4 &b)
{
	return VEC4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}