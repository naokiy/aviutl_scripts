#include "aviutl/image.h"

#include <iostream>

#include "gtest/gtest.h"
#include "aviutl/point.h"

namespace {
    using namespace aviutl;


    TEST(ImageTest, BlankImageSize) {
        const int width = 200;
        const int height = 128;

        Image<double> image = Image<double>(width, height);

        EXPECT_EQ(200, image.width());
        EXPECT_EQ(128, image.height());
    }

    TEST(ImageTest, BlankImageWillBeInitializedByBlack) {
        const int width = 3;
        const int height = 4;

        Image<double> image = Image<double>(width, height);
        Pixel<double> pixel = image.At(Point(1,1));

        EXPECT_DOUBLE_EQ(0.0, pixel.r);
        EXPECT_DOUBLE_EQ(0.0, pixel.g);
        EXPECT_DOUBLE_EQ(0.0, pixel.b);
        EXPECT_DOUBLE_EQ(0.0, pixel.a); 
    }

    TEST(ImageTest, CreateFromRawImage) {
        const RawPixel raw_pixels[4] = {{10,20,30,40}, {1,2,3,4}, {5,6,7,8}, {110,120,130,140}};
        const int width = 2;
        const int height = 2;

        Image<double> image = Image<double>(raw_pixels, width, height);
        Pixel<double> pixel_at_top_left = image.At(Point(0,0));

        EXPECT_DOUBLE_EQ(30.0, pixel_at_top_left.r);
        EXPECT_DOUBLE_EQ(20.0, pixel_at_top_left.g);
        EXPECT_DOUBLE_EQ(10.0, pixel_at_top_left.b);
        EXPECT_DOUBLE_EQ(40.0, pixel_at_top_left.a); 
    }

    TEST(ImageTest, SetPixelAt) {
        const int width = 2;
        const int height = 2;

        Image<double> image = Image<double>(width, height);
        const Pixel<double> pixel = Pixel<double>(10.0,20.0,30.0,40.0);
        const Point point = Point(1, 1);

        image.At(point) = pixel;

        const Pixel<double> loaded_pixel = image.At(point);

        EXPECT_DOUBLE_EQ(10.0, loaded_pixel.r);
        EXPECT_DOUBLE_EQ(20.0, loaded_pixel.g);
        EXPECT_DOUBLE_EQ(30.0, loaded_pixel.b);
        EXPECT_DOUBLE_EQ(40.0, loaded_pixel.a);
    }

    TEST(ImageTest, SetChannelValueAt) {
        const int width = 2;
        const int height = 2;

        Image<double> image = Image<double>(width, height);
        const Point point = Point(1, 1);

        image.At(point).r = 100.0;
        image.At(point).g = 110.0;
        image.At(point).b = 120.0;
        image.At(point).a = 130.0;
        
        const Pixel<double> loaded_pixel = image.At(point);

        EXPECT_DOUBLE_EQ(100.0, loaded_pixel.r);
        EXPECT_DOUBLE_EQ(110.0, loaded_pixel.g);
        EXPECT_DOUBLE_EQ(120.0, loaded_pixel.b);
        EXPECT_DOUBLE_EQ(130.0, loaded_pixel.a);
    }

    
    TEST(ImageTest, AddPixelAt) {
        const int width = 2;
        const int height = 2;

        Image<double> image = Image<double>(width, height);
        const Pixel<double> pixel = Pixel<double>(10.0,20.0,30.0,40.0);
        const Point point = Point(1, 1);

        image.At(point) += pixel;

        const Pixel<double> loaded_pixel = image.At(point);

        EXPECT_DOUBLE_EQ(10.0, loaded_pixel.r);
        EXPECT_DOUBLE_EQ(20.0, loaded_pixel.g);
        EXPECT_DOUBLE_EQ(30.0, loaded_pixel.b);
        EXPECT_DOUBLE_EQ(40.0, loaded_pixel.a);
    }

    TEST(ImageTest, AsRectangle) {
        const int width = 200;
        const int height = 300;

        const Image<double> image = Image<double>(width, height);
        const Point top_left = image.TopLeftPoint();
        const Point bottom_right = image.BottomRightPoint();
        
        EXPECT_EQ(0, top_left.x());
        EXPECT_EQ(0, top_left.y());
        EXPECT_EQ(199, bottom_right.x());
        EXPECT_EQ(299, bottom_right.y()); 
    }
}