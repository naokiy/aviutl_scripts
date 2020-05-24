#include <mosaic_fade.h>

#include "aviutl.h"
#include "gtest/gtest.h"
#include "mosaic_parameter.h"

namespace {
using namespace mosaic_fade;

TEST(MosaicFadeTest, BlankMap) {
  const int pixel_size = 10;
  const int offset_x = 7;
  const int offset_y = 3;

  const MosaicParameter mosaic_parameter(pixel_size, offset_x, offset_y);

  const int image_width = 105;
  const int image_height = 205;

  aviutl::Map<bool> map =
      mosaic_parameter.MakeBlankMap<bool>(image_width, image_height);

  EXPECT_EQ(11, map.width());
  EXPECT_EQ(22, map.height());
}

TEST(MosaicFadeTest, PointInMap) {
  const int pixel_size = 10;
  const int offset_x = 7;
  const int offset_y = 3;

  const MosaicParameter mosaic_parameter(pixel_size, offset_x, offset_y);

  const aviutl::Point point_a_in(0, 0);
  const aviutl::Point point_a_out = mosaic_parameter.PointInMap(point_a_in);

  EXPECT_EQ(0, point_a_out.x());
  EXPECT_EQ(0, point_a_out.y());

  const aviutl::Point point_b_in(16, 22);
  const aviutl::Point point_b_out = mosaic_parameter.PointInMap(point_b_in);

  EXPECT_EQ(1, point_b_out.x());
  EXPECT_EQ(2, point_b_out.y());

  const aviutl::Point point_c_in(17, 23);
  const aviutl::Point point_c_out = mosaic_parameter.PointInMap(point_c_in);

  EXPECT_EQ(2, point_c_out.x());
  EXPECT_EQ(3, point_c_out.y());
}

TEST(MosaicFadeTest, MakeRandomPattern) {
  const int pixel_size = 2;
  const int offset_x = 0;
  const int offset_y = 0;
  const int image_width = 10;
  const int image_height = 10;

  const MosaicParameter mosaic_parameter(pixel_size, offset_x, offset_y);

  aviutl::Map<bool> map_a =
      mosaic_parameter.MakeBlankMap<bool>(image_width, image_height);

  const double transparency_a = 255;

  MakeAlphaPatternRandom(map_a, transparency_a, 0);

  EXPECT_FALSE(map_a.At(aviutl::Point(0, 0)));
  EXPECT_FALSE(map_a.At(aviutl::Point(1, 1)));
  EXPECT_FALSE(map_a.At(aviutl::Point(3, 3)));
  EXPECT_FALSE(map_a.At(aviutl::Point(4, 4)));

  aviutl::Map<bool> map_b =
      mosaic_parameter.MakeBlankMap<bool>(image_width, image_height);

  const double transparency_b = 0;

  MakeAlphaPatternRandom(map_b, transparency_b, 0);

  EXPECT_TRUE(map_b.At(aviutl::Point(0, 0)));
  EXPECT_TRUE(map_b.At(aviutl::Point(1, 1)));
  EXPECT_TRUE(map_b.At(aviutl::Point(3, 3)));
  EXPECT_TRUE(map_b.At(aviutl::Point(4, 4)));
}

TEST(MosaicFadeTest, ApplyAlphaPattern) {
  const int pixel_size = 2;
  const int offset_x = 0;
  const int offset_y = 0;
  const int image_width = 10;
  const int image_height = 10;

  const MosaicParameter mosaic_parameter(pixel_size, offset_x, offset_y);

  aviutl::Map<bool> map =
      mosaic_parameter.MakeBlankMap<bool>(image_width, image_height);

  map.At(aviutl::Point(0, 0)) = false;
  map.At(aviutl::Point(2, 1)) = false;
  map.At(aviutl::Point(2, 2)) = true;
  map.At(aviutl::Point(3, 1)) = true;
  map.At(aviutl::Point(3, 2)) = false;
  map.At(aviutl::Point(4, 4)) = false;

  EXPECT_FALSE(map.At(aviutl::Point(0, 0)));
  EXPECT_FALSE(map.At(aviutl::Point(2, 1)));
  EXPECT_TRUE(map.At(aviutl::Point(2, 2)));
  EXPECT_TRUE(map.At(aviutl::Point(3, 1)));
  EXPECT_FALSE(map.At(aviutl::Point(3, 2)));
  EXPECT_FALSE(map.At(aviutl::Point(4, 4)));

  aviutl::Image<double> image(image_width, image_height);

  image.At(aviutl::Point(0, 0)) = aviutl::Pixel<double>(255, 255, 255, 255);
  image.At(aviutl::Point(5, 3)) = aviutl::Pixel<double>(100, 100, 100, 100);
  image.At(aviutl::Point(5, 4)) = aviutl::Pixel<double>(150, 150, 150, 150);
  image.At(aviutl::Point(6, 3)) = aviutl::Pixel<double>(200, 200, 200, 200);
  image.At(aviutl::Point(6, 4)) = aviutl::Pixel<double>(250, 250, 250, 250);
  image.At(aviutl::Point(9, 9)) = aviutl::Pixel<double>(255, 255, 255, 255);

  ApplyAlphaPattern(image, map, mosaic_parameter);

  EXPECT_DOUBLE_EQ(0.0, image.At(aviutl::Point(0, 0)).a);
  EXPECT_DOUBLE_EQ(0.0, image.At(aviutl::Point(5, 3)).a);
  EXPECT_DOUBLE_EQ(150.0, image.At(aviutl::Point(5, 4)).a);
  EXPECT_DOUBLE_EQ(200.0, image.At(aviutl::Point(6, 3)).a);
  EXPECT_DOUBLE_EQ(0.0, image.At(aviutl::Point(6, 4)).a);
  EXPECT_DOUBLE_EQ(0.0, image.At(aviutl::Point(9, 9)).a);
}
}  // namespace