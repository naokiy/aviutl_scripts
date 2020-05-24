#ifndef AVIUTL_SHARED_INCLUDE_AVIUTL_PIXEL_H_
#define AVIUTL_SHARED_INCLUDE_AVIUTL_PIXEL_H_

#include <cassert>
#include <cstdint>

namespace aviutl {
struct RawPixel {
  uint8_t b;
  uint8_t g;
  uint8_t r;
  uint8_t a;
};

enum class Channel {
  R = 2,
  G = 1,
  B = 0,
  A = 3,
};

static const Channel RGBA_Channels[] = {Channel::R, Channel::G, Channel::B,
                                        Channel::A};
static const Channel RGB_Channels[] = {Channel::R, Channel::G, Channel::B};

template <typename T>
class Pixel {
 public:
  T r;
  T g;
  T b;
  T a;
  constexpr explicit Pixel(const RawPixel& raw)
      : Pixel(static_cast<T>(raw.r), static_cast<T>(raw.g),
              static_cast<T>(raw.b), static_cast<T>(raw.a)){};
  template <typename U>
  constexpr explicit Pixel(const Pixel<U>& s) : Pixel(s.r, s.g, s.b, s.a){};
  constexpr Pixel() : Pixel(0, 0, 0, 0){};
  constexpr Pixel(const T& _r, const T& _g, const T& _b, const T& _a)
      : r(_r), g(_g), b(_b), a(_a){};
  inline RawPixel ToRaw() const {
    return RawPixel{
        static_cast<uint8_t>(b),
        static_cast<uint8_t>(g),
        static_cast<uint8_t>(r),
        static_cast<uint8_t>(a),
    };
  };

  template <typename U>
  constexpr Pixel<T>& operator+=(const Pixel<U>& _pixel) {
    b += static_cast<T>(_pixel.b);
    g += static_cast<T>(_pixel.g);
    r += static_cast<T>(_pixel.r);
    a += static_cast<T>(_pixel.a);
    return *this;
  };
  template <typename U>
  constexpr Pixel<T>& operator-=(const Pixel<U>& _pixel) {
    b -= static_cast<T>(_pixel.b);
    g -= static_cast<T>(_pixel.g);
    r -= static_cast<T>(_pixel.r);
    a -= static_cast<T>(_pixel.a);
    return *this;
  };
  template <>
  constexpr Pixel<T>& operator+=<T>(const Pixel<T>& _pixel) {
    b += _pixel.b;
    g += _pixel.g;
    r += _pixel.r;
    a += _pixel.a;
    return *this;
  };
  template <>
  constexpr Pixel<T>& operator-=<T>(const Pixel<T>& _pixel) {
    b -= _pixel.b;
    g -= _pixel.g;
    r -= _pixel.r;
    a -= _pixel.a;
    return *this;
  };

  constexpr Pixel<T>& operator*=(const double& multiplier) {
    b *= multiplier;
    g *= multiplier;
    r *= multiplier;
    a *= multiplier;
    return *this;
  };
  constexpr Pixel<T>& operator/=(const double& divisor) {
    b /= divisor;
    g /= divisor;
    r /= divisor;
    a /= divisor;
    return *this;
  };

  inline T GetChannelValue(const Channel& channel) const {
    switch (channel) {
      case Channel::R:
        return r;
      case Channel::G:
        return g;
      case Channel::B:
        return b;
      case Channel::A:
        return a;
    }
    assert(false);
    return 0;
  }

  inline void SetChannelValue(const Channel& channel, const T& value) {
    switch (channel) {
      case Channel::R:
        r = value;
        break;
      case Channel::G:
        g = value;
        break;
      case Channel::B:
        b = value;
        break;
      case Channel::A:
        a = value;
        break;
    }
  }
};

template <typename T>
constexpr Pixel<T> operator*(const Pixel<T>& t1, const double t2) {
  return Pixel<T>(t1) *= t2;
};
template <typename T>
constexpr Pixel<T> operator/(const Pixel<T>& t1, const double t2) {
  return Pixel<T>(t1) /= t2;
};
template <typename T, typename U>
constexpr Pixel<T> operator+(const Pixel<T>& t1, const Pixel<U>& t2) {
  return Pixel<T>(t1) += t2;
};
template <typename T, typename U>
constexpr Pixel<T> operator-(const Pixel<T>& t1, const Pixel<U>& t2) {
  return Pixel<T>(t1) -= t2;
};
}  // namespace aviutl

#endif  // AVIUTL_SHARED_INCLUDE_AVIUTL_PIXEL_H_
