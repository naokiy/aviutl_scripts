#ifndef AVIUTL_SHARED_INCLUDE_AVIUTL_POINT_RANGE_H_
#define AVIUTL_SHARED_INCLUDE_AVIUTL_POINT_RANGE_H_

#include "irectangle.h"
#include "point.h"

namespace aviutl {
class PointRange : public IRectangle {
 public:
  explicit PointRange(const IRectangle& rect)
      : PointRange(rect.TopLeftPoint(), rect.BottomRightPoint()){};
  PointRange(const Point& top_left, const Point& bottom_right)
      : PointRange(top_left, top_left, bottom_right){};
  PointRange(const Point& current, const Point& top_left,
             const Point& bottom_right)
      : current_(current), top_left_(top_left), bottom_right_(bottom_right){};

  inline PointRange begin() const {
    return PointRange(top_left_, bottom_right_);
  };

  inline PointRange end() const {
    const Point end_point = Point(top_left_.x(), bottom_right_.y() + 1);
    return PointRange(end_point, top_left_, bottom_right_);
  };

  inline const Point& operator*() noexcept { return current_; };

  inline PointRange& operator++() {
    if (current_.x() >= bottom_right_.x()) {
      current_ = Point(top_left_.x(), current_.y() + 1);
    } else {
      current_ = Point(current_.x() + 1, current_.y());
    }
    return *this;
  };

  inline const Point& current() const { return current_; }

  inline const Point& TopLeftPoint() const override { return top_left_; };
  inline const Point& BottomRightPoint() const override {
    return bottom_right_;
  };

 private:
  Point current_;
  const Point top_left_;
  const Point bottom_right_;
};

inline bool operator==(const PointRange& p1, const PointRange& p2) {
  return (p1.current() == p2.current()) &&
         (p1.TopLeftPoint() == p2.TopLeftPoint()) &&
         (p1.BottomRightPoint() == p2.BottomRightPoint());
};

inline bool operator!=(const PointRange& p1, const PointRange& p2) {
  return !(p1 == p2);
};
}  // namespace aviutl

#endif  // AVIUTL_SHARED_INCLUDE_AVIUTL_POINT_RANGE_H_