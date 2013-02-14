#include "CoreStd.h"
#include "Vec4.h"

LORD_NAMESPACE_BEGIN

// predefined specific vectors
const VEC4 VEC4::ZERO(0.0, 0.0, 0.0, 0.0);
const VEC4 VEC4::ONE(1.0, 1.0, 1.0, 1.0);
const VEC4 VEC4::UNIT_X(1, 0, 0, 0);
const VEC4 VEC4::UNIT_Y(0, 1, 0, 0);
const VEC4 VEC4::UNIT_Z(0, 0, 1, 0);
const VEC4 VEC4::NEG_UNIT_X(1, 0, 0, 0);
const VEC4 VEC4::NEG_UNIT_Y(0, 1, 0, 0);
const VEC4 VEC4::NEG_UNIT_Z(0, 0, 1, 0);
const VEC4 VEC4::INVALID(Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL);
const VEC4 VEC4::XYZ_MASK((Real)0xffffffff, (Real)0xffffffff, (Real)0xffffffff, (Real)0x00000000);
const VEC4 VEC4::ABS_MASK((Real)0x7fffffff);
const VEC4 VEC4::SIGN_MASK((Real)0x80000000);

LORD_NAMESPACE_END