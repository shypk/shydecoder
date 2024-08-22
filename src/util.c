#include "util.h"

long shy_strncpy(char* str1, const char* str2, long len) {
    for (long i = 0; i < len; i++) {
        str1[i] = str2[i];
        if (str2[i] == '\0') {
            return i;
        }
    }
    return len;
}

long shy_strncmp(const char* str1, const char* str2, long len) {
    for (long i = 0; i < len; i++) {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
    }
    return 0;
}

long shy_strlen(const char* str) {
    long len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

long strtol_unsafe( const char* str, int len ){
    //                    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
	const int maptbl[256] =   {
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0,
                            0,10,11,12,13,14,15, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0,10,11,12,13,14,15, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            };
	long acc = 0;
    for(int i = 0; i < len; i++ ){
        acc <<= 4;
        acc += maptbl[ (int) str[i] ];
    }
    return acc;
}

long strtol_10_unsafe( const char* str, int len ){
    //                    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
	const int maptbl[256] =   {
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            };
	long acc = 0;
    for(int i = 0; i < len; i++ ){
        acc *= 10;
        acc += maptbl[ (int) str[i] ];
    }
    return acc;
}

int unicode_to_hex(long unicode, char* str, int reverse) {
    if (unicode < 0x80) {
        str[0] = unicode;
        str[1] = '\0';
        return true;
    } else if (unicode < 0x800) {
        str[0] = 0xC0 | (unicode >> 6);
        str[1] = 0x80 | (unicode & 0x3F);
        str[2] = '\0';

        if( reverse ) {
            unsigned char temp = str[0];
            str[0] = str[1];
            str[1] = temp;
        }
        return true;
    } else if (unicode < 0x10000) {
        str[0] = 0xE0 | (unicode >> 12);
        str[1] = 0x80 | ((unicode >> 6) & 0x3F);
        str[2] = 0x80 | (unicode & 0x3F);
        str[3] = '\0';

        if( reverse ) {
            unsigned char temp = str[0];
            str[0] = str[2];
            str[2] = temp;
        }
        return true;
    } else if (unicode < 0x200000) {
        str[0] = 0xF0 | (unicode >> 18);
        str[1] = 0x80 | ((unicode >> 12) & 0x3F);
        str[2] = 0x80 | ((unicode >> 6) & 0x3F);
        str[3] = 0x80 | (unicode & 0x3F);
        str[4] = '\0';

        if( reverse ) {
            for (int i = 0; i < 2; i++) {
                unsigned char temp = str[i];
                str[i] = str[3 - i];
                str[3 - i] = temp;
            }
        }

        return true;
    } else if (unicode < 0x4000000) {
        str[0] = 0xF8 | (unicode >> 24);
        str[1] = 0x80 | ((unicode >> 18) & 0x3F);
        str[2] = 0x80 | ((unicode >> 12) & 0x3F);
        str[3] = 0x80 | ((unicode >> 6) & 0x3F);
        str[4] = 0x80 | (unicode & 0x3F);
        str[5] = '\0';

        if( reverse ) {
            for (int i = 0; i < 2; i++) {
                unsigned char temp = str[i];
                str[i] = str[4 - i];
                str[4 - i] = temp;
            }
        }

        return true;
    } else if (unicode < 0x80000000) {
        str[0] = 0xFC | (unicode >> 30);
        str[1] = 0x80 | ((unicode >> 24) & 0x3F);
        str[2] = 0x80 | ((unicode >> 18) & 0x3F);
        str[3] = 0x80 | ((unicode >> 12) & 0x3F);
        str[4] = 0x80 | ((unicode >> 6) & 0x3F);
        str[5] = 0x80 | (unicode & 0x3F);
        str[6] = '\0';

        // Swap bytes if the system is big endian
        if( reverse ) {
            for (int i = 0; i < 3; i++) {
                unsigned char temp = str[i];
                str[i] = str[5 - i];
                str[5 - i] = temp;
            }
        }

        return true;

    }


    return false;
}

unsigned append_unicode(char* str, unsigned index, long unicode) {
    char hex[7];
    unicode_to_hex(unicode, hex, false);
    unsigned len = shy_strlen(hex);
    for (unsigned i = 0; i < len; i++) {
        str[index + i] = hex[i];
    }
    return len;
}
