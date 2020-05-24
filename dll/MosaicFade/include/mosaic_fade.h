#ifndef AVIUTL_MOSAIC_FADE_INCLUDE_MOSAIC_FADE_H_
#define AVIUTL_MOSAIC_FADE_INCLUDE_MOSAIC_FADE_H_

#include <aviutl.h>

#include <cmath>
#include <cstdint>
#include <cstring>
#include <random>

#include "mosaic_parameter.h"

namespace mosaic_fade {

void MakeAlphaPatternRandom(aviutl::Map<bool>& pattern,
                            const double transparency, const int seed);

void ApplyAlphaPattern(aviutl::Image<double>& image,
                       const aviutl::Map<bool>& alpha_pattern,
                       const MosaicParameter& mosaic_parameter);

void Apply(aviutl::Image<double>& image,
           const MosaicParameter& mosaic_parameter, const double transparency,
           const int random_seed);
}  // namespace mosaic_fade

#endif