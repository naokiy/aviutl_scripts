#include <error_diffusion_dither.h>

#include <lua.hpp>

namespace error_diffusion_dither_lua_adapter {
int Apply(lua_State *L) {
  aviutl::RawPixel *pixels =
      reinterpret_cast<aviutl::RawPixel *>(lua_touserdata(L, 1));
  const int width = static_cast<int>(lua_tointeger(L, 2));
  const int height = static_cast<int>(lua_tointeger(L, 3));
  const int level = static_cast<int>(lua_tointeger(L, 4));

  aviutl::Image<double> image = aviutl::Image<double>(pixels, width, height);

  error_diffusion_dither::Apply(image, level);

  image.WriteRaw(pixels);

  return 0;
}
}  // namespace error_diffusion_dither_lua_adapter

const luaL_Reg functions[] = {
    {"apply", error_diffusion_dither_lua_adapter::Apply}, {nullptr, nullptr}};

extern "C" {
__declspec(dllexport) int luaopen_ErrorDiffusionDither(lua_State *L) {
  luaL_register(L, "ErrorDiffusionDither", functions);
  return 1;
}
}