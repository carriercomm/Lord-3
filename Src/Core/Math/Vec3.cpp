#include "CoreStd.h"
#include "Vec3.h"

LORD_NAMESPACE_BEGIN

// predefined specific vectors
const VEC3 VEC3::ZERO(0, 0, 0);
const VEC3 VEC3::ONE(1, 1, 1);
const VEC3 VEC3::UNIT_X(1, 0, 0);
const VEC3 VEC3::UNIT_Y(0, 1, 0);
const VEC3 VEC3::UNIT_Z(0, 0, 1);
const VEC3 VEC3::NEG_UNIT_X(-1, 0, 0);
const VEC3 VEC3::NEG_UNIT_Y(0, -1, 0);
const VEC3 VEC3::NEG_UNIT_Z(0, 0, -1);
const VEC3 VEC3::INVALID(Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL);

LORD_NAMESPACE_END