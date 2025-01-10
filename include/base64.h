#ifdef __cplusplus
extern "C"{
#endif

int base64_decode(const char* encoded, char* decoded );
int base64_decode_safe(const char* encoded, char* decoded );
int base64_decode_forced(const char* encoded, char* decoded );

#ifdef __cplusplus
}
#endif
