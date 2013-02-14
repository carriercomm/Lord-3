inline 
VEC3::VEC3()
{
	// do nothing
}

inline 
VEC3::VEC3(const Real x, const Real y, const Real z)
{
	set(x, y, z);
}

inline 
VEC3::VEC3(const VEC2 &vec, Real z)
{
	set(vec.x, vec.y, z);
}

inline 
VEC3::VEC3(const VEC3 &vec)
{
	set(vec.x, vec.y, vec.z);
}

inline 
VEC3::operator VEC2 ()
{
	return VEC2(x, y);
}

inline 
VEC3::operator const VEC2 () const
{
	return VEC2(x, y);
}

inline 
VEC3& VEC3::operator = (const VEC3 &rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

inline 
VEC3& VEC3::operator += (const VEC3 &rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

inline 
VEC3& VEC3::operator -= (const VEC3 &rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

inline 
VEC3& VEC3::operator *= (const Real value)
{
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

inline 
VEC3& VEC3::operator /= (const Real value)
{
	x /= value;
	y /= value;
	z /= value;
	return *this;
}

inline 
Real& VEC3::operator [] (int index)
{
	LordAssertX(index >= 0 && index < 3, _T("Access out of bounds"));
	return m[index];
}

inline 
const Real& VEC3::operator [] (int index) const
{
	LordAssertX(index >= 0 && index < 3, _T("Access out of bounds"));
	return m[index];
}

inline 
bool VEC3::operator < (const VEC3 &rhs) const
{
	if( x < rhs.x && y < rhs.y && z < rhs.z)
		return true;
	else
		return false;
}

inline 
bool VEC3::operator <= (const VEC3 &rhs) const
{
	if( x <= rhs.x && y <= rhs.y && z <= rhs.z)
		return true;
	else
		return false;
}

inline 
bool VEC3::operator > (const VEC3 &rhs) const
{
	if( x > rhs.x && y > rhs.y && z > rhs.z)
		return true;
	else
		return false;
}

inline 
bool VEC3::operator >= (const VEC3 &rhs) const
{
	if( x >= rhs.x && y >= rhs.y && z >= rhs.z)
		return true;
	else
		return false;
}

inline 
Real* VEC3::ptr()
{
	return &x;
}

inline 
const Real* VEC3::ptr() const
{
	return &x;
}

inline 
void VEC3::zero()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

inline 
void VEC3::invalid()
{
	*this = INVALID;
}

inline 
void VEC3::set(Real x, Real y, Real z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

inline 
void VEC3::set(Real *p)
{
	this->x = p[0];
	this->y = p[1];
	this->z = p[2];
}

inline 
void VEC3::setVec2(const VEC2 &vec2, Real z)
{
	x = vec2.x;
	y = vec2.y;
	z = z;
}

inline 
Real VEC3::dot(const VEC3 &rhs) const
{
	return (x * rhs.x + y * rhs.y + z * rhs.z);
}

inline 
VEC3 VEC3::cross(const VEC3 &rhs) const
{
	VEC3 vec;

	vec.x = y * rhs.z - z * rhs.y;
	vec.y = z * rhs.x - x * rhs.z;
	vec.z = x * rhs.y - y * rhs.x;

	return vec;
}

inline 
void VEC3::inverse()
{
	x = 1.0f / x;
	y = 1.0f / y;
	z = 1.0f / z;
}

inline 
void VEC3::sqrt()
{
	x = Math::Sqrt(x);
	y = Math::Sqrt(y);
	z = Math::Sqrt(z);
}

inline 
void VEC3::invSqrt()
{
	x = 1.0f / Math::Sqrt(x);
	y = 1.0f / Math::Sqrt(y);
	z = 1.0f / Math::Sqrt(z);
}

inline 
Real VEC3::len() const
{
	Real vecLen;

	Real sum = x * x + y * y + z * z;
	vecLen = Math::Sqrt(sum);

	return vecLen;
}

inline 
Real VEC3::lenSqr() const
{
	return (x * x + y * y + z * z);
}

inline 
void VEC3::normalize()
{
	Real length = len();

	x /= length;
	y /= length;
	z /= length;
}

inline 
Real VEC3::normalizeLen()
{
	Real length = len();

	x /= length;
	y /= length;
	z /= length;

	return length;
}

inline 
VEC3& VEC3::abs()
{
	x = Math::Abs(x);
	y = Math::Abs(y);
	z = Math::Abs(z);

	return *this;
}

inline 
VEC3& VEC3::neg()
{
	x = -x;
	y = -y;
	z = -z;

	return *this;
}

inline 
VEC3& VEC3::saturate()
{
	if ( x > 1.0 ) x = 1.0;
	if ( y > 1.0 ) y = 1.0;
	if ( z > 1.0 ) z = 1.0;

	if ( x < 0.0 ) x = 0.0;
	if ( y < 0.0 ) y = 0.0;
	if ( z < 0.0 ) z = 0.0;

	return *this;
}

inline 
VEC3& VEC3::clampZero()
{
	if ( x < 0.0 ) x = 0.0;
	if ( y < 0.0 ) y = 0.0;
	if ( z < 0.0 ) z = 0.0;

	return *this;
}

inline 
VEC3& VEC3::clampOne()
{
	if ( x > 1.0 ) x = 1.0;
	if ( y > 1.0 ) y = 1.0;
	if ( z > 1.0 ) z = 1.0;

	return *this;
}

inline 
VEC3& VEC3::floor()
{
	x = Math::Floor(x);
	y = Math::Floor(y);
	z = Math::Floor(z);

	return *this;
}

inline 
VEC3& VEC3::ceil()
{
	x = Math::Ceil(x);
	y = Math::Ceil(y);
	z = Math::Ceil(z);

	return *this;
}

inline 
VEC3 VEC3::midPoint(const VEC3& vec) const
{
	return VEC3((x + vec.x) * 0.5f, (y + vec.y) * 0.5f, (z + vec.z) * 0.5f);
}

inline 
void VEC3::makeFloor(const VEC3 &cmp)
{
	if( cmp.x < x ) x = cmp.x;
	if( cmp.y < y ) y = cmp.y;
	if( cmp.z < z ) z = cmp.z;
}

inline 
void VEC3::makeCeil(const VEC3 &cmp)
{
	if( cmp.x > x ) x = cmp.x;
	if( cmp.y > y ) y = cmp.y;
	if( cmp.z > z ) z = cmp.z;
}

inline 
bool VEC3::isInvalid() const
{
	return Math::IsInvalid(x) || Math::IsInvalid(y) || Math::IsInvalid(z);
}

inline 
VEC3 VEC3::perpendicular() const
{
	VEC3 perp = this->cross(VEC3::UNIT_X);

	// Check length
	if(perp.lenSqr() == 0.0)
	{
		/* This vector is the Y axis multiplied by a scalar, so we have
		   to use another axis.
		*/
		perp = this->cross(VEC3::UNIT_Y);
	}
	perp.normalize();

	return perp;
}

inline 
Real VEC3::Dot(const VEC3 &a, const VEC3 &b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline 
void VEC3::Cross(VEC3 &outVec, const VEC3 &a, const VEC3 &b)
{
	outVec.x = a.y * b.z - a.z * b.y;
	outVec.y = a.z * b.x - a.x * b.z;
	outVec.z = a.x * b.y - a.y * b.x;
}

inline 
void VEC3::Lerp(VEC3 &outVec, const VEC3 &a, const VEC3 &b, const Real t)
{
	outVec = a + (b - a) * t;
}

inline 
void VEC3::Max(VEC3 &outVec, const VEC3 &a, const VEC3 &b)
{
	outVec.x = a.x > b.x ? a.x : b.x;
	outVec.y = a.y > b.y ? a.y : b.y;
	outVec.z = a.z > b.z ? a.z : b.z;
}

inline 
void VEC3::Min(VEC3 &outVec, const VEC3 &a, const VEC3 &b)
{
	outVec.x = a.x < b.x ? a.x : b.x;
	outVec.y = a.y < b.y ? a.y : b.y;
	outVec.z = a.z < b.z ? a.z : b.z;
}

inline 
void VEC3::Inverse(VEC3 &outVec, const VEC3 &a)
{
	outVec = a;
	outVec.inverse();
}

inline 
void VEC3::Sqrt(VEC3 &outVec, const VEC3 &a)
{
	outVec = a;
	outVec.sqrt();
}

inline 
void VEC3::InvSqrt(VEC3 &outVec, const VEC3 &a)
{
	outVec = a;
	outVec.invSqrt();
}

inline 
void VEC3::Normalize(VEC3 &outVec, const VEC3 &a)
{
	outVec = a;
	outVec.normalize();
}

inline 
Real VEC3::NormalizeLen(VEC3 &outVec, const VEC3 &a)
{
	outVec = a;
	Real vecLen = outVec.normalizeLen();
	return vecLen;
}

inline 
void VEC3::Abs(VEC3 &outVec, const VEC3 &a)
{
	outVec = a;
	outVec.abs();
}

inline 
void VEC3::Neg(VEC3 &outVec, const VEC3 &a)
{
	outVec = a;
	outVec.neg();
}

inline 
void VEC3::Saturate(VEC3 &outVec, const VEC3 &a)
{
	outVec= a;
	outVec.saturate();
}

inline 
const VEC3 operator + (const VEC3 &rhs)
{
	return rhs;
}

inline 
const VEC3 operator - (const VEC3 &rhs)
{
	return VEC3(-rhs.x, -rhs.y, -rhs.z);
}

inline 
bool operator == (const VEC3 &a, const VEC3 &b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z);
}

inline 
bool operator != (const VEC3 &a, const VEC3 &b)
{
	return !(a.x == b.x && a.y == b.y && a.z == b.z);
}

inline 
const VEC3 operator + (const VEC3 &a, const VEC3 &b)
{
	VEC3 c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;

	return c;
}

inline 
const VEC3 operator - (const VEC3 &a, const VEC3 &b)
{
	VEC3 c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;

	return c;
}

inline 
const VEC3 operator * (const Real f, const VEC3 &v)
{
	VEC3 result;

	result.x = f * v.x;
	result.y = f * v.y;
	result.z = f * v.z;

	return result;
}

inline 
const VEC3 operator * (const VEC3 &v, const Real f)
{
	VEC3 result;

	result.x = f * v.x;
	result.y = f * v.y;
	result.z = f * v.z;

	return result;
}

inline 
const VEC3 operator * (const VEC3 a, const VEC3 &b)
{
	return VEC3(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline 
const VEC3 operator / (const VEC3 &a, const Real f)
{
	VEC3 c;

	c.x = a.x / f;
	c.y = a.y / f;
	c.z = a.z / f;

	return c;
}

inline 
const VEC3 operator / (const Real f, const VEC3 &a)
{
	VEC3 c;

	c.x = f / a.x;
	c.y = f / a.y;
	c.z = f / a.z;

	return c;
}

inline 
const VEC3 operator / (const VEC3 a, const VEC3 &b)
{
	return VEC3(a.x / b.x, a.y / b.y, a.z / b.z);
}