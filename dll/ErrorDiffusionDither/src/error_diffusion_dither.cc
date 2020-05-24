#include "error_diffusion_dither.h"

#include "aviutl.h"
#include "closest_color_finder.h"


namespace error_diffusion_dither {
void Apply(aviutl::Image<double> &image, const int level) {
  ClosestColorFinder finder = ClosestColorFinder(level);
  for (const aviutl::Point &point : aviutl::PointRange(image)) {
    const aviutl::Pixel<double> pixel = image.At(point);
    const aviutl::Pixel<double> new_pixel = finder(pixel);
    const aviutl::Pixel<double> error = pixel - new_pixel;

    image.At(point) = new_pixel;

    const aviutl::Point point_right = point.Right();
    if (point_right.IsIn(image)) {
      image.At(point_right) += (error * (7.0 / 16));
    }

    const aviutl::Point point_down_left = point.Down().Left();
    if (point_down_left.IsIn(image)) {
      image.At(point_down_left) += (error * (3.0 / 16));
    }

    const aviutl::Point point_down = point.Down();
    if (point_down.IsIn(image)) {
      image.At(point_down) += (error * (5.0 / 16));
    }

    const aviutl::Point point_down_right = point.Down().Right();
    if (point_down_right.IsIn(image)) {
      image.At(point_down_right) += (error * (1.0 / 16));
    }
  }
};
}  // namespace error_diffusion_dither