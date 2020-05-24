#include <mosaic_fade.h>
#include <mosaic_parameter.h>

#include <lua.hpp>


namespace mosaic_fade_lua_adapter {

int Apply(lua_State* L) {
  aviutl::RawPixel* pixels =
      reinterpret_cast<aviutl::RawPixel*>(lua_touserdata(L, 1));
  const int width = static_cast<int>(lua_tointeger(L, 2));
  const int height = static_cast<int>(lua_tointeger(L, 3));
  const int pixel_size = static_cast<int>(lua_tointeger(L, 4));
  if (pixel_size <= 0) {
    return 0;
  }
  const double transparency = static_cast<double>(lua_tonumber(L, 5));
  // const int mode = static_cast<int>(lua_tointeger(L, 6));
  const int offset_x = static_cast<int>(lua_tointeger(L, 7)) % pixel_size;
  const int offset_y = static_cast<int>(lua_tointeger(L, 8)) % pixel_size;
  const int random_seed = static_cast<int>(lua_tointeger(L, 9));

  aviutl::Image<double> image = aviutl::Image<double>(pixels, width, height);

  const MosaicParameter mosaic_parameter(pixel_size, offset_x, offset_y);

  mosaic_fade::Apply(image, mosaic_parameter, transparency, random_seed);
  image.WriteRaw(pixels);

  return 0;
}
}  // namespace mosaic_fade_lua_adapter

const luaL_Reg functions[] = {{"apply", mosaic_fade_lua_adapter::Apply},
                              {nullptr, nullptr}};

extern "C" {
__declspec(dllexport) int luaopen_MosaicFade(lua_State* L) {
  luaL_register(L, "MosaicFade", functions);
  return 1;
}
}