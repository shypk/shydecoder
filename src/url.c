#include "url.h"

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


bool url_decode_0(const char* encoded, char* decoded ) {
    size_t len = strlen(encoded);

    size_t i, j;
    for (i = 0, j = 0; i < len; i++, j++) {
        if (encoded[i] == '+') {
            decoded[j] = ' ';
        } 
        else if (encoded[i] == '%') {
            if (( '0' <= encoded[i+1] && encoded[i+1] <= '9') ||
                ('a' <= encoded[i+1] && encoded[i+1] <= 'f') ||
                ('A' <= encoded[i+1] && encoded[i+1] <= 'F')) {
                if (( '0' <= encoded[i+2] && encoded[i+2] <= '9') ||
                    ('a' <= encoded[i+2] && encoded[i+2] <= 'f') ||
                    ('A' <= encoded[i+2] && encoded[i+2] <= 'F')) {
                    decoded[j] = (char)strtol_unsafe(&encoded[i+1], 2);
                    i += 2;
                } else {
                    decoded[j] = encoded[i];
                }
            } else {
                decoded[j] = encoded[i];
            }
        } 
        else {
            decoded[j] = encoded[i];
        }
    }
    decoded[j] = '\0';
    return true;
}

bool url_decode(const char* encoded, int level, char* decoded ) {
    if (level == 0) {
        return url_decode_0(encoded, decoded);
    } else {
        return url_decode_0(encoded, decoded);
    }

    return false;
}
