#include "CoreStd.h"
#include "Vec2.h"

LORD_NAMESPACE_BEGIN

// predefined specific vectors
const VEC2 VEC2::ZERO(0, 0);
const VEC2 VEC2::ONE(1, 1);
const VEC2 VEC2::UNIT_X(1, 0);
const VEC2 VEC2::UNIT_Y(0, 1);
const VEC2 VEC2::NEG_UNIT_X(-1, 0);
const VEC2 VEC2::NEG_UNIT_Y(0, -1);
const VEC2 VEC2::INVALID(Math::MAX_REAL, Math::MAX_REAL);

LORD_NAMESPACE_END