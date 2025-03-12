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
#include "unify.h"

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
    char ret[l];
    ret[0] = '\0';
    bool suc = false;
    suc = base64_decode( target, ret );

    //pushed string is copied and used on lua side
    lua_pushstring(L, ret);
    lua_pushboolean(L, suc);

    return 2;
}

static int s_base64_decode_safe(lua_State *L) {
    size_t l = 0;

    const char* target = luaL_checklstring( L, 1, &l);
    char ret[l];
    ret[0] = '\0';
    bool suc = false;
    suc = base64_decode_safe( target, ret );

    //pushed string is copied and used on lua side
    lua_pushstring(L, ret);
    lua_pushboolean(L, suc);

    return 2;
}

static int s_base64_decode_forced(lua_State *L) {
    size_t l = 0;

    const char* target = luaL_checklstring( L, 1, &l);
    char ret[l];
    ret[0] = '\0';
    bool suc = false;
    suc = base64_decode_forced( target, ret );

    //pushed string is copied and used on lua side
    lua_pushstring(L, ret);
    lua_pushboolean(L, suc);

    return 2;
}

static int s_base64_find_and_decode(lua_State *L) {
    size_t l = 0;

    const char* target = luaL_checklstring( L, 1, &l);
    int offset = luaL_checkinteger (L, 2);
    char ret[l];
    int decoded_len = 0;
    ret[decoded_len] = '\0';
    int next = -1;
    next = base64_find_and_decode( target, ret, offset, &decoded_len );

    //pushed string is copied and used on lua side
    lua_pushstring(L, ret);
    lua_pushnumber(L, decoded_len);
    lua_pushnumber(L, next);

    return 3;
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
    char ret[l];
    ret[0] = '\0';
    bool suc = false;
    suc = url_decode( target, ret );

    //pushed string is copied and used on lua side
    lua_pushstring(L, ret);
    lua_pushboolean(L, suc);

    return 2;
}

static int s_unify_decode(lua_State *L) {
    size_t l = 0;

    const char* target = luaL_checklstring( L, 1, &l);
    int level = luaL_checkinteger (L, 2);
    char ret[l];
    ret[0] = '\0';
    bool suc = false;
    suc = unify_decode( target, level, ret );

    //pushed string is copied and used on lua side
    lua_pushstring(L, ret);
    lua_pushboolean(L, suc);

    return 2;
}

//library to be registered
static const struct luaL_Reg mylib [] = {
      {"swap", s_swap},
      {"base64_decode", s_base64_decode},
      {"base64_decode_safe", s_base64_decode_safe},
      {"base64_decode_forced", s_base64_decode_forced},
      {"base64_find_and_decode", s_base64_find_and_decode},
      {"escape_decode", s_escape_decode},
      {"html_decode", s_html_decode},
      {"url_decode", s_url_decode},
      {"unify_decode", s_unify_decode},
      {NULL, NULL}  /* sentinel */
    };

//name of this function is not flexible
int luaopen_shydecoder(lua_State *L){
    luaL_register(L, "shydecoder", mylib);
    return 1;
}

#ifdef __cplusplus
}
#endif
