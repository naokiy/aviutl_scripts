#ifndef AVIUTL_SHARED_INCLUDE_AVIUTL_IMAGE_H_
#define AVIUTL_SHARED_INCLUDE_AVIUTL_IMAGE_H_

#include <cstring>
#include <functional>
#include <iostream>
#include <vector>

#include "irectangle.h"
#include "pixel.h"
#include "point.h"

namespace aviutl {
template <typename T>
class Image : public IRectangle {
 public:
  Image(const Image<T>& source)
      : width_(source.width()), height_(source.height()) {
    pixels_ = std::vector<Pixel<T>>();
    pixels_.reserve(length());
    std::copy(source.pixels_.begin(), source.pixels_.end(), pixels_.begin());
    top_left_ = Point(0, 0);
    bottom_right_ = Point(width_ - 1, height_ - 1);
  };
  Image(const int width, const int height) : width_(width), height_(height) {
    pixels_ = std::vector<Pixel<T>>(length());
    top_left_ = Point(0, 0);
    bottom_right_ = Point(width_ - 1, height_ - 1);
  };
  Image(const Pixel<T>* const data, const int width, const int height)
      : width_(width), height_(height) {
    pixels_ = std::vector<Pixel<T>>();
    pixels_.reserve(length());
    for (int i = 0; i < length(); i++) {
      pixels_[i] = data[i];
    }
    top_left_ = Point(0, 0);
    bottom_right_ = Point(width_ - 1, height_ - 1);
  };
  Image(const RawPixel* const data, const int width, const int height)
      : width_(width), height_(height) {
    pixels_ = std::vector<Pixel<T>>();
    pixels_.reserve(length());
    for (int i = 0; i < length(); i++) {
      pixels_[i] = Pixel<double>(data[i]);
    }
    top_left_ = Point(0, 0);
    bottom_right_ = Point(width_ - 1, height_ - 1);
  };

  constexpr int width() const { return width_; };
  constexpr int height() const { return height_; };
  constexpr int length() const { return width_ * height_; };
  inline const Point& TopLeftPoint() const override { return top_left_; };
  inline const Point& BottomRightPoint() const override {
    return bottom_right_;
  };

  void WriteRaw(RawPixel* const dist) const {
    for (int i = 0; i < length(); i++) {
      const Pixel<T> pixel = pixels_[i];
      dist[i] = pixel.ToRaw();
    }
  };

  constexpr Pixel<T>& At(const Point& point) const& {
    return (pixels_[Pos(point)]);
  };
  inline Pixel<T>& At(const Point& point) & { return (pixels_[Pos(point)]); };
  constexpr Pixel<T> At(const Point& point) const&& {
    return pixels_[Pos(point)];
  };

  constexpr Pixel<T>& At(const int pos) const& { return (pixels_[pos]); };
  inline Pixel<T>& At(const int pos) & { return (pixels_[pos]); };
  constexpr Pixel<T> At(const int pos) const&& { return pixels_[pos]; };

 private:
  constexpr int Pos(const Point& point) const {
    return point.x() + point.y() * width_;
  };
  int width_;
  int height_;
  Point top_left_;
  Point bottom_right_;
  std::vector<Pixel<T>> pixels_;
};
}  // namespace aviutl

#endif  // AVIUTL_SHARED_INCLUDE_AVIUTL_IRECTANGLE_H_