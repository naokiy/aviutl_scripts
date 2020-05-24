#include "aviutl/point.h"

#include "gtest/gtest.h"
#include "aviutl/irectangle.h"

namespace {
    using namespace aviutl;

    TEST(PointTest, Constructor) {
        const Point p = Point(1,2);
        EXPECT_EQ(1, p.x());
        EXPECT_EQ(2, p.y());
    }

    TEST(PointTest, Equation) {
        const Point p1 = Point(1,2);
        const Point p2 = Point(1,2);
        EXPECT_TRUE(p1 == p2);
    }

    TEST(PointTest, Inequation) {
        const Point p1 = Point(1,2);
        const Point p2 = Point(2,1);
        EXPECT_TRUE(p1 != p2);
    }

    TEST(PointTest, IsIn) {
        class RectangleForTest: public IRectangle {
            Point top_left_ = Point(10, 20);
            Point bottom_right_ = Point(40, 50);
            
            inline const Point& TopLeftPoint() const override { return top_left_; };
            inline const Point& BottomRightPoint() const override { return bottom_right_; };
        };
        RectangleForTest rect = {};
        EXPECT_TRUE(Point(10, 20).IsIn(rect));
        EXPECT_FALSE(Point(9, 20).IsIn(rect));
        EXPECT_FALSE(Point(10, 19).IsIn(rect));
        EXPECT_TRUE(Point(40, 50).IsIn(rect));
        EXPECT_FALSE(Point(41, 50).IsIn(rect));
        EXPECT_FALSE(Point(40, 51).IsIn(rect));
    }
}