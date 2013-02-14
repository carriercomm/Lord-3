inline 
MAT::MAT()
{
}

inline 
MAT::MAT(	Real f00, Real f01, Real f02, Real f03,
			Real f10, Real f11, Real f12, Real f13,
			Real f20, Real f21, Real f22, Real f23,
			Real f30, Real f31, Real f32, Real f33)
{
	m00 = f00; m01 = f01; m02 = f02; m03 = f03;
	m10 = f10; m11 = f11; m12 = f12; m13 = f13;
	m20 = f20; m21 = f21; m22 = f22; m23 = f23;
	m30 = f30; m31 = f31; m32 = f32; m33 = f33;
}

inline 
MAT::MAT(Real *arr)
{
	memcpy(m, arr, sizeof(Real)*16);
}

inline 
MAT::MAT(const MAT &mat)
{
	memcpy(m, mat.m, sizeof(Real)*16);
}

inline 
Real& MAT::operator () (int i, int j)
{ 
	LordAssertX(i>=0 && i<4, _T("Access out of bounds"));
	LordAssertX(j>=0 && j<4, _T("Access out of bounds"));
	return getRow(i)[j];
}

inline 
VEC4 MAT::operator [] (int row)
{
	return getRow(row);
}

inline
MAT& MAT::operator = (const MAT &rhs)
{
	memcpy(m, rhs.m, sizeof(Real)*16);
	return *this;
}

inline 
MAT& MAT::operator += (const Real f)
{
	m00 += f; m01 += f; m02 += f; m03 += f;
	m10 += f; m11 += f; m12 += f; m13 += f;
	m20 += f; m21 += f; m22 += f; m23 += f;
	m30 += f; m31 += f; m32 += f; m33 += f;

	return *this;
}

inline 
MAT& MAT::operator += (const MAT &rhs)
{
	m00 += rhs.m00; m01 += rhs.m01; m02 += rhs.m02; m03 += rhs.m03;
	m10 += rhs.m10; m11 += rhs.m11; m12 += rhs.m12; m13 += rhs.m13;
	m20 += rhs.m20; m21 += rhs.m21; m22 += rhs.m22; m23 += rhs.m23;
	m30 += rhs.m30; m31 += rhs.m31; m32 += rhs.m32; m33 += rhs.m33;

	return *this;
}

inline 
MAT& MAT::operator -= (const Real f)
{
	m00 -= f; m01 -= f; m02 -= f; m03 -= f;
	m10 -= f; m11 -= f; m12 -= f; m13 -= f;
	m20 -= f; m21 -= f; m22 -= f; m23 -= f;
	m30 -= f; m31 -= f; m32 -= f; m33 -= f;

	return *this;
}

inline 
MAT& MAT::operator -= (const MAT &rhs)
{
	m00 -= rhs.m00; m01 -= rhs.m01; m02 -= rhs.m02; m03 -= rhs.m03;
	m10 -= rhs.m10; m11 -= rhs.m11; m12 -= rhs.m12; m13 -= rhs.m13;
	m20 -= rhs.m20; m21 -= rhs.m21; m22 -= rhs.m22; m23 -= rhs.m23;
	m30 -= rhs.m30; m31 -= rhs.m31; m32 -= rhs.m32; m33 -= rhs.m33;

	return *this;
}

inline 
MAT& MAT::operator *= (const Real f)
{
	m00 *= f; m01 *= f; m02 *= f; m03 *= f;
	m10 *= f; m11 *= f; m12 *= f; m13 *= f;
	m20 *= f; m21 *= f; m22 *= f; m23 *= f;
	m30 *= f; m31 *= f; m32 *= f; m33 *= f;

	return *this;
}

inline 
MAT& MAT::operator *= (const MAT &rhs)
{
	m00 = m00 * rhs.m00 + m01 * rhs.m10 + m02 * rhs.m20 + m03 * rhs.m30;
	m01 = m00 * rhs.m01 + m01 * rhs.m11 + m02 * rhs.m21 + m03 * rhs.m31;
	m02 = m00 * rhs.m02 + m01 * rhs.m12 + m02 * rhs.m22 + m03 * rhs.m32;
	m03 = m00 * rhs.m03 + m01 * rhs.m13 + m02 * rhs.m23 + m03 * rhs.m33;
	
	m10 = m10 * rhs.m00 + m11 * rhs.m10 + m12 * rhs.m20 + m13 * rhs.m30;
	m11 = m10 * rhs.m01 + m11 * rhs.m11 + m12 * rhs.m21 + m13 * rhs.m31;
	m12 = m10 * rhs.m02 + m11 * rhs.m12 + m12 * rhs.m22 + m13 * rhs.m32;
	m13 = m10 * rhs.m03 + m11 * rhs.m13 + m12 * rhs.m23 + m13 * rhs.m33;
	
	m20 = m20 * rhs.m00 + m21 * rhs.m10 + m22 * rhs.m20 + m23 * rhs.m30;
	m21 = m20 * rhs.m01 + m21 * rhs.m11 + m22 * rhs.m21 + m23 * rhs.m31;
	m22 = m20 * rhs.m02 + m21 * rhs.m12 + m22 * rhs.m22 + m23 * rhs.m32;
	m23 = m20 * rhs.m03 + m21 * rhs.m13 + m22 * rhs.m23 + m23 * rhs.m33;
	
	m30 = m30 * rhs.m00 + m31 * rhs.m10 + m32 * rhs.m20 + m33 * rhs.m30;
	m31 = m30 * rhs.m01 + m31 * rhs.m11 + m32 * rhs.m21 + m33 * rhs.m31;
	m32 = m30 * rhs.m02 + m31 * rhs.m12 + m32 * rhs.m22 + m33 * rhs.m32;
	m33 = m30 * rhs.m03 + m31 * rhs.m13 + m32 * rhs.m23 + m33 * rhs.m33;

	return *this;
}

inline 
MAT& MAT::operator /= (const Real f)
{
	m00 /= f; m01 /= f; m02 /= f; m03 /= f;
	m10 /= f; m11 /= f; m12 /= f; m13 /= f;
	m20 /= f; m21 /= f; m22 /= f; m23 /= f;
	m30 /= f; m31 /= f; m32 /= f; m33 /= f;

	return *this;
}

inline 
Real* MAT::ptr()
{
	return m;
}

inline 
const Real* MAT::ptr() const
{
	return m;
}

inline 
void MAT::zero()
{
	memset(m, 0, sizeof(Real)*16);
}

inline 
void MAT::invalid()
{
	*this = INVALID;
}

inline 
void MAT::setRow(int row, VEC4 &vec)
{
	LordAssertX(row >= 0 && row < 4, _T("Access out of bounds"));
	Real *p = m + row;
	p[0] = vec.x; 
	p[1] = vec.y;
	p[2] = vec.z;
	p[3] = vec.w;
}

inline 
void MAT::setColumn(int column, VEC4 &vec)
{
	LordAssertX(column >= 0 && column < 4, _T("Access out of bounds"));
	Real *p = m + column;
	p[0] = vec.x; 
	p[4] = vec.y; 
	p[8] = vec.z; 
	p[12] = vec.w; 
}

inline 
VEC4 MAT::getRow(int row) const
{
	LordAssertX(row >= 0 && row < 4, _T("Access out of bounds"));
	const Real *p = m + row*4;
	return VEC4(p[0], p[1], p[2], p[3]);
}

inline 
VEC4 MAT::getColumn(int column) const
{
	LordAssertX(column >= 0 && column < 4, _T("Access out of bounds"));
	const Real *p = m + column;
	return VEC4(p[0], p[4], p[8], p[12]);
}

inline 
void MAT::identity()
{
	*this = IDENTITY;
}

inline 
void MAT::translate(Real x, Real y, Real z)
{
	m30 += x;
	m31 += y;
	m32 += z;
}

inline 
void MAT::translate(const VEC3 &v)
{
	m30 += v.x;
	m31 += v.y;
	m32 += v.z;
}

inline 
void MAT::translateReplace(Real x, Real y, Real z)
{
	identity();
	m30 = x;
	m31 = y;
	m32 = z;
}

inline 
void MAT::translateReplace(const VEC3 &v)
{
	identity();
	m30 += v.x;
	m31 += v.y;
	m32 += v.z;
}

inline 
void MAT::translateX(Real d)
{
	m30 += d;
}

inline 
void MAT::translateY(Real d)
{
	m31 += d;
}

inline 
void MAT::translateZ(Real d)
{
	m32 += d;
}

inline 
void MAT::scale(const VEC3 &scaleVec)
{
	scale(scaleVec[0], scaleVec[1], scaleVec[2]);
}

inline 
void MAT::scale(Real x, Real y, Real z)
{
	m00 *= x; m01 *= x; m02 *= x; m03 *= x;
	m10 *= y; m11 *= y; m12 *= y; m13 *= y;
	m20 *= z; m21 *= z; m22 *= z; m23 *= z;
}

inline 
void MAT::scaleReplace(const VEC3 &scaleVec)
{
	scaleReplace(scaleVec[0], scaleVec[1], scaleVec[2]);
}

inline 
void MAT::scaleReplace(Real x, Real y, Real z)
{
	m00 = x; m01 = 0; m02 = 0; m03 = 0;
	m10 = 0; m11 = y; m12 = 0; m13 = 0;
	m20 = 0; m21 = 0; m22 = z; m23 = 0;
	m30 = 0; m31 = 0; m32 = 0; m33 = 1;
}

// assume input vec.w equals 1
// result.w is garbage
inline 
VEC4 MAT::transform(const VEC4 &vec) const
{
	return vec * (*this);
}

inline 
VEC3 MAT::transform(const VEC3 &vec) const
{
	VEC3 result;

	Real w = vec.x * m03 + vec.y * m13 + vec.z * m23 + m33;
	result.x = (vec.x * m00 + vec.y * m10 + vec.z * m20 + m30) / w;
	result.y = (vec.x * m01 + vec.y * m11 + vec.z * m21 +m31) / w;
	result.z = (vec.x * m02 + vec.y * m12 + vec.z * m22 + m32) / w;

	return result;
}

inline 
VEC4 MAT::transformNormal(const VEC4 &vec) const
{
	MAT mat = *this;
	mat.noTranslate();

	return vec * mat;
}

inline 
VEC3 MAT::transformNormal(const VEC3 &vec) const
{
	MAT mat = *this;
	mat.noTranslate();
	return mat.transform(vec);
}

inline 
MAT& MAT::transpose()
{
	Math::Swap(m01, m10);
	Math::Swap(m02, m20);
	Math::Swap(m03, m30);
	Math::Swap(m12, m21);
	Math::Swap(m13, m31);
	Math::Swap(m23, m32);

	return *this;
}

inline 
MAT& MAT::fastInverse()
{	
	Math::Swap(m01, m10);
	Math::Swap(m02, m20);
	Math::Swap(m12, m21);

	m03 = 0;
	m13 = 0;
	m23 = 0;
	
	m30 = -m30;
	m31 = -m31;
	m32 = -m32;
	m33 = 1;

	return *this;
}

inline 
void MAT::makeTranslation(Real x, Real y, Real z)
{
	identity();
	m30 = x;
	m31 = y;
	m32 = z;
	m33 = 1;
}

inline 
void MAT::makeTranslation(const VEC3 &vec)
{
	makeTranslation(vec.x, vec.y, vec.z);
}

inline 
void MAT::makeScaling(Real x, Real y, Real z)
{
	identity();
	m00 = x;
	m11 = y;
	m22 = z;
}

inline 
void MAT::makeScaling(const VEC3 &vec)
{
	makeScaling(vec.x, vec.y, vec.z);
}

inline 
void MAT::noTranslate()
{
	m30 = 0;
	m31 = 0;
	m32 = 0;
	m33 = 1;
}

inline 
void MAT::noRotate()
{
	m00 = 1; m01 = 0; m02 = 0; m03 = 0;
	m10 = 1; m11 = 1; m12 = 0; m13 = 0;
	m20 = 1; m21 = 0; m22 = 1; m23 = 0;
}

inline 
bool operator == (const MAT &a, const MAT &b)
{
	// true if all vectors equal to each other
	bool result =	a.m00 == b.m00 && a.m01 == b.m01 && a.m02 == b.m02 && a.m03 == b.m03 &&
					a.m10 == b.m10 && a.m11 == b.m11 && a.m12 == b.m12 && a.m13 == b.m13 &&
					a.m20 == b.m20 && a.m21 == b.m21 && a.m22 == b.m22 && a.m23 == b.m23 &&
					a.m30 == b.m30 && a.m31 == b.m31 && a.m32 == b.m32 && a.m33 == b.m33;
	return result;
}

inline 
bool operator != (const MAT &a, const MAT &b)
{
	// true if any one vector not-equal
	bool result =	a.m00 != b.m00 || a.m01 != b.m01 || a.m02 != b.m02 || a.m03 != b.m03 ||
					a.m10 != b.m10 || a.m11 != b.m11 || a.m12 != b.m12 || a.m13 != b.m13 ||
					a.m20 != b.m20 || a.m21 != b.m21 || a.m22 != b.m22 || a.m23 != b.m23 ||
					a.m30 != b.m30 || a.m31 != b.m31 || a.m32 != b.m32 || a.m33 != b.m33;
	return result;
}

inline 
const MAT operator + (const MAT &a, const Real f)
{
	MAT result = a;
	result += f;
	return result;
}

inline 
const MAT operator + (const Real f, const MAT &a)
{
	MAT result = a;
	result += f;
	return result;
}

inline 
const MAT operator + (const MAT &a, const MAT &b)
{
	MAT result;

	result.m00 = a.m00 + b.m00;
	result.m01 = a.m01 + b.m01;
	result.m02 = a.m02 + b.m02;
	result.m03 = a.m03 + b.m03;

	result.m10 = a.m10 + b.m10;
	result.m11 = a.m11 + b.m11;
	result.m12 = a.m12 + b.m12;
	result.m13 = a.m13 + b.m13;
	
	result.m20 = a.m20 + b.m20;
	result.m21 = a.m21 + b.m21;
	result.m22 = a.m22 + b.m22;
	result.m23 = a.m23 + b.m23;
	
	result.m30 = a.m30 + b.m30;
	result.m31 = a.m31 + b.m31;
	result.m32 = a.m32 + b.m32;
	result.m33 = a.m33 + b.m33;

	return result;
}

inline 
const MAT operator - (const MAT &a, const Real f)
{
	MAT result = a;
	result -= f;
	return result;
}

inline 
const MAT operator - (const Real f, const MAT &a)
{
	MAT result = a;
	result -= f;
	return result;
}

inline 
const MAT operator - (const MAT &a, const MAT &b)
{
	MAT result;

	result.m00 = a.m00 - b.m00;
	result.m01 = a.m01 - b.m01;
	result.m02 = a.m02 - b.m02;
	result.m03 = a.m03 - b.m03;

	result.m10 = a.m10 - b.m10;
	result.m11 = a.m11 - b.m11;
	result.m12 = a.m12 - b.m12;
	result.m13 = a.m13 - b.m13;
	
	result.m20 = a.m20 - b.m20;
	result.m21 = a.m21 - b.m21;
	result.m22 = a.m22 - b.m22;
	result.m23 = a.m23 - b.m23;
	
	result.m30 = a.m30 - b.m30;
	result.m31 = a.m31 - b.m31;
	result.m32 = a.m32 - b.m32;
	result.m33 = a.m33 - b.m33;

	return result;
}

inline 
const VEC4 operator * (const VEC4 &v, const MAT &m)
{
	VEC4 result;

	result.x = v.x * m.m00 + v.y * m.m10 + v.z * m.m20 + v.w * m.m30;
	result.y = v.x * m.m01 + v.y * m.m11 + v.z * m.m21 + v.w * m.m31;
	result.z = v.x * m.m02 + v.y * m.m12 + v.z * m.m22 + v.w * m.m32;
	result.w = v.x * m.m03 + v.y * m.m13 + v.z * m.m23 + v.w * m.m33;

	return result;
}

inline 
const MAT operator * (const MAT &a, const MAT &b)
{
	MAT result;

	result.m00 = a.m00 * b.m00 + a.m01 * b.m10 + a.m02 * b.m20 + a.m03 * b.m30;
	result.m01 = a.m00 * b.m01 + a.m01 * b.m11 + a.m02 * b.m21 + a.m03 * b.m31;
	result.m02 = a.m00 * b.m02 + a.m01 * b.m12 + a.m02 * b.m22 + a.m03 * b.m32;
	result.m03 = a.m00 * b.m03 + a.m01 * b.m13 + a.m02 * b.m23 + a.m03 * b.m33;
	
	result.m10 = a.m10 * b.m00 + a.m11 * b.m10 + a.m12 * b.m20 + a.m13 * b.m30;
	result.m11 = a.m10 * b.m01 + a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31;
	result.m12 = a.m10 * b.m02 + a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32;
	result.m13 = a.m10 * b.m03 + a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33;
	
	result.m20 = a.m20 * b.m00 + a.m21 * b.m10 + a.m22 * b.m20 + a.m23 * b.m30;
	result.m21 = a.m20 * b.m01 + a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31;
	result.m22 = a.m20 * b.m02 + a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32;
	result.m23 = a.m20 * b.m03 + a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33;
	
	result.m30 = a.m30 * b.m00 + a.m31 * b.m10 + a.m32 * b.m20 + a.m33 * b.m30;
	result.m31 = a.m30 * b.m01 + a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31;
	result.m32 = a.m30 * b.m02 + a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32;
	result.m33 = a.m30 * b.m03 + a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33;

	return result;
}

inline 
const MAT operator * (const MAT &a, const Real f)
{
	MAT result;

	result.m00 = a.m00 * f;
	result.m01 = a.m01 * f;
	result.m02 = a.m02 * f;
	result.m03 = a.m03 * f;
	
	result.m10 = a.m10 * f;
	result.m11 = a.m11 * f;
	result.m12 = a.m12 * f;
	result.m13 = a.m13 * f;
	
	result.m20 = a.m20 * f;
	result.m21 = a.m21 * f;
	result.m22 = a.m22 * f;
	result.m23 = a.m23 * f;
	
	result.m30 = a.m30 * f;
	result.m31 = a.m31 * f;
	result.m32 = a.m32 * f;
	result.m33 = a.m33 * f;

	return result;
}

inline 
const MAT operator * (const Real f, const MAT &a)
{
	MAT result;

	result.m00 = f * a.m00;
	result.m01 = f * a.m01;
	result.m02 = f * a.m02;
	result.m03 = f * a.m03;
	
	result.m10 = f * a.m10;
	result.m11 = f * a.m11;
	result.m12 = f * a.m12;
	result.m13 = f * a.m13;
	
	result.m20 = f * a.m20;
	result.m21 = f * a.m21;
	result.m22 = f * a.m22;
	result.m23 = f * a.m23;
	
	result.m30 = f * a.m30;
	result.m31 = f * a.m31;
	result.m32 = f * a.m32;
	result.m33 = f * a.m33;

	return result;
}

inline 
const MAT operator / (const MAT &a, const Real f)
{
	MAT result;

	result.m00 = a.m00 / f;
	result.m01 = a.m01 / f;
	result.m02 = a.m02 / f;
	result.m03 = a.m03 / f;
	
	result.m10 = a.m10 / f;
	result.m11 = a.m11 / f;
	result.m12 = a.m12 / f;
	result.m13 = a.m13 / f;
	
	result.m20 = a.m20 / f;
	result.m21 = a.m21 / f;
	result.m22 = a.m22 / f;
	result.m23 = a.m23 / f;
	
	result.m30 = a.m30 / f;
	result.m31 = a.m31 / f;
	result.m32 = a.m32 / f;
	result.m33 = a.m33 / f;

	return result;
}