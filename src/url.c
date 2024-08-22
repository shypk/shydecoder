#include "url.h"

#include "util.h"


int url_decode_0(const char* encoded, char* decoded ) {
    unsigned len = shy_strlen(encoded);

    unsigned i, j;
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

int url_decode(const char* encoded, char* decoded ) {

    return url_decode_0(encoded, decoded);
}
