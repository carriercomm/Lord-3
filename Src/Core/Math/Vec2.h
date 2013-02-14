#ifndef __LORD_VEC2_H__
#define __LORD_VEC2_H__

#include "LordMath.h"
#include "../Util/AssertX.h"

LORD_NAMESPACE_BEGIN

// 1x2 Vector (row vector)
class LORD_CORE_API VEC2
{
public:
	union
	{
		struct 
		{
			Real x, y;
		};

		Real m[2];
	};

	static const VEC2 ZERO;				//!< VEC2(0, 0)
	static const VEC2 ONE;				//!< VEC2(1, 1)
	static const VEC2 UNIT_X;			//!< VEC2(1, 0)
	static const VEC2 UNIT_Y;			//!< VEC2(0, 1)
	static const VEC2 NEG_UNIT_X;		//!< VEC2(-1, 0)
	static const VEC2 NEG_UNIT_Y;		//!< VEC2(0, -1)
	static const VEC2 INVALID;			//!< VEC2(Math::MAX_REAL, Math::MAX_REAL)

public:
	VEC2();
	VEC2(const Real x, const Real y);
	VEC2(const VEC2 &vec);

public:
	VEC2& operator = (const VEC2 &rhs);
	VEC2& operator += (const VEC2 &rhs);
	VEC2& operator -= (const VEC2 &rhs);
	VEC2& operator *= (const Real rhs);
	VEC2& operator /= (const Real rhs);
	Real& operator [] (int index);
	const Real& operator [] (int index) const;
	bool operator < (const VEC2 &rhs) const;
	bool operator <= (const VEC2 &rhs) const;
	bool operator > (const VEC2 &rhs) const;
	bool operator >= (const VEC2 &rhs) const;

public:

	Real*			ptr();
	const Real*		ptr() const;
	void			zero();
	void			invalid();
	void			set(Real x, Real y);
	void			set(Real *p);
	Real			dot(const VEC2 &rhs) const;
	Real			cross(const VEC2 &rhs) const;
	void			inverse();
	void			sqrt();
	void			invSqrt();
	Real			len() const;
	Real			lenSqr() const;
	void			normalize();
	Real			normalizeLen();
	VEC2&			abs();
	VEC2&			neg();
	VEC2&			saturate();
	VEC2&			clampZero();
	VEC2&			clampOne();
	VEC2&			floor();
	VEC2&			ceil();
	VEC2			midPoint(const VEC2& vec) const;
	void			makeFloor(const VEC2 &cmp);
	void			makeCeil(const VEC2 &cmp);
	bool			isInvalid() const;

public:

	static Real		Dot(const VEC2 &a, const VEC2 &b);
	static Real		Cross(const VEC2 &a, const VEC2 &b);
	static void		Lerp(VEC2 &outVec, const VEC2 &a, const VEC2 &b, const Real t);
	static void		Max(VEC2 &outVec, const VEC2 &a, const VEC2 &b);
	static void		Min(VEC2 &outVec, const VEC2 &a, const VEC2 &b);
	static void		Inverse(VEC2 &outVec, const VEC2 &a);
	static void		Sqrt(VEC2 &outVec, const VEC2 &a);
	static void		InvSqrt(VEC2 &outVec, const VEC2 &a);
	static void		Normalize(VEC2 &outVec, const VEC2 &a);
	static Real		NormalizeLen(VEC2 &outVec, const VEC2 &a);
	static void		Abs(VEC2 &outVec, const VEC2 &a);
	static void		Neg(VEC2 &outVec, const VEC2 &a);
	static void		Saturate(VEC2 &outVec, const VEC2 &a);

};

LORD_CORE_API const VEC2 operator + (const VEC2 &rhs);
LORD_CORE_API const VEC2 operator - (const VEC2 &rhs);
LORD_CORE_API bool operator == (const VEC2 &a, const VEC2 &b);
LORD_CORE_API bool operator != (const VEC2 &a, const VEC2 &b);
LORD_CORE_API const VEC2 operator + (const VEC2 &a, const VEC2 &b);
LORD_CORE_API const VEC2 operator - (const VEC2 &a, const VEC2 &b);
LORD_CORE_API const VEC2 operator * (const Real f, const VEC2 &v);
LORD_CORE_API const VEC2 operator * (const VEC2 &v, const Real f);
LORD_CORE_API const VEC2 operator * (const VEC2 a, const VEC2 &b);
LORD_CORE_API const VEC2 operator / (const VEC2 &a, const Real f);
LORD_CORE_API const VEC2 operator / (const Real f, const VEC2 &a);
LORD_CORE_API const VEC2 operator / (const VEC2 a, const VEC2 &b);

#include "Vec2.inl"

LORD_NAMESPACE_END

#endif