#ifdef __cplusplus
extern "C"{
#endif

int base64_decode(const char* encoded, char* decoded );
int base64_decode_safe(const char* encoded, char* decoded );
int base64_decode_forced(const char* encoded, char* decoded );
int base64_find_and_decode(const char* encoded, char* decoded, int offset, int* decoded_len );
int base64_decode_extract(const char* encoded, char* decoded, char sep );

#ifdef __cplusplus
}
#endif
