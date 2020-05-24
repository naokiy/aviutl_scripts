#ifndef AVIUTL_SHARED_INCLUDE_AVIUTL_MAP_H_
#define AVIUTL_SHARED_INCLUDE_AVIUTL_MAP_H_

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <vector>

#include "irectangle.h"
#include "point.h"
#include "point_range.h"

namespace aviutl {
template <typename T>
class Map : public IRectangle {
 public:
  Map(const int width, const int height) : width_(width), height_(height) {
    data_ = std::vector<T>(length());
    top_left_ = Point(0, 0);
    bottom_right_ = Point(width_ - 1, height_ - 1);
  };
  Map(const Map<T>& source)
      : data_(std::vector<T>(source.data_)),
        width_(source.width_),
        height_(source.height_) {
    top_left_ = Point(0, 0);
    bottom_right_ = Point(width_ - 1, height_ - 1);
  };
  Map(const T* const data, const int width, const int height)
      : width_(width), height_(height) {
    data_ = std::vector<T>();
    data_.resize(length());
    for (int i = 0; i < length(); ++i) {
      data_[i] = data[i];
    }
    top_left_ = Point(0, 0);
    bottom_right_ = Point(width_ - 1, height_ - 1);
  };

  constexpr T& At(const Point& point) const& { return data_[Pos(point)]; };
  inline T& At(const Point& point) & { return data_[Pos(point)]; };
  constexpr T At(const Point& point) const&& { return data_[Pos(point)]; };

  constexpr T& At(const int pos) const& { return data_[pos]; };
  inline T& At(const int pos) & { return data_[pos]; };
  constexpr T At(const int pos) const&& { return data_[pos]; };

  constexpr int width() const { return width_; };
  constexpr int height() const { return height_; };
  constexpr int length() const { return width_ * height_; };
  inline const Point& TopLeftPoint() const override { return top_left_; };
  inline const Point& BottomRightPoint() const override {
    return bottom_right_;
  };

 private:
  constexpr int Pos(const Point& point) const {
    return point.x() + point.y() * width();
  };
  std::vector<T> data_;
  const int width_;
  const int height_;
  Point top_left_;
  Point bottom_right_;
};

template <>
class Map<bool> : public IRectangle {
 public:
  Map(const int width, const int height) : width_(width), height_(height) {
    data_ = new bool[length()];
    top_left_ = Point(0, 0);
    bottom_right_ = Point(width_ - 1, height_ - 1);
  };
  Map(const Map<bool>& source)
      : Map(source.data_, source.width_, source.height_){};
  Map(const bool* const data, const int width, const int height)
      : width_(width), height_(height) {
    data_ = new bool[length()];
    for (int i = 0; i < length(); ++i) {
      data_[i] = data[i];
    }
    top_left_ = Point(0, 0);
    bottom_right_ = Point(width_ - 1, height_ - 1);
  };
  virtual ~Map() { delete[] data_; };
  Map<bool>& operator=(const Map<bool>& o) {
    if (this != &o) {
      delete[] data_;
      width_ = o.width_;
      height_ = o.height_;
      top_left_ = o.top_left_;
      bottom_right_ = o.bottom_right_;
      data_ = new bool[length()];
      for (int i = 0; i < length(); ++i) {
        data_[i] = o.data_[i];
      }
    }
    return *this;
  }

  constexpr bool& At(const Point& point) const& { return data_[Pos(point)]; };
  inline bool& At(const Point& point) & { return data_[Pos(point)]; };
  constexpr bool At(const Point& point) const&& { return data_[Pos(point)]; };

  constexpr bool& At(const int pos) const& { return data_[pos]; };
  inline bool& At(const int pos) & { return data_[pos]; };
  constexpr bool At(const int pos) const&& { return data_[pos]; };

  constexpr int width() const { return width_; };
  constexpr int height() const { return height_; };
  constexpr int length() const { return width_ * height_; };
  inline const Point& TopLeftPoint() const override { return top_left_; };
  inline const Point& BottomRightPoint() const override {
    return bottom_right_;
  };

 private:
  constexpr int Pos(const Point& point) const {
    return point.x() + point.y() * width();
  };
  bool* data_;
  int width_;
  int height_;
  Point top_left_;
  Point bottom_right_;
};
}  // namespace aviutl

#endif  // AVIUTL_SHARED_INCLUDE_AVIUTL_MAP_H_