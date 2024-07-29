#ifdef __cplusplus
extern "C"{
#endif
#include <cstddef>

long strtol_unsafe( const char* str, int len );
long strtol_10_unsafe( const char* str, int len );
bool unicode_to_hex(long unicode, char* str, bool reverse);
size_t append_unicode(char* str, size_t index, long unicode);

#ifdef __cplusplus
}
#endif
