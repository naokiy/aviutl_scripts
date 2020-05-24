#ifndef AVIUTL_SHARED_INCLUDE_AVIUTL_POINT_H_
#define AVIUTL_SHARED_INCLUDE_AVIUTL_POINT_H_

#include "irectangle.h"

namespace aviutl {
class IRectangle;

class Point final {
 public:
  constexpr Point() : Point(0, 0){};
  constexpr Point(const Point& source) : Point(source.x(), source.y()){};
  constexpr Point(const int x, const int y) : x_(x), y_(y){};
  constexpr Point Up() const { return Point(x_, y_ - 1); };
  constexpr Point Down() const { return Point(x_, y_ + 1); };
  constexpr Point Right() const { return Point(x_ + 1, y_); };
  constexpr Point Left() const { return Point(x_ - 1, y_); };
  constexpr int x() const { return x_; };
  constexpr int y() const { return y_; };
  inline bool IsIn(const IRectangle& rect) const {
    const Point top_left = rect.TopLeftPoint();
    const Point bottom_right = rect.BottomRightPoint();
    return (x_ >= top_left.x_) && (x_ <= bottom_right.x_) &&
           (y_ >= top_left.y_) && (y_ <= bottom_right.y_);
  };

  constexpr Point& operator+=(const Point& point) {
    x_ += point.x_;
    y_ += point.y_;
    return *this;
  };

  constexpr Point& operator-=(const Point& point) {
    x_ -= point.x_;
    y_ -= point.y_;
    return *this;
  };

 private:
  int x_;
  int y_;
};

constexpr bool operator==(const Point& p1, const Point& p2) {
  return (p1.x() == p2.x()) && (p1.y() == p2.y());
};

constexpr bool operator!=(const Point& p1, const Point& p2) {
  return !(p1 == p2);
};

constexpr Point operator+(const Point& p1, const Point& p2) {
  return Point(p1) += p2;
};

constexpr Point operator-(const Point& p1, const Point& p2) {
  return Point(p1) -= p2;
};
}  // namespace aviutl

#endif  // AVIUTL_SHARED_INCLUDE_AVIUTL_POINT_H_