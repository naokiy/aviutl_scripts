#ifndef AVIUTL_ERROR_DIFFUSION_DITHER_INCLUDE_ERROR_DIFFUSION_DITHER_H_
#define AVIUTL_ERROR_DIFFUSION_DITHER_INCLUDE_ERROR_DIFFUSION_DITHER_H_

#include "aviutl.h"

namespace error_diffusion_dither {
void Apply(aviutl::Image<double>& image, const int level);
}  // namespace error_diffusion_dither

#endif