#include "aviutl/map.h"

#include "gtest/gtest.h"
#include "aviutl/point.h"

namespace {
    using namespace aviutl;

    TEST(MapTest, FromArray) {
        const double values[4] = {10.0, 20.0, 30.0, 40.0};
        const int width = 2;
        const int height = 2;
        Map<double> map_a = Map<double>(values, width, height);
        EXPECT_DOUBLE_EQ(10.0, map_a.At(0));
        EXPECT_DOUBLE_EQ(20.0, map_a.At(1));
        EXPECT_DOUBLE_EQ(30.0, map_a.At(2));
        EXPECT_DOUBLE_EQ(40.0, map_a.At(3));
    }

    TEST(MapTest, CopyConstructor) {
        const double values[4] = {10.0, 20.0, 30.0, 40.0};
        const int width = 2;
        const int height = 2;
        Map<double> map_a = Map<double>(values, width, height);
        EXPECT_DOUBLE_EQ(10.0, map_a.At(0));
        EXPECT_DOUBLE_EQ(20.0, map_a.At(1));
        EXPECT_DOUBLE_EQ(30.0, map_a.At(2));
        EXPECT_DOUBLE_EQ(40.0, map_a.At(3));

        Map<double> map_b = Map<double>(map_a);
        EXPECT_DOUBLE_EQ(10.0, map_b.At(0));
        EXPECT_DOUBLE_EQ(20.0, map_b.At(1));
        EXPECT_DOUBLE_EQ(30.0, map_b.At(2));
        EXPECT_DOUBLE_EQ(40.0, map_b.At(3));
    }

    TEST(MapBoolTest, CopyConstructor) {
        const bool values[4] = {false, true, true, false};
        const int width = 2;
        const int height = 2;
        Map<bool> map_a = Map<bool>(values, width, height);
        EXPECT_FALSE(map_a.At(0));
        EXPECT_TRUE(map_a.At(1));
        EXPECT_TRUE(map_a.At(2));
        EXPECT_FALSE(map_a.At(3));

        Map<bool> map_b = Map<bool>(map_a);
        EXPECT_FALSE(map_b.At(0));
        EXPECT_TRUE(map_b.At(1));
        EXPECT_TRUE(map_b.At(2));
        EXPECT_FALSE(map_b.At(3));
    }

    TEST(MapTest, SetValueAt) {
        const int width = 2;
        const int height = 2;
        const Point point = Point(1,1);
        Map<double> map = Map<double>(width, height);
        map.At(point) = 20.0;
        EXPECT_DOUBLE_EQ(20.0, map.At(point));
    }

    TEST(MapBoolTest, SetValueAt) {
        const int width = 2;
        const int height = 2;
        const Point point = Point(1,1);
        Map<bool> map = Map<bool>(width, height);
        map.At(point) = true;
        EXPECT_TRUE(map.At(point));
    }

    TEST(MapTest, AddValueAt) {
        const int width = 2;
        const int height = 2;
        const Point point = Point(1,1);
        Map<double> map = Map<double>(width, height);
        map.At(point) += 20.0;
        EXPECT_DOUBLE_EQ(20.0, map.At(point));
    }

    TEST(MapTest, AsRectangle) {
        const int width = 200;
        const int height = 300;

        const Map<double> map = Map<double>(width, height);
        const Point top_left = map.TopLeftPoint();
        const Point bottom_right = map.BottomRightPoint();
        
        EXPECT_EQ(0, top_left.x());
        EXPECT_EQ(0, top_left.y());
        EXPECT_EQ(199, bottom_right.x());
        EXPECT_EQ(299, bottom_right.y()); 
    }
}