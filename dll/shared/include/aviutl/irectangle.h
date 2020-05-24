#ifndef AVIUTL_SHARED_INCLUDE_AVIUTL_IRECTANGLE_H_
#define AVIUTL_SHARED_INCLUDE_AVIUTL_IRECTANGLE_H_

namespace aviutl {
class Point;

class IRectangle {
 public:
  virtual inline const Point& TopLeftPoint() const = 0;
  virtual inline const Point& BottomRightPoint() const = 0;
};
}  // namespace aviutl

#endif  // AVIUTL_SHARED_INCLUDE_AVIUTL_IRECTANGLE_H_
