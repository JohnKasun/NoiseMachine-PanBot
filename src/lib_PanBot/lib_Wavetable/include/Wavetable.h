#pragma once

#define _USE_MATH_DEFINES
#include <assert.h>
#include <math.h>

#include <cmath>
#include <cstdlib>

#include "ErrorDef.h"

namespace Wavetable {
Error_t generateSine(float* buffer, int size, float amplitude = 1.0f);
Error_t generateTri(float* buffer, int size, float amplitude = 1.0f);
}  // namespace Wavetable