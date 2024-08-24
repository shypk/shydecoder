#ifdef __cplusplus
extern "C"{
#endif

#define true 1
#define false 0

unsigned int shy_strncpy(char* str1, const char* str2, unsigned int len);
int shy_strncmp(const char* str1, const char* str2, unsigned int len);
unsigned int shy_strlen(const char* str);
long strtol_unsafe( const char* str, unsigned int len );
long strtol_10_unsafe( const char* str, unsigned int len );
unsigned unicode_to_hex(long unicode, char* str, int reverse);
unsigned append_unicode(char* str, unsigned index, long unicode);

#ifdef __cplusplus
}
#endif
