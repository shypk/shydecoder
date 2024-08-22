#ifdef __cplusplus
extern "C"{
#endif

#define true 1
#define false 0

long shy_strncpy(char* str1, const char* str2, long len);
long shy_strncmp(const char* str1, const char* str2, long len);
long shy_strlen(const char* str);
long strtol_unsafe( const char* str, int len );
long strtol_10_unsafe( const char* str, int len );
int unicode_to_hex(long unicode, char* str, int reverse);
unsigned append_unicode(char* str, unsigned index, long unicode);

#ifdef __cplusplus
}
#endif
