#include "aviutl/point_range.h"

#include <vector>

#include "aviutl/irectangle.h"
#include "aviutl/point.h"
#include "gtest/gtest.h"

namespace {
using namespace aviutl;

TEST(PointRangeTest, For) {
  std::vector<Point> points = {};
  for (Point p : PointRange(Point(1, 3), Point(5, 7))) {
    points.push_back(p);
  }
  EXPECT_EQ(25, static_cast<int>(points.size()));
  EXPECT_EQ(1, points[0].x());
  EXPECT_EQ(3, points[0].y());
  EXPECT_EQ(3, points[12].x());
  EXPECT_EQ(5, points[12].y());
  EXPECT_EQ(5, points[24].x());
  EXPECT_EQ(7, points[24].y());
}

TEST(PointRangeTest, ForWithRectangle) {
  class RectangleForTest : public IRectangle {
    Point top_left_ = Point(1, 3);
    Point bottom_right_ = Point(5, 7);

    inline const Point& TopLeftPoint() const override { return top_left_; };
    inline const Point& BottomRightPoint() const override {
      return bottom_right_;
    };
  };
  RectangleForTest rect = {};
  std::vector<Point> points = {};
  for (Point p : PointRange(rect)) {
    points.push_back(p);
  }
  EXPECT_EQ(25, static_cast<int>(points.size()));
  EXPECT_EQ(1, points[0].x());
  EXPECT_EQ(3, points[0].y());
  EXPECT_EQ(3, points[12].x());
  EXPECT_EQ(5, points[12].y());
  EXPECT_EQ(5, points[24].x());
  EXPECT_EQ(7, points[24].y());
}
}  // namespace