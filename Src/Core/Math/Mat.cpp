#include "CoreStd.h"
#include "Mat.h"

LORD_NAMESPACE_BEGIN

// predefined specific matrices
const MAT MAT::ZERO(
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0);

const MAT MAT::INVALID(
	Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL, 
	Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL, 
	Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL, 
	Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL);

const MAT MAT::IDENTITY(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1);

//////////////////////////////////////////////////////////////////////////

Real Minor(MAT &mat, const int r0, const int r1, const int r2, const int c0, const int c1, const int c2)
{
	return  mat(r0,c0) * (mat(r1,c1) * mat(r2,c2) - mat(r2,c1) * mat(r1,c2)) -
	mat(r0,c1) * (mat(r1,c0) * mat(r2,c2) - mat(r2,c0) * mat(r1,c2)) +
	mat(r0,c2) * (mat(r1,c0) * mat(r2,c1) - mat(r2,c0) * mat(r1,c1));
}

MAT MATAdjoint(MAT &mat)
{
	MAT matrix(	Minor(mat, 1, 2, 3, 1, 2, 3),
			   -Minor(mat, 0, 2, 3, 1, 2, 3),
			   Minor(mat, 0, 1, 3, 1, 2, 3),
			   -Minor(mat, 0, 1, 2, 1, 2, 3),
			   
			   -Minor(mat, 1, 2, 3, 0, 2, 3),
			   Minor(mat, 0, 2, 3, 0, 2, 3),
			   -Minor(mat, 0, 1, 3, 0, 2, 3),
			   Minor(mat, 0, 1, 2, 0, 2, 3),
			   
			   Minor(mat, 1, 2, 3, 0, 1, 3),
			   -Minor(mat, 0, 2, 3, 0, 1, 3),
			   Minor(mat, 0, 1, 3, 0, 1, 3),
			   -Minor(mat, 0, 1, 2, 0, 1, 3),
			   
			   -Minor(mat, 1, 2, 3, 0, 1, 2),
			   Minor(mat, 0, 2, 3, 0, 1, 2),
			   -Minor(mat, 0, 1, 3, 0, 1, 2),
			   Minor(mat, 0, 1, 2, 0, 1, 2));
	
	return matrix;
}

Real MATDeterminant(MAT &mat)
{
	return	mat.m00 * Minor(mat, 1, 2, 3, 1, 2, 3) -
	mat.m01 * Minor(mat, 1, 2, 3, 0, 2, 3) +
	mat.m02 * Minor(mat, 1, 2, 3, 0, 1, 3) -
	mat.m03 * Minor(mat, 1, 2, 3, 0, 1, 2);
}

void MAT::rotateAxis(const VEC3 &v, Real radian)
{
	Real x = v.x;
	Real y = v.y;
	Real z = v.z;
	
	Real fSin, fCos;
	fSin = Math::Sin(radian);
	fCos = Math::Cos(radian);
	
	MAT  local, final;
	
	local.m00 = ( x * x ) * ( 1.0f - fCos ) + fCos;
	local.m01 = ( x * y ) * ( 1.0f - fCos ) + (z * fSin);
	local.m02 = ( x * z ) * ( 1.0f - fCos ) - (y * fSin);
	local.m03 = 0.0f;
	
	local.m10 = ( y * x ) * ( 1.0f - fCos ) - (z * fSin);
	local.m11 = ( y * y ) * ( 1.0f - fCos ) + fCos;
	local.m12 = ( y * z ) * ( 1.0f - fCos ) + (x * fSin);
	local.m13 = 0.0f;
	
	local.m20 = ( z * x ) * ( 1.0f - fCos ) + (y * fSin);
	local.m21 = ( z * y ) * ( 1.0f - fCos ) - (x * fSin);
	local.m22 = ( z * z ) * ( 1.0f - fCos ) + fCos;
	local.m23 = 0.0f;
	
	local.m30 = 0.0f;
	local.m31 = 0.0f;
	local.m32 = 0.0f;
	local.m33 = 1.0f;
	
	final = local * (*this);
	*this = final;
}

void MAT::rotateAxisReplace(const VEC3 &axis, Real radian)
{
	Real x = axis.x;
	Real y = axis.y;
	Real z = axis.z;
	
	Real fSin, fCos;
	fSin = Math::Sin(radian);
	fCos = Math::Cos(radian);
	
	m00 = ( x * x ) * ( 1.0f - fCos ) + fCos;
	m01 = ( x * y ) * ( 1.0f - fCos ) + (z * fSin);
	m02 = ( x * z ) * ( 1.0f - fCos ) - (y * fSin);
	m03 = 0.0f;
	
	m10 = ( y * x ) * ( 1.0f - fCos ) - (z * fSin);
	m11 = ( y * y ) * ( 1.0f - fCos ) + fCos;
	m12 = ( y * z ) * ( 1.0f - fCos ) + (x * fSin);
	m13 = 0.0f;
	
	m20 = ( z * x ) * ( 1.0f - fCos ) + (y * fSin);
	m21 = ( z * y ) * ( 1.0f - fCos ) - (x * fSin);
	m22 = ( z * z ) * ( 1.0f - fCos ) + fCos;
	m23 = 0.0f;
	
	m30 = 0.0f;
	m31 = 0.0f;
	m32 = 0.0f;
	m33 = 1.0f;
}

// this = Rx * this
void MAT::rotateX(const Real radian)
{
	Real fSin, fCos;
	fSin = Math::Sin(radian);
	fCos = Math::Cos(radian);
	
	Real temp10 = m10 * fCos + m20 * fSin;
	Real temp11 = m11 * fCos + m21 * fSin;
	Real temp12 = m12 * fCos + m22 * fSin;
	Real temp13 = m13 * fCos + m23 * fSin;
	
	Real temp20 = m10 *-fSin + m20 * fCos;
	Real temp21 = m11 *-fSin + m21 * fCos;
	Real temp22 = m12 *-fSin + m22 * fCos;
	Real temp23 = m13 *-fSin + m23 * fCos;
	
	m10 = temp10;
	m11 = temp11;
	m12 = temp12;
	m13 = temp13;
	m20 = temp20;
	m21 = temp21;
	m22 = temp22;
	m23 = temp23;
}

void MAT::rotateXReplace(const Real radian)
{
	Real fSin, fCos;
	fSin = Math::Sin(radian);
	fCos = Math::Cos(radian);
	
	m00 = 1; m01 = 0; m02 = 0; m03 = 0;
	m10 = 0; m11 = fCos; m12 = fSin; m13 = 0;
	m20 = 0; m21 = -fSin; m22 = fCos; m23 = 0;
	m30 = 0; m31 = 0; m22 = 0; m33 = 1;
}

// this = Ry * this
void MAT::rotateY(const Real radian)
{
	Real temp00, temp01, temp02, temp03;
	Real temp20, temp21, temp22, temp23;
	Real fSin, fCos;
	fSin = Math::Sin(radian);
	fCos = Math::Cos(radian);
	
	temp00 = m00 * fCos - m20 * fSin;
	temp01 = m01 * fCos - m21 * fSin;
	temp02 = m02 * fCos - m22 * fSin;
	temp03 = m03 * fCos - m23 * fSin;
	
	temp20 = m00 * fSin + m20 * fCos;
	temp21 = m01 * fSin + m21 * fCos;
	temp22 = m02 * fSin + m22 * fCos;
	temp23 = m03 * fSin + m23 * fCos;
	
	m00 = temp00;
	m01 = temp01;
	m02 = temp02;
	m03 = temp03;
	m20 = temp20;
	m21 = temp21;
	m22 = temp22;
	m23 = temp23;
}

void MAT::rotateYReplace(const Real radian)
{
	Real fSin, fCos;
	fSin = Math::Sin(radian);
	fCos = Math::Cos(radian);
	
	m00 = fCos; m01 = 0; m02 = -fSin; m03 = 0;
	m10 = 0; m11 = 1; m12 = 0; m13 = 0;
	m20 = -fSin; m21 = 0; m22 = fCos; m23 = 0;
	m30 = 0; m31 = 0; m22 = 0; m33 = 1;
}

// this = Rx * this
void MAT::rotateZ(const Real radian)
{
	Real temp00, temp01, temp02, temp03;
	Real temp10, temp11, temp12, temp13;
	Real fSin, fCos;
	fSin = Math::Sin(radian);
	fCos = Math::Cos(radian);
	
	temp00 = m00 * fCos + m10 * fSin;
	temp01 = m01 * fCos + m11 * fSin;
	temp02 = m02 * fCos + m12 * fSin;
	temp03 = m03 * fCos + m13 * fSin;
	
	temp10 = m00 *-fSin + m10 * fCos;
	temp11 = m01 *-fSin + m11 * fCos;
	temp12 = m02 *-fSin + m12 * fCos;
	temp13 = m03 *-fSin + m13 * fCos;
	
	m00 = temp00;
	m01 = temp01;
	m02 = temp02;
	m03 = temp03;
	m10 = temp10;
	m11 = temp11;
	m12 = temp12;
	m13 = temp13;
}

void MAT::rotateZReplace(const Real radian)
{
	Real fSin, fCos;
	fSin = Math::Sin(radian);
	fCos = Math::Cos(radian);
	
	m00 = fCos; m01 = fSin; m02 = 0; m03 = 0;
	m10 = -fSin; m11 = fCos; m12 = 0; m13 = 0;
	m20 = 0; m21 = 0; m22 = 1; m23 = 0;
	m30 = 0; m31 = 0; m22 = 0; m33 = 1;
}

VEC3 MAT::rotateVEC3(const VEC3 &vec)
{
	VEC3 result;
	
	result.x = vec.x*m00 + vec.y*m10 + vec.z*m20;
	result.y = vec.x*m01 + vec.y*m11 + vec.z*m21;
	result.z = vec.x*m02 + vec.y*m12 + vec.z*m22;
	
	return result;
}

VEC4 MAT::rotateVEC4(const VEC4 &vec)
{
	VEC4 result;
	
	result.x = vec.x*m00 + vec.y*m10 + vec.z*m20;
	result.y = vec.x*m01 + vec.y*m11 + vec.z*m21;
	result.z = vec.x*m02 + vec.y*m12 + vec.z*m22;
	result.w = 1.0;
	
	return result;
}

MAT& MAT::inverse()
{
	MAT mat = (1.0f / MATDeterminant(*this)) * MATAdjoint(*this);
	*this = mat;
	return *this;
}

void MAT::Transpose(MAT &outMat, const MAT &matrix)
{
	outMat = matrix;
	outMat.transpose();
}

void MAT::TransformVEC3(VEC3 &outVec, const VEC3 &v, const MAT &matrix)
{
	Real x = v.x * matrix.m00 + v.y * matrix.m10 + v.z * matrix.m20 + matrix.m30;
	Real y = v.x * matrix.m01 + v.y * matrix.m11 + v.z * matrix.m21 + matrix.m31;
	Real z = v.x * matrix.m02 + v.y * matrix.m12 + v.z * matrix.m22 + matrix.m32;
	outVec.set(x, y, z);
}

void MAT::TransformVEC4(VEC4 &outVec, const VEC4 &v, const MAT &matrix)
{
	Real x = v.x * matrix.m00 + v.y * matrix.m10 + v.z * matrix.m20 + v.w * matrix.m30;
	Real y = v.x * matrix.m01 + v.y * matrix.m11 + v.z * matrix.m21 + v.w * matrix.m31;
	Real z = v.x * matrix.m02 + v.y * matrix.m12 + v.z * matrix.m22 + v.w * matrix.m32;
	Real w = v.x * matrix.m03 + v.y * matrix.m13 + v.z * matrix.m23 + v.w * matrix.m33;
	outVec.set(x, y, z, w);
}

void MAT::FastInverse(MAT &outMat, const MAT &matrix)
{
	outMat = matrix;
	outMat.fastInverse();
}

void MAT::RotateAxis(MAT &outMat, const VEC3 &axis, const Real radian)
{
	Real fSin, fCos;
	fSin = Math::Sin(radian);
	fCos = Math::Cos(radian);
	Real fOneMinusCos = 1.0f - fCos;
	
	VEC3 v_Mul_Sin = axis * fSin;
	VEC3 multipler = fOneMinusCos * axis;

	outMat.m00 = axis.x * multipler.x + fCos;
	outMat.m01 = axis.x * multipler.y + v_Mul_Sin.z;
	outMat.m02 = axis.x * multipler.z + -v_Mul_Sin.y;
	outMat.m03 = 0;
	
	outMat.m10 = axis.y * multipler.x + -v_Mul_Sin.z;
	outMat.m11 = axis.y * multipler.y + fCos;
	outMat.m12 = axis.y * multipler.z + v_Mul_Sin.x;
	outMat.m13 = 0;
	
	outMat.m20 = axis.y * multipler.x + v_Mul_Sin.y;
	outMat.m21 = axis.y * multipler.y + -v_Mul_Sin.x;
	outMat.m22 = axis.y * multipler.z + fCos;
	outMat.m23 = 0;
	
	outMat.m30 = 0;
	outMat.m31 = 0;
	outMat.m32 = 0;
	outMat.m33 = 1;
}

void MAT::RotateYawPitchRoll(MAT &outMat, Real yaw, Real pitch, Real roll)
{
	outMat.identity();
	outMat.rotateZ(roll);
	outMat.rotateX(pitch);
	outMat.rotateY(yaw);
}

void MAT::LookAtRH(MAT &outMat, const VEC3 &eye, const VEC3 &at, const VEC3 &up)
{
	VEC3 upNormalized;
	VEC3::Normalize(upNormalized, up);
	
	VEC3 zAxis = at - eye;
	zAxis.normalize();
	
	VEC3 xAxis;
	VEC3::Cross(xAxis, upNormalized, zAxis);
	xAxis.normalize();
	
	VEC3 yAxis;
	VEC3::Cross(yAxis, zAxis, xAxis);
	
	outMat.m00 = xAxis.x;
	outMat.m01 = xAxis.y;
	outMat.m02 = xAxis.z;
	outMat.m03 = 0.0;
	outMat.m10 = yAxis.x;
	outMat.m11 = yAxis.y;
	outMat.m12 = yAxis.z;
	outMat.m13 = 0.0;
	outMat.m20 = zAxis.x;
	outMat.m21 = zAxis.y;
	outMat.m22 = zAxis.z;
	outMat.m23 = 0.0;
	outMat.m30 = -VEC3::Dot(xAxis, eye);
	outMat.m31 = -VEC3::Dot(yAxis, eye);
	outMat.m32 = -VEC3::Dot(zAxis, eye);
	outMat.m33 = 1.0;
}

void MAT::LookAtLH(MAT &outMat, const VEC3 &eye, const VEC3 &at, const VEC3 &up)
{
	VEC3 upNormalized;
	VEC3::Normalize(upNormalized, up);
	
	VEC3 zAxis = at - eye;
	zAxis.normalize();
	
	VEC3 xAxis;
	VEC3::Cross(xAxis, upNormalized, zAxis);
	xAxis.normalize();
	
	VEC3 yAxis;
	VEC3::Cross(yAxis, zAxis, xAxis);
	
	outMat.m00 = xAxis.x;
	outMat.m10 = xAxis.y;
	outMat.m20 = xAxis.z;
	outMat.m01 = yAxis.x;
	outMat.m11 = yAxis.y;
	outMat.m21 = yAxis.z;
	outMat.m02 = zAxis.x;
	outMat.m12 = zAxis.y;
	outMat.m22 = zAxis.z;
	outMat.m22 = zAxis.z;
	outMat.m03 = 0.0;
	outMat.m13 = 0.0;
	outMat.m23 = 0.0;
	outMat.m30 = -VEC3::Dot(xAxis, eye);
	outMat.m31 = -VEC3::Dot(yAxis, eye);
	outMat.m32 = -VEC3::Dot(zAxis, eye);
	outMat.m33 = 1.0;
}

void MAT::OrthoRHD3D(MAT &outMat, Real w, Real h, Real zn, Real zf)
{
	outMat.identity();
	outMat[0][0] = 2.0f / w;
	outMat[1][1] = 2.0f / h;
	outMat[2][2] = 1.0f / (zn - zf);
	outMat[3][2] = zn / (zn - zf);
}

void MAT::OrthoLHD3D(MAT &outMat, Real w, Real h, Real zn, Real zf)
{
	outMat.identity();
	outMat[0][0] = 2.0f / w;
	outMat[1][1] = 2.0f / h;
	outMat[2][2] = 1.0f / (zf - zn);
	outMat[3][2] = zn / (zn - zf);
}

void MAT::OrthoRHGL(MAT &outMat, Real w, Real h, Real zn, Real zf)
{
	outMat.identity();
	outMat[0][0] = 2.0f / w;
	outMat[1][1] = 2.0f / h;
	outMat[2][2] = 2.0f / (zn - zf);
	outMat[3][2] = (zn + zf)/(zn - zf);
}

void MAT::OrthoLHGL(MAT &outMat, Real w, Real h, Real zn, Real zf)
{
	outMat.identity();
	outMat[0][0] = 2.0f / w;
	outMat[1][1] = 2.0f / h;
	outMat[2][2] = 2.0f / (zf - zn);
	outMat[3][2] = (zn + zf)/(zn - zf);
}

void MAT::OrthoOffCenterRHD3D(MAT &outMat, Real l, Real r, Real b, Real t, Real zn, Real zf)
{
	outMat.identity();
	outMat[0][0] = 2.0f / (r - l);
	outMat[1][1] = 2.0f / (t - b);
	outMat[2][2] = 1.0f / (zn -zf);
	outMat[3][0] = (r + l) / (l - r);
	outMat[3][1] = (t + b) / (b - t);
	outMat[3][2] = zn / (zn - zf);
}

void MAT::OrthoOffCenterLHD3D(MAT &outMat, Real l, Real r, Real b, Real t, Real zn, Real zf)
{
	outMat.identity();
	outMat[0][0] = 2.0f / (r - l);
	outMat[1][1] = 2.0f / (t - b);
	outMat[2][2] = 1.0f / (zf -zn);
	outMat[3][0] = (r + l) / (l - r);
	outMat[3][1] = (t + b) / (b - t);
	outMat[3][2] = zn / (zn - zf);
}

void MAT::OrthoOffCenterRHGL(MAT &outMat, Real l, Real r, Real b, Real t, Real zn, Real zf)
{
	outMat.identity();
	outMat[0][0] = 2.0f / (r - l);
	outMat[1][1] = 2.0f / (t - b);
	outMat[2][2] = 2.0f / (zn -zf);
	outMat[3][0] = (r + l) / (l - r);
	outMat[3][1] = (t + b) / (b - t);
	outMat[3][2] = (zn + zf) / (zn - zf);
}

void MAT::OrthoOffCenterLHGL(MAT &outMat, Real l, Real r, Real b, Real t, Real zn, Real zf)
{
	outMat.identity();
	outMat[0][0] = 2.0f / (r - l);
	outMat[1][1] = 2.0f / (t - b);
	outMat[2][2] = 2.0f / (zf -zn);
	outMat[3][0] = (r + l) / (l - r);
	outMat[3][1] = (t + b) / (b - t);
	outMat[3][2] = (zn + zf) / (zn - zf);
}

void MAT::PerspectiveFovRHD3D(MAT &outMat, Real fovy, Real aspect, Real zn, Real zf)
{
	outMat.identity();
	
	Real yScale = 1.0f / Math::Tan(fovy / 2.0f);
	Real xScale = yScale / aspect;
	
	outMat[0][0] = xScale;
	outMat[1][1] = yScale;
	outMat[2][2] = zf / (zn - zf);
	outMat[2][3] = -1.0f;
	outMat[3][2] = (zn * zf) / (zn - zf);
	outMat[3][3] = 0.0f;
}

void MAT::PerspectiveFovLHD3D(MAT &outMat, Real fovy, Real aspect, Real zn, Real zf)
{
	outMat.identity();
	
	Real yScale = 1.0f / Math::Tan(fovy / 2.0f);
	Real xScale = yScale / aspect;
	
	outMat[0][0] = xScale;
	outMat[1][1] = yScale;
	outMat[2][2] = zf / (zf - zn);
	outMat[2][3] = 1.0f;
	outMat[3][2] = (zn * zf) / (zn - zf);
	outMat[3][3] = 0.0f;
}

void MAT::PerspectiveFovRHGL(MAT &outMat, Real fovy, Real aspect, Real zn, Real zf)
{
	outMat.identity();
	
	Real yScale = 1.0f / Math::Tan(fovy / 2.0f);
	Real xScale = yScale / aspect;
	
	outMat[0][0] = xScale;
	outMat[1][1] = yScale;
	outMat[2][2] = (zn + zf) / (zn - zf);
	outMat[2][3] = -1.0;
	outMat[3][2] = 2.0f * zn * zf / (zn - zf);
	outMat[3][3] = 0.0f;
}

void MAT::PerspectiveFovLHGL(MAT &outMat, Real fovy, Real aspect, Real zn, Real zf)
{
	outMat.m00 = 1.0f / (aspect * Math::Tan(fovy * 0.5f));
	outMat.m01 = 0.0;
	outMat.m02 = 0.0;
	outMat.m03 = 0.0;
	outMat.m10 = 0.0;
	outMat.m11 = 1.0f / Math::Tan(fovy * 0.5f);
	outMat.m12 = 0.0;
	outMat.m13 = 0.0;
	outMat.m20 = 0.0;
	outMat.m21 = 0.0;
	outMat.m22 = zf / (zf - zn);
	outMat.m23 = 1.0;
	outMat.m30 = 0.0;
	outMat.m31 = 0.0;
	outMat.m32 = (-zn) * zf / (zf - zn);
	outMat.m33 = 0.0;
}

LORD_NAMESPACE_END