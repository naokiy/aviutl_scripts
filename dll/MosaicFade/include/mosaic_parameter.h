#ifndef AVIUTL_MOSAIC_FADE_INCLUDE_MOSAIC_PARAMETER_H_
#define AVIUTL_MOSAIC_FADE_INCLUDE_MOSAIC_PARAMETER_H_

#include <aviutl.h>

class MosaicParameter final {
 public:
  constexpr MosaicParameter(const int pixel_size, const int offset_x,
                            const int offset_y)
      : pixel_size_(pixel_size),
        offset_x_(FixOffset(offset_x, pixel_size)),
        offset_y_(FixOffset(offset_y, pixel_size)){};
  constexpr aviutl::Point PointInMap(const aviutl::Point& point) const {
    const int map_x = XInMap(point.x());
    const int map_y = YInMap(point.y());
    return aviutl::Point(map_x, map_y);
  };
  template <typename T>
  constexpr aviutl::Map<T> MakeBlankMap(const int image_width,
                                        const int image_height) const {
    const int map_width =
        (int)std::ceil((double)(image_width + offset_x_) / pixel_size_);
    const int map_height =
        (int)std::ceil((double)(image_height + offset_y_) / pixel_size_);

    return aviutl::Map<bool>(map_width, map_height);
  };

 private:
  constexpr int XInMap(const int x) const {
    return (x + offset_x_) / pixel_size_;
  };
  constexpr int YInMap(const int y) const {
    return (y + offset_y_) / pixel_size_;
  };
  constexpr static int FixOffset(const int offset, const int pixel_size) {
    return ((offset % pixel_size) == 0) ? 0
                                        : (pixel_size - (offset % pixel_size));
  };
  const int pixel_size_;
  const int offset_x_;
  const int offset_y_;
};

#endif