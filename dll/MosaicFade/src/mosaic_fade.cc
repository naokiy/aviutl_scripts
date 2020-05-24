#include "mosaic_fade.h"

#include "mosaic_parameter.h"

namespace mosaic_fade {

const int LEVEL_MAX = 255;

void MakeAlphaPatternRandom(aviutl::Map<bool>& pattern,
                            const double transparency, const int seed) {
  std::mt19937 engine(seed);
  const double threshold = transparency / LEVEL_MAX;
  for (aviutl::Point point : aviutl::PointRange(pattern)) {
    pattern.At(point) = (((double)(engine()) / UINT32_MAX) > threshold);
  }
}

void MakeAlphaPatternBayerDither(aviutl::Map<bool>& pattern,
                                 const double transparency) {
  const std::uint8_t bayer_dither_pattern[4][4] = {
      {0, 8, 2, 10}, {12, 4, 14, 6}, {3, 11, 1, 9}, {15, 7, 13, 5}};
  bool dither_pattern[4][4] = {};
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      dither_pattern[x][y] =
          (transparency <= (bayer_dither_pattern[x][y] * 16 + 8));
    }
  }
  for (const aviutl::Point& point : aviutl::PointRange(pattern)) {
    pattern.At(point) = dither_pattern[point.x() % 4][point.y() % 4];
  }
}

void ApplyAlphaPattern(aviutl::Image<double>& image,
                       const aviutl::Map<bool>& alpha_pattern,
                       const MosaicParameter& mosaic_parameter) {
  for (const aviutl::Point& point : aviutl::PointRange(image)) {
    const aviutl::Point map_point = mosaic_parameter.PointInMap(point);
    if (!alpha_pattern.At(map_point)) {
      image.At(point).a = 0.0;
    }
  }
}

void Apply(aviutl::Image<double>& image,
           const MosaicParameter& mosaic_parameter, const double transparency,
           const int random_seed) {
  aviutl::Map<bool> alpha_pattern =
      mosaic_parameter.MakeBlankMap<bool>(image.width(), image.height());

  MakeAlphaPatternRandom(alpha_pattern, transparency, random_seed);

  ApplyAlphaPattern(image, alpha_pattern, mosaic_parameter);
}
}  // namespace mosaic_fade