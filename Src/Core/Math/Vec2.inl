inline
VEC2::VEC2()
{
	// do nothing
}

inline
VEC2::VEC2(const Real x, const Real y)
{
	set(x, y);
}

inline
VEC2::VEC2(const VEC2 &vec)
{
	set(vec.x, vec.y);
}

inline 
VEC2& VEC2::operator = (const VEC2 &rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}

inline 
VEC2& VEC2::operator += (const VEC2 &rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

inline 
VEC2& VEC2::operator -= (const VEC2 &rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

inline 
VEC2& VEC2::operator *= (const Real value)
{
	x *= value;
	y *= value;
	return *this;
}

inline 
VEC2& VEC2::operator /= (const Real value)
{
	x /= value;
	y /= value;
	return *this;
}

inline 
Real& VEC2::operator [] (int index)
{
	LordAssertX(index>=0 && index<2, _T("Access out of bounds"));
	return m[index];
}

inline 
const Real& VEC2::operator [] (int index) const
{
	LordAssertX(index>=0 && index<2, _T("Access out of bounds"));
	return m[index];
}

inline 
void VEC2::set(Real x, Real y)
{
	this->x = x;
	this->y = y;
}

inline 
bool VEC2::operator < (const VEC2 &rhs) const
{
	if( x < rhs.x && y < rhs.y )
		return true;
	else
		return false;
}

inline 
bool VEC2::operator <= (const VEC2 &rhs) const
{
	if( x <= rhs.x && y <= rhs.y )
		return true;
	else
		return false;
}

inline 
bool VEC2::operator > (const VEC2 &rhs) const
{
	if( x > rhs.x && y > rhs.y )
		return true;
	else
		return false;
}

inline 
bool VEC2::operator >= (const VEC2 &rhs) const
{
	if( x >= rhs.x && y >= rhs.y )
		return true;
	else
		return false;
}

inline 
Real* VEC2::ptr()
{
	return &x;
}

inline 
const Real* VEC2::ptr() const
{
	return &x;
}

inline 
void VEC2::zero()
{
	x = 0.0;
	y = 0.0;
}

inline 
void VEC2::invalid()
{
	*this = INVALID;
}

inline 
void VEC2::set(Real *p)
{
	this->x = p[0];
	this->y = p[1];
}

inline 
Real VEC2::dot(const VEC2 &rhs) const
{
	return (x * rhs.x + y * rhs.y);
}

inline 
Real VEC2::cross(const VEC2 &rhs) const
{
	return (x * rhs.y - y * rhs.x);
}

inline 
	void VEC2::inverse()
{
	x = 1.0f / x;
	y = 1.0f / y;
}

inline 
void VEC2::sqrt()
{
	x = Math::Sqrt(x);
	y = Math::Sqrt(y);
}

inline 
void VEC2::invSqrt()
{
	x = 1.0f / Math::Sqrt(x);
	y = 1.0f / Math::Sqrt(y);
}

inline 
Real VEC2::len() const
{
	Real vecLen;

	Real sum = x*x + y*y;
	vecLen = Math::Sqrt(sum);

	return vecLen;
}

inline 
Real VEC2::lenSqr() const
{
	Real vecLen = x * x + y * y;
	return vecLen;
}

inline 
void VEC2::normalize()
{
	Real length = len();
	x /= length;
	y /= length;
}

inline 
Real VEC2::normalizeLen()
{
	Real length = len();
	x /= length;
	y /= length;
	return length;
}

inline 
VEC2& VEC2::abs()
{
	x = Math::Abs(x);
	y = Math::Abs(y);
	return *this;
}

inline 
VEC2& VEC2::neg()
{
	x = -x;
	y = -y;
	return *this;
}

inline 
VEC2& VEC2::saturate()
{
	if ( x > 1.0 ) x = 1.0;
	if ( y > 1.0 ) y = 1.0;

	if ( x < 0.0 ) x = 0.0;
	if ( y < 0.0 ) y = 0.0;
	return *this;
}

inline 
VEC2& VEC2::clampZero()
{
	if ( x < 0.0 ) x = 0.0;
	if ( y < 0.0 ) y = 0.0;
	return *this;
}

inline 
VEC2& VEC2::clampOne()
{
	if ( x > 1.0 ) x = 1.0;
	if ( y > 1.0 ) y = 1.0;
	return *this;
}

inline
VEC2& VEC2::floor()
{
	x = Math::Floor(x);
	y = Math::Floor(y);
	return *this;
}

inline
VEC2& VEC2::ceil()
{
	x = Math::Ceil(x);
	y = Math::Ceil(y);
	return *this;
}

inline 
VEC2 VEC2::midPoint(const VEC2& vec) const
{
	return VEC2((x + vec.x) * 0.5f, (y + vec.y) * 0.5f);
}

inline 
void VEC2::makeFloor(const VEC2 &cmp)
{
	if( cmp.x < x ) x = cmp.x;
	if( cmp.y < y ) y = cmp.y;
}

inline 
void VEC2::makeCeil(const VEC2 &cmp)
{
	if( cmp.x > x ) x = cmp.x;
	if( cmp.y > y ) y = cmp.y;
}

inline 
bool VEC2::isInvalid() const
{
	return Math::IsInvalid(x) || Math::IsInvalid(y);
}

inline 
Real VEC2::Dot(const VEC2 &a, const VEC2 &b)
{
	return a.x * b.x + a.y * b.y;
}

inline 
Real VEC2::Cross(const VEC2 &a, const VEC2 &b)
{
	return a.x * b.y - a.y * b.x;
}

inline 
void VEC2::Lerp(VEC2 &outVec, const VEC2 &a, const VEC2 &b, const Real t)
{
	outVec = a + (b - a) * t;
}

inline 
void VEC2::Max(VEC2 &outVec, const VEC2 &a, const VEC2 &b)
{
	outVec.x = a.x > b.x ? a.x : b.x;
	outVec.y = a.y > b.y ? a.y : b.y;
}

inline 
void VEC2::Min(VEC2 &outVec, const VEC2 &a, const VEC2 &b)
{
	outVec.x = a.x < b.x ? a.x : b.x;
	outVec.y = a.y < b.y ? a.y : b.y;
}

inline 
void VEC2::Inverse(VEC2 &outVec, const VEC2 &a)
{
	outVec = a;
	outVec.inverse();
}

inline 
void VEC2::Sqrt(VEC2 &outVec, const VEC2 &a)
{
	outVec = a;
	outVec.sqrt();
}

inline 
void VEC2::InvSqrt(VEC2 &outVec, const VEC2 &a)
{
	outVec = a;
	outVec.invSqrt();
}

inline 
void VEC2::Normalize(VEC2 &outVec, const VEC2 &a)
{
	outVec = a;
	outVec.normalize();
}

inline 
Real VEC2::NormalizeLen(VEC2 &outVec, const VEC2 &a)
{
	outVec = a;
	Real vectorlength = outVec.normalizeLen();
	return vectorlength;
}

inline 
void VEC2::Abs(VEC2 &outVec, const VEC2 &a)
{
	outVec = a;
	outVec.abs();
}

inline 
void VEC2::Neg(VEC2 &outVec, const VEC2 &a)
{
	outVec = a;
	outVec.neg();
}

inline 
void VEC2::Saturate(VEC2 &outVec, const VEC2 &a)
{
	outVec = a;
	outVec.saturate();
}

inline 
const VEC2 operator + (const VEC2 &rhs)
{
	return rhs;
}

inline 
const VEC2 operator - (const VEC2 &rhs)
{
	return VEC2(-rhs.x, -rhs.y);
}

inline 
bool operator == (const VEC2 &a, const VEC2 &b)
{
	return (a.x==b.x && a.y==b.y);
}

inline 
bool operator != (const VEC2 &a, const VEC2 &b)
{
	return !(a.x==b.x && a.y==b.y);
}

inline 
const VEC2 operator + (const VEC2 &a, const VEC2 &b)
{
	VEC2 c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;

	return c;
}

inline 
const VEC2 operator - (const VEC2 &a, const VEC2 &b)
{
	VEC2 c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;

	return c;
}

inline 
const VEC2 operator * (const Real f, const VEC2 &v)
{
	VEC2 result;

	result.x = f * v.x;
	result.y = f * v.y;

	return result;
}

inline 
const VEC2 operator * (const VEC2 &v, const Real f)
{
	VEC2 result;

	result.x = f * v.x;
	result.y = f * v.y;

	return result;
}

inline 
const VEC2 operator * (const VEC2 a, const VEC2 &b)
{
	return VEC2(a.x * b.x, a.y * b.y);
}

inline 
const VEC2 operator / (const VEC2 &a, const Real f)
{
	VEC2 c;

	c.x = a.x / f;
	c.y = a.y / f;

	return c;
}

inline 
const VEC2 operator / (const Real f, const VEC2 &a)
{
	VEC2 c;

	c.x = f / a.x;
	c.y = f / a.y;

	return c;
}

inline 
const VEC2 operator / (const VEC2 a, const VEC2 &b)
{
	return VEC2(a.x / b.x, a.y / b.y);
}