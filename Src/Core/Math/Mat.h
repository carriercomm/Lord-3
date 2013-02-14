#ifndef __LORD_MATRIX_H__
#define __LORD_MATRIX_H__

#include "Vec4.h"

LORD_NAMESPACE_BEGIN

/**
\brief 4x4 Matrix (row major)
*/
class LORD_CORE_API MAT
{
public:
	union
	{
		struct
		{
			Real m00, m01, m02, m03;
			Real m10, m11, m12, m13;
			Real m20, m21, m22, m23;
			Real m30, m31, m32, m33;
		};
		
		Real m[16];
	};

	static const MAT ZERO;
	static const MAT IDENTITY;
	static const MAT INVALID;

public:
	MAT();
	MAT(Real f00, Real f01, Real f02, Real f03,
		Real f10, Real f11, Real f12, Real f13,
		Real f20, Real f21, Real f22, Real f23,
		Real f30, Real f31, Real f32, Real f33);
	MAT(Real *arr);
	MAT(const MAT &mat);
	
public:
	Real& operator () (int i, int j);
	VEC4 operator [] (int row);
	MAT& operator = (const MAT &rhs);
	MAT& operator += (const Real f);
	MAT& operator += (const MAT &rhs);
	MAT& operator -= (const Real f);
	MAT& operator -= (const MAT &rhs);
	MAT& operator *= (const Real f);
	MAT& operator *= (const MAT &rhs);
	MAT& operator /= (const Real f);
	
public:
	
	Real*			ptr();
	const Real*		ptr() const;
	void			zero();
	void			invalid();
	void			setRow(int row, VEC4 &vec);
	void			setColumn(int column, VEC4 &vec);
	VEC4			getRow(int row) const;
	VEC4			getColumn(int column) const;
	void			identity();
	void			translate(Real x, Real y, Real z);
	void			translate(const VEC3 &v);
	void			translateReplace(Real x, Real y, Real z);
	void			translateReplace(const VEC3 &v);
	void			translateX(Real d);
	void			translateY(Real d);
	void			translateZ(Real d);
	void			rotateAxis(const VEC3 &axis, Real radian);
	void			rotateAxisReplace(const VEC3 &axis, Real radian);
	void			rotateX(const Real radian);
	void			rotateXReplace(const Real radian);
	void			rotateY(const Real radian);
	void			rotateYReplace(const Real radian);
	void			rotateZ(const Real radian);
	void			rotateZReplace(const Real radian);
	VEC3			rotateVEC3(const VEC3 &vec);
	VEC4			rotateVEC4(const VEC4 &vec);
	void			scale(const VEC3 &scaleVec);
	void			scale(Real x, Real y, Real z);
	void			scaleReplace(const VEC3 &scaleVec);
	void			scaleReplace(Real x, Real y, Real z);
	VEC4			transform(const VEC4 &vec) const;
	VEC3			transform(const VEC3 &vec) const;
	VEC4			transformNormal(const VEC4 &vec) const;
	VEC3			transformNormal(const VEC3 &vec) const;
	MAT&			transpose();
	MAT&			fastInverse();
	MAT&			inverse();
	void			makeTranslation(Real x, Real y, Real z);
	void			makeTranslation(const VEC3 &vec);
	void			makeScaling(Real x, Real y, Real z);
	void			makeScaling(const VEC3 &vec);
	void			noTranslate();
	void			noRotate();
	
public:
	static void		Transpose(MAT &outMat, const MAT &matrix);
	static void		TransformVEC3(VEC3 &outVec, const VEC3 &v, const MAT &matrix);
	static void		TransformVEC4(VEC4 &outVec, const VEC4 &v, const MAT &matrix);
	static void		TransformNormal(VEC3 &outVec, const VEC3 &v, const MAT &matrix);
	static void		FastInverse(MAT &outMat, const MAT &matrix);
	static void		RotateAxis(MAT &outMat, const VEC3 &axis, const Real radian);
	static void		RotateYawPitchRoll(MAT &outMat, Real yaw, Real pitch, Real roll);
	static void		LookAtRH(MAT &outMat, const VEC3 &eye, const VEC3 &at, const VEC3 &up);
	static void		LookAtLH(MAT &outMat, const VEC3 &eye, const VEC3 &at, const VEC3 &up);
	static void		OrthoRHD3D(MAT &outMat, Real w, Real h, Real zn, Real zf);
	static void		OrthoLHD3D(MAT &outMat, Real w, Real h, Real zn, Real zf);
	static void		OrthoRHGL(MAT &outMat, Real w, Real h, Real zn, Real zf);
	static void		OrthoLHGL(MAT &outMat, Real w, Real h, Real zn, Real zf);
	static void		OrthoOffCenterRHD3D(MAT &outMat, Real l, Real r, Real b, Real t, Real zn, Real zf);
	static void		OrthoOffCenterLHD3D(MAT &outMat, Real l, Real r, Real b, Real t, Real zn, Real zf);
	static void		OrthoOffCenterRHGL(MAT &outMat, Real l, Real r, Real b, Real t, Real zn, Real zf);
	static void		OrthoOffCenterLHGL(MAT &outMat, Real l, Real r, Real b, Real t, Real zn, Real zf);
	static void		PerspectiveFovRHD3D(MAT &outMat, Real fovy, Real aspect, Real zn, Real zf);
	static void		PerspectiveFovLHD3D(MAT &outMat, Real fovy, Real aspect, Real zn, Real zf);
	static void		PerspectiveFovRHGL(MAT &outMat, Real fovy, Real aspect, Real zn, Real zf);
	static void		PerspectiveFovLHGL(MAT &outMat, Real fovy, Real aspect, Real zn, Real zf);
};

LORD_CORE_API bool operator == (const MAT &a, const MAT &b);
LORD_CORE_API bool operator != (const MAT &a, const MAT &b);
LORD_CORE_API const MAT operator + (const MAT &a, const Real f);
LORD_CORE_API const MAT operator + (const Real f, const MAT &a);
LORD_CORE_API const MAT operator + (const MAT &a, const MAT &b);
LORD_CORE_API const MAT operator - (const MAT &a, const Real f);
LORD_CORE_API const MAT operator - (const Real f, const MAT &a);
LORD_CORE_API const MAT operator - (const MAT &a, const MAT &b);
LORD_CORE_API const VEC4 operator * (const VEC4 &vec, const MAT &matrix);
LORD_CORE_API const MAT operator * (const MAT &a, const MAT &b);
LORD_CORE_API const MAT operator * (const MAT &a, const Real f);
LORD_CORE_API const MAT operator * (const Real f, const MAT &a);
LORD_CORE_API const MAT operator / (const MAT &matrix, const Real f);

#include "Mat.inl"

LORD_NAMESPACE_END

//#include "Quat.h"

#endif