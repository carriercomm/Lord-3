#include "CoreStd.h"
#include "LordMath.h"

LORD_NAMESPACE_BEGIN

namespace Math
{

// predefined specific
const Real PI						= (Real)(3.14159265358979323846264338327950288419716939937511);
const Real PI_2						= Math::PI * 2.0f;
const Real PI_DIV2					= Math::PI * 0.5f;
const Real PI_DIV3					= Math::PI / 3.0f;
const Real PI_DIV4					= Math::PI / 4.0f;
const Real PI_DIV5					= Math::PI / 5.0f;
const Real PI_DIV6					= Math::PI / 6.0f;
const Real PI_DIV8					= Math::PI / 8.0f;
const Real PI_DIV180				= Math::PI / 180.0f;
const Real PI_SQR					= (Real)(9.86960440108935861883449099987615113531369940724079);
const Real PI_INV					= (Real)(0.31830988618379067153776752674502872406891929148091);
//const Real EPSILON				= (Real)(1e-10);
const Real EPSILON					= std::numeric_limits<Real>::epsilon();
const Real LOWEPSILON				= (Real)(1e-04);
const Real POS_INFINITY				= std::numeric_limits<Real>::infinity();
const Real NEG_INFINITY				= -std::numeric_limits<Real>::infinity();
const Real LN2						= std::log(2.0f);
const Real LN10						= std::log(10.0f);
const Real INV_LN2					= 1.0f / LN2;
const Real INV_LN10					= 1.0f / LN10;
const Real DEG2RAD					= (Real)0.01745329;
const Real RAD2DEG					= (Real)57.29577;

#ifdef LORD_PRECISION_DOUBLE
const Real MIN_REAL					= 2.2250738585072014e-308;
const Real MAX_REAL					= 1.7976931348623158e+308;
#else
const Real MIN_REAL					= 1.175494351e-38F;
const Real MAX_REAL					= 3.402823466e+38F;
#endif

const float MIN_FLOAT				= 1.175494351e-38F;
const float MAX_FLOAT				= 3.402823466e+38F;
const double MIN_DOUBLE				= 2.2250738585072014e-308;
const double MAX_DOUBLE				= 1.7976931348623158e+308;

Real UnitRandom(unsigned int uiSeed)
{
	if (uiSeed > 0)
	{
		srand(uiSeed);
	}

	Real dRatio = ((Real)rand())/((Real)(RAND_MAX));
	return dRatio;
}

Real SymmetricRandom(unsigned int uiSeed)
{
	if (uiSeed > 0.0)
		srand(uiSeed);

	Real dRatio = ((Real)rand())/((Real)(RAND_MAX));
	return (2.0f * dRatio - 1.0f);
}

Real IntervalRandom (Real fMin, Real fMax, unsigned int uiSeed)
{
	if (uiSeed > 0)
		srand(uiSeed);

	Real dRatio = ((Real)rand())/((Real)(RAND_MAX));
	return (fMin + (fMax-fMin)*dRatio);
}

} // - End namespace Math

LORD_NAMESPACE_END