#ifndef __LORD_VEC3_H__
#define __LORD_VEC3_H__

#include "Vec2.h"

LORD_NAMESPACE_BEGIN

// 1x3 Vector (row vector)
class LORD_CORE_API VEC3
{
public:

	union
	{
		struct 
		{
			Real x, y, z;
		};

		Real m[3];
	};

	static const VEC3 ZERO;					//!< VEC3(0, 0, 0)
	static const VEC3 ONE;					//!< VEC3(1, 1, 1)
	static const VEC3 UNIT_X;				//!< VEC3(1, 0, 0)
	static const VEC3 UNIT_Y;				//!< VEC3(0, 1, 0)
	static const VEC3 UNIT_Z;				//!< VEC3(0, 0, 1)
	static const VEC3 NEG_UNIT_X;			//!< VEC3(-1, 0, 0)
	static const VEC3 NEG_UNIT_Y;			//!< VEC3(0, -1, 0)
	static const VEC3 NEG_UNIT_Z;			//!< VEC3(0, 0, -1)
	static const VEC3 INVALID;				//!< VEC3(Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL)

public:
	VEC3();
	VEC3(const Real x, const Real f, const Real z);
	VEC3(const VEC2 &vec, Real z);
	VEC3(const VEC3 &vec);

public:
	operator VEC2 ();
	operator const VEC2 () const;
	VEC3& operator = (const VEC3 &rhs);
	VEC3& operator += (const VEC3 &rhs);
	VEC3& operator -= (const VEC3 &rhs);
	VEC3& operator *= (const Real value);
	VEC3& operator /= (const Real value);
	Real& operator [] (int index);
	const Real& operator [] (int index) const;
	bool operator < (const VEC3 &rhs) const;
	bool operator <= (const VEC3 &rhs) const;
	bool operator > (const VEC3 &rhs) const;
	bool operator >= (const VEC3 &rhs) const;

public:

	Real*			ptr();
	const Real*		ptr() const;
	void			zero();
	void			invalid();
	void			set(Real x, Real y ,Real z);
	void			set(Real *p);
	void			setVec2(const VEC2 &vec2, Real z = 0.0);
	Real			dot(const VEC3 &rhs) const;
	VEC3			cross(const VEC3 &rhs) const;
	void			inverse();
	void			sqrt();
	void			invSqrt();
	Real			len() const;
	Real			lenSqr() const;
	void			normalize();
	Real			normalizeLen();
	VEC3&			abs();
	VEC3&			neg();
	VEC3&			saturate();
	VEC3&			clampZero();
	VEC3&			clampOne();
	VEC3&			floor();
	VEC3&			ceil();
	VEC3			midPoint(const VEC3& vec) const;
	void			makeFloor(const VEC3 &cmp);
	void			makeCeil(const VEC3 &cmp);
	bool			isInvalid() const;
	VEC3			perpendicular() const;

public:

	static Real		Dot(const VEC3 &a, const VEC3 &b);
	static void		Cross(VEC3 &outVec, const VEC3 &a, const VEC3 &b);
	static void		Lerp(VEC3 &outVec, const VEC3 &a, const VEC3 &b, const Real t);
	static void		Max(VEC3 &outVec, const VEC3 &a, const VEC3 &b);
	static void		Min(VEC3 &outVec, const VEC3 &a, const VEC3 &b);
	static void		Inverse(VEC3 &outVec, const VEC3 &a);
	static void		Sqrt(VEC3 &outVec, const VEC3 &a);
	static void		InvSqrt(VEC3 &outVec, const VEC3 &a);
	static void		Normalize(VEC3 &outVec, const VEC3 &a);
	static Real		NormalizeLen(VEC3 &outVec, const VEC3 &a);
	static void		Abs(VEC3 &outVec, const VEC3 &a);
	static void		Neg(VEC3 &outVec, const VEC3 &a);
	static void		Saturate(VEC3 &outVec, const VEC3 &a);

};


LORD_CORE_API const VEC3 operator + (const VEC3 &rhs);
LORD_CORE_API const VEC3 operator - (const VEC3 &rhs);
LORD_CORE_API bool operator == (const VEC3 &a, const VEC3 &b);
LORD_CORE_API bool operator != (const VEC3 &a, const VEC3 &b);
LORD_CORE_API const VEC3 operator + (const VEC3 &a, const VEC3 &b);
LORD_CORE_API const VEC3 operator - (const VEC3 &a, const VEC3 &b);
LORD_CORE_API const VEC3 operator * (const Real f, const VEC3 &v);
LORD_CORE_API const VEC3 operator * (const VEC3 &v, const Real f);
LORD_CORE_API const VEC3 operator * (const VEC3 a, const VEC3 &b);
LORD_CORE_API const VEC3 operator / (const VEC3 &a, const Real f);
LORD_CORE_API const VEC3 operator / (const Real f, const VEC3 &a);
LORD_CORE_API const VEC3 operator / (const VEC3 a, const VEC3 &b);

#include "Vec3.inl"

LORD_NAMESPACE_END

#endif