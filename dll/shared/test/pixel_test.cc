#include "aviutl/pixel.h"

#include "gtest/gtest.h"

namespace {
    using namespace aviutl;

    TEST(PixelTest, BlankConstructor) {
        Pixel<double> pixel = Pixel<double>();
        pixel.r = 70.0;
        pixel.g = 80.0;
        pixel.b = 90.0;
        pixel.a = 100.0;
        EXPECT_DOUBLE_EQ(70.0, pixel.r);
        EXPECT_DOUBLE_EQ(80.0, pixel.g);
        EXPECT_DOUBLE_EQ(90.0, pixel.b);
        EXPECT_DOUBLE_EQ(100.0, pixel.a);
    }


    TEST(PixelTest, RawPixelToPixel) {
        const RawPixel raw_pixel = {10,20,30,40};
        const Pixel<double> pixel = Pixel<double>(raw_pixel);
        EXPECT_DOUBLE_EQ(30.0, pixel.r);
        EXPECT_DOUBLE_EQ(20.0, pixel.g);
        EXPECT_DOUBLE_EQ(10.0, pixel.b);
        EXPECT_DOUBLE_EQ(40.0, pixel.a);
    }

    TEST(PixelTest, PixelToRawPixel) {
        const Pixel<double> pixel = Pixel<double>(10.0,20.0,30.0,40.0);
        const RawPixel raw_pixel = pixel.ToRaw();
        EXPECT_EQ(10, raw_pixel.r);
        EXPECT_EQ(20, raw_pixel.g);
        EXPECT_EQ(30, raw_pixel.b);
        EXPECT_EQ(40, raw_pixel.a);    
    }

    TEST(PixelTest, Addition) {
        const Pixel<double> pixel_a = Pixel<double>(10.0,20.0,30.0,40.0);
        const Pixel<double> pixel_b = Pixel<double>(1.1,2.2,3.3,4.4);
        const Pixel<double> pixel = pixel_a + pixel_b;

        EXPECT_DOUBLE_EQ(11.1, pixel.r);
        EXPECT_DOUBLE_EQ(22.2, pixel.g);
        EXPECT_DOUBLE_EQ(33.3, pixel.b);
        EXPECT_DOUBLE_EQ(44.4, pixel.a);    
    }

    TEST(PixelTest, AdditionAssignment) {
        Pixel<double> pixel = Pixel<double>(10.0,20.0,30.0,40.0);
        const Pixel<double> pixel_a = Pixel<double>(1.1,2.2,3.3,4.4);
        pixel += pixel_a;

        EXPECT_DOUBLE_EQ(11.1, pixel.r);
        EXPECT_DOUBLE_EQ(22.2, pixel.g);
        EXPECT_DOUBLE_EQ(33.3, pixel.b);
        EXPECT_DOUBLE_EQ(44.4, pixel.a);    
    }

    TEST(PixelTest, Subtraction) {
        const Pixel<double> pixel_a = Pixel<double>(11.1,22.2,33.3,44.4);
        const Pixel<double> pixel_b = Pixel<double>(1.1,2.2,3.3,4.4);
        const Pixel<double> pixel = pixel_a - pixel_b;

        EXPECT_DOUBLE_EQ(10.0, pixel.r);
        EXPECT_DOUBLE_EQ(20.0, pixel.g);
        EXPECT_DOUBLE_EQ(30.0, pixel.b);
        EXPECT_DOUBLE_EQ(40.0, pixel.a);    
    }

    TEST(PixelTest, Multiplication) {
        const Pixel<double> pixel = Pixel<double>(1.0,2.0,3.0,4.0);
        const double multiplier = 2.5;
        const Pixel<double> pixel_m = pixel * multiplier;

        EXPECT_DOUBLE_EQ(2.5, pixel_m.r);
        EXPECT_DOUBLE_EQ(5.0, pixel_m.g);
        EXPECT_DOUBLE_EQ(7.5, pixel_m.b);
        EXPECT_DOUBLE_EQ(10.0, pixel_m.a);    
    }

    TEST(PixelTest, Division) {
        const Pixel<double> pixel = Pixel<double>(10.0,20.0,30.0,40.0);
        const double divisor = 2.5;
        const Pixel<double> pixel_d = pixel / divisor;

        EXPECT_DOUBLE_EQ(4.0, pixel_d.r);
        EXPECT_DOUBLE_EQ(8.0, pixel_d.g);
        EXPECT_DOUBLE_EQ(12.0, pixel_d.b);
        EXPECT_DOUBLE_EQ(16.0, pixel_d.a);    
    }
}