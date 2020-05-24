#ifndef AVIUTL_ERROR_DIFFUSION_DITHER_INCLUDE_CLOSEST_COLOR_FINDER_H_
#define AVIUTL_ERROR_DIFFUSION_DITHER_INCLUDE_CLOSEST_COLOR_FINDER_H_

#include "aviutl.h"

namespace error_diffusion_dither {

class ClosestColorFinder {
 public:
  ClosestColorFinder(const int level) : level_(level) {
    assert(level >= 1);
    assert(level <= 9);

    const int shift_level = 9 - level;
    max_ = (double)((UINT8_MAX >> shift_level) << shift_level);
    shift_value_ = (256 - max_) / 2;
  };
  constexpr const aviutl::Pixel<double> operator()(
      const aviutl::Pixel<double>& pixel) const {
    aviutl::Pixel<double> new_pixel = aviutl::Pixel<double>();
    new_pixel.r = ModChannelValue(pixel.r);
    new_pixel.g = ModChannelValue(pixel.g);
    new_pixel.b = ModChannelValue(pixel.b);
    new_pixel.a = pixel.a;
    return new_pixel;
  };

 private:
  constexpr double ModChannelValue(const double value) const {
    const double shifted = value + shift_value_;
    if (shifted >= 256.0) {
      return 255.0;
    }
    uint8_t uint8_value = (uint8_t)shifted;
    const int shift_level = 9 - level_;
    return (double)((uint8_value >> shift_level) << shift_level);
  }
  double max_;
  double shift_value_;
  const int level_;
};

}  // namespace error_diffusion_dither

#endif