#ifdef __cplusplus
extern "C"{
#endif

bool base64_decode(const char* encoded, char* decoded );
bool base64_decode_safe(const char* encoded, char* decoded );

#ifdef __cplusplus
}
#endif
