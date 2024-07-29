#ifdef __cplusplus
  #include "lua.hpp"
#else
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
#endif
#include <math.h>

// https://chsasank.com/lua-c-wrapping.html
// http://milkpot.sakura.ne.jp/lua/lua51_manual_ja.html
// http://milkpot.sakura.ne.jp/lua/lua52_manual_ja.html
// http://milkpot.sakura.ne.jp/lua/lua53_manual_ja.html

//so that name mangling doesn't mess up function names
#ifdef __cplusplus
extern "C"{
#endif

#include "base64.h"
#include "escape.h"
#include "html.h"
#include "swap.h"
#include "url.h"

static int s_swap(lua_State *L) {
    //check and fetch the arguments
    int arg1 = luaL_checkinteger (L, 1);
    int arg2 = luaL_checkinteger (L, 2);

    swap( &arg1, &arg2 );

    //push the results
    lua_pushnumber(L, arg1);
    lua_pushnumber(L, arg2);

    //return number of results
    return 2;
}

static int s_base64_decode(lua_State *L) {
    size_t l = 0;

    const char* target = luaL_checklstring( L, 1, &l);
    int level = luaL_checkinteger (L, 2);
    char ret[l];
    ret[0] = '\0';
    bool suc = false;
    suc = base64_decode( target, level, ret );

    //pushed string is copied and used on lua side
    lua_pushstring(L, ret);
    lua_pushboolean(L, suc);

    return 2;
}


static int s_escape_decode(lua_State *L) {
    size_t l = 0;

    const char* target = luaL_checklstring( L, 1, &l);
    int level = luaL_checkinteger (L, 2);
    char ret[l];
    ret[0] = '\0';
    bool suc = false;
    suc = escape_decode( target, level, ret );

    //pushed string is copied and used on lua side
    lua_pushstring(L, ret);
    lua_pushboolean(L, suc);

    return 2;
}

static int s_html_decode(lua_State *L) {
    size_t l = 0;

    const char* target = luaL_checklstring( L, 1, &l);
    int level = luaL_checkinteger (L, 2);
    char ret[l];
    ret[0] = '\0';
    bool suc = false;
    suc = html_decode( target, level, ret );

    //pushed string is copied and used on lua side
    lua_pushstring(L, ret);
    lua_pushboolean(L, suc);

    return 2;
}


static int s_url_decode(lua_State *L) {
    size_t l = 0;

    const char* target = luaL_checklstring( L, 1, &l);
    int level = luaL_checkinteger (L, 2);
    char ret[l];
    ret[0] = '\0';
    bool suc = false;
    suc = url_decode( target, level, ret );

    //pushed string is copied and used on lua side
    lua_pushstring(L, ret);
    lua_pushboolean(L, suc);

    return 2;
}

//library to be registered
static const struct luaL_Reg mylib [] = {
      {"swap", s_swap},
      {"base64_decode", s_base64_decode},
      {"escape_decode", s_escape_decode},
      {"html_decode", s_html_decode},
      {"url_decode", s_url_decode},
      {NULL, NULL}  /* sentinel */
    };

//name of this function is not flexible
int luaopen_shydecoder(lua_State *L){
    luaL_newlib(L, mylib);
    return 1;
}

#ifdef __cplusplus
}
#endif
