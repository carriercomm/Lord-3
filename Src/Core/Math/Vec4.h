#ifndef __LORD_VEC4_H__
#define __LORD_VEC4_H__

#include "Vec3.h"

LORD_NAMESPACE_BEGIN

/**
\brief 1x4 Vector (row vector)
*/
class LORD_CORE_API VEC4
{
public:
	union
	{
		struct 
		{
			Real x, y, z, w;
		};
		Real m[4];
	};

	static const VEC4 ZERO;
	static const VEC4 ONE;
	static const VEC4 UNIT_X;				//!< VEC4(1, 0, 0, 0)
	static const VEC4 UNIT_Y;				//!< VEC4(0, 1, 0, 0)
	static const VEC4 UNIT_Z;				//!< VEC4(0, 0, 1, 0)
	static const VEC4 NEG_UNIT_X;			//!< VEC4(-1, 0, 0, 0)
	static const VEC4 NEG_UNIT_Y;			//!< VEC4(0, -1, 0, 0)
	static const VEC4 NEG_UNIT_Z;			//!< VEC4(0, 0, -1, 0)
	static const VEC4 INVALID;				//!< VEC4(Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL)
	static const VEC4 XYZ_MASK;				//!< VEC4(0xffffffff, 0xffffffff, 0xffffffff, 0)
	static const VEC4 ABS_MASK;				//!< VEC4(0x7fffffff, 0xffffffff, 0xffffffff, 0)
	static const VEC4 SIGN_MASK;

public:
	VEC4();
	VEC4(const Real x, const Real y, const Real z, const Real w = 0.0);
	VEC4(const Real value);
	VEC4(const VEC3 &vec3, Real w = 0.0);
	VEC4(const VEC4 &vec);

public:
	operator VEC2 ();
	operator const VEC2 () const;
	operator VEC3 ();
	operator const VEC3 () const;
	VEC4& operator = (const VEC4 &rhs);
	VEC4& operator = (const Real value);
	VEC4& operator += (const VEC4 &rhs);
	VEC4& operator += (const Real value);
	VEC4& operator -= (const VEC4 &rhs);
	VEC4& operator -= (const Real value);
	VEC4& operator *= (const VEC4 &rhs);
	VEC4& operator *= (const Real value);
	VEC4& operator /= (const VEC4 &rhs);
	VEC4& operator /= (const Real value);
	Real& operator [] (int index);
	const Real& operator [] (int index) const;

public:

	Real*			ptr();
	const Real*		ptr() const;
	void			zero();
	void			invalid();
	void			set(Real x, Real y, Real z, Real w = 0.0);
	void			set(Real value);
	void			set(Real *p);
	void			setVec3(const VEC3 &vec3, Real w = 0.0);
	VEC3			getVec3();
	Real			dot(const VEC4 &rhs) const;
	void			inverse();
	void			sqrt();
	void			invSqrt();
	Real			len() const;
	Real			lenSqr() const;
	void			normalize();
	Real			normalizeLen();
	VEC4&			abs();
	VEC4&			neg();
	VEC4&			saturate();
	VEC4&			clampZero();
	VEC4&			clampOne();
	VEC4&			floor();
	VEC4&			ceil();
	VEC4			midPoint(const VEC4& vec) const;
	void			makeFloor(const VEC4 &cmp);
	void			makeCeil(const VEC4 &cmp);
	bool			isInvalid() const;

public:

	static Real		Dot(const VEC4 &a, const VEC4 &b);
	static void		Lerp(VEC4 &outVec, const VEC4 &a, const VEC4 &b, const Real t);
	static void		Max(VEC4 &outVec, const VEC4 &a, const VEC4 &b);
	static void		Min(VEC4 &outVec, const VEC4 &a, const VEC4 &b);
	static void		Inverse(VEC4 &outVec, const VEC4 &a);
	static void		Sqrt(VEC4 &outVec, const VEC4 &a);
	static void		InvSqrt(VEC4 &outVec, const VEC4 &a);
	static void		Normalize(VEC4 &outVec, const VEC4 &a);
	static Real		NormalizeLen(VEC4 &outVec, const VEC4 &a);
	static void		Abs(VEC4 &outVec, const VEC4 &a);
	static void		Neg(VEC4 &outVec, const VEC4 &a);
	static void		Saturate(VEC4 &outVec, const VEC4 &a);

};


LORD_CORE_API const VEC4 operator + (const VEC4 &rhs);
LORD_CORE_API const VEC4 operator - (const VEC4 &rhs);
LORD_CORE_API bool operator == (const VEC4 &a, const VEC4 &b);
LORD_CORE_API bool operator != (const VEC4 &a, const VEC4 &b);
LORD_CORE_API const VEC4 operator + (const VEC4 &a, const VEC4 &b);
LORD_CORE_API const VEC4 operator - (const VEC4 &a, const VEC4 &b);
LORD_CORE_API const VEC4 operator * (const Real f, const VEC4 &v);
LORD_CORE_API const VEC4 operator * (const VEC4 &v, const Real f);
LORD_CORE_API const VEC4 operator * (const VEC4 a, const VEC4 &b);
LORD_CORE_API const VEC4 operator / (const VEC4 &a, const Real f);
LORD_CORE_API const VEC4 operator / (const Real f, const VEC4 &a);
LORD_CORE_API const VEC4 operator / (const VEC4 a, const VEC4 &b);

#include "Vec4.inl"

LORD_NAMESPACE_END

#endif