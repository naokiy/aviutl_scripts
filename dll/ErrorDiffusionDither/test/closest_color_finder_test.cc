#include <closest_color_finder.h>

#include "aviutl.h"
#include "gtest/gtest.h"

namespace {
using namespace error_diffusion_dither;

TEST(ErrorDiffusionDitherTest, FindClosestColor) {
  ClosestColorFinder finder = ClosestColorFinder(1);

  aviutl::Pixel<double> pixel = aviutl::Pixel<double>(127.9, 128, 255, 255);

  aviutl::Pixel<double> new_pixel = finder(pixel);

  EXPECT_DOUBLE_EQ(0.0, new_pixel.r);
  EXPECT_DOUBLE_EQ(255.0, new_pixel.g);
  EXPECT_DOUBLE_EQ(255.0, new_pixel.b);
  EXPECT_DOUBLE_EQ(255.0, new_pixel.a);
}
}  // namespace