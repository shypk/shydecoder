#include "unify.h"

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


bool unify_decode_2(const char* encoded, char* decoded ) {
    size_t len = strlen(encoded);
    size_t i, j;
    for (i = 0, j = 0; i < len; i++, j++) {

        // escape_decode_2
        if (encoded[i] == '\\') {
            if (encoded[i+1] == 'x') {
                if (( '0' <= encoded[i+2] && encoded[i+2] <= '9') ||
                    ('a' <= encoded[i+2] && encoded[i+2] <= 'f') ||
                    ('A' <= encoded[i+2] && encoded[i+2] <= 'F')) {
                    if (( '0' <= encoded[i+3] && encoded[i+3] <= '9') ||
                        ('a' <= encoded[i+3] && encoded[i+3] <= 'f') ||
                        ('A' <= encoded[i+3] && encoded[i+3] <= 'F')) {
                        decoded[j] = (char)strtol_unsafe(&encoded[i+2], 2);
                        i += 3;
                    } else {
                        decoded[j] = encoded[i];
                    }
                } else {
                    decoded[j] = encoded[i];
                }
            } else if (encoded[i+1] == 'u') {
                if (( '0' <= encoded[i+2] && encoded[i+2] <= '9') ||
                    ('a' <= encoded[i+2] && encoded[i+2] <= 'f') ||
                    ('A' <= encoded[i+2] && encoded[i+2] <= 'F')) {
                    if (( '0' <= encoded[i+3] && encoded[i+3] <= '9') ||
                        ('a' <= encoded[i+3] && encoded[i+3] <= 'f') ||
                        ('A' <= encoded[i+3] && encoded[i+3] <= 'F')) {
                        if (( '0' <= encoded[i+4] && encoded[i+4] <= '9') ||
                            ('a' <= encoded[i+4] && encoded[i+4] <= 'f') ||
                            ('A' <= encoded[i+4] && encoded[i+4] <= 'F')) {
                            if (( '0' <= encoded[i+5] && encoded[i+5] <= '9') ||
                                ('a' <= encoded[i+5] && encoded[i+5] <= 'f') ||
                                ('A' <= encoded[i+5] && encoded[i+5] <= 'F')) {
                                long value = strtol_unsafe(&encoded[i+2], 4);
                                size_t len = append_unicode( decoded, j, value );
                                i += 5;
                                j += (len-1);
                            } else {
                                decoded[j] = encoded[i];
                            }
                        } else {
                            decoded[j] = encoded[i];
                        }
                    } else {
                        decoded[j] = encoded[i];
                    }
                } else {
                    decoded[j] = encoded[i];
                }
            } else if (encoded[i+1] == 'U') {
                if (( '0' <= encoded[i+2] && encoded[i+2] <= '9') ||
                    ('a' <= encoded[i+2] && encoded[i+2] <= 'f') ||
                    ('A' <= encoded[i+2] && encoded[i+2] <= 'F')) {
                    if (( '0' <= encoded[i+3] && encoded[i+3] <= '9') ||
                        ('a' <= encoded[i+3] && encoded[i+3] <= 'f') ||
                        ('A' <= encoded[i+3] && encoded[i+3] <= 'F')) {
                        if (( '0' <= encoded[i+4] && encoded[i+4] <= '9') ||
                            ('a' <= encoded[i+4] && encoded[i+4] <= 'f') ||
                            ('A' <= encoded[i+4] && encoded[i+4] <= 'F')) {
                            if (( '0' <= encoded[i+5] && encoded[i+5] <= '9') ||
                                ('a' <= encoded[i+5] && encoded[i+5] <= 'f') ||
                                ('A' <= encoded[i+5] && encoded[i+5] <= 'F')) {
                                if (( '0' <= encoded[i+6] && encoded[i+6] <= '9') ||
                                    ('a' <= encoded[i+6] && encoded[i+6] <= 'f') ||
                                    ('A' <= encoded[i+6] && encoded[i+6] <= 'F')) {
                                    if (( '0' <= encoded[i+7] && encoded[i+7] <= '9') ||
                                        ('a' <= encoded[i+7] && encoded[i+7] <= 'f') ||
                                        ('A' <= encoded[i+7] && encoded[i+7] <= 'F')) {
                                        long value = strtol_unsafe(&encoded[i+2], 6);
                                        size_t len = append_unicode( decoded, j, value );
                                        i += 7;
                                        j += (len-1);
                                    } else {
                                        decoded[j] = encoded[i];
                                    }
                                } else {
                                    decoded[j] = encoded[i];
                                }
                            } else {
                                decoded[j] = encoded[i];
                            }
                        } else {
                            decoded[j] = encoded[i];
                        }
                    } else {
                        decoded[j] = encoded[i];
                    }
                } else {
                    decoded[j] = encoded[i];
                }
            } else {
                decoded[j] = encoded[i];
            }
        } 
        
        // html_decode_2
        else if (encoded[i] == '&') {
            // major html codes
            if (strncmp(&encoded[i], "&amp;", 5) == 0) {
                decoded[j] = '&';
                i += 4;
            } else if (strncmp(&encoded[i], "&lt;", 4) == 0) {
                decoded[j] = '<';
                i += 3;
            } else if (strncmp(&encoded[i], "&gt;", 4) == 0) {
                decoded[j] = '>';
                i += 3;
            } else if (strncmp(&encoded[i], "&quot;", 6) == 0) {
                decoded[j] = '"';
                i += 5;
            } else if (strncmp(&encoded[i], "&apos;", 6) == 0) {
                decoded[j] = '\'';
                i += 5;
            } else if (strncmp(&encoded[i], "&plus;", 6) == 0) {
                decoded[j] = '+';
                i += 5;
            } else if (strncmp(&encoded[i], "&equals;", 8) == 0) {
                decoded[j] = '=';
                i += 7;
            }
            // similar html codes
             else if (strncmp(&encoded[i], "&nbsp;", 6) == 0) {
                decoded[j] = ' ';
                i += 5;
            } else if (strncmp(&encoded[i], "&minus;", 7) == 0) {
                decoded[j] = '-';
                i += 6;
            }
            // hex or decimal html codes
            else if (encoded[i+1] == '#') {
                bool found = false;

                // hex html codes
                if (encoded[i+2] == 'x') {
                    for (int k = 0; k < 7; k++) {
                        if (encoded[i+3+k] == ';') {
                            if (k == 0) {
                                break;
                            }

                            long value = strtol_unsafe(&encoded[i+3], k);
                            size_t len = append_unicode( decoded, j, value );
                            i += k+3;
                            j += (len-1);
                            
                            found = true;
                            break;
                        }

                        if (( '0' <= encoded[i+3+k] && encoded[i+3+k] <= '9') ||
                            ('a' <= encoded[i+3+k] && encoded[i+3+k] <= 'f') ||
                            ('A' <= encoded[i+3+k] && encoded[i+3+k] <= 'F')) {
                            continue;
                        } else {
                            break;
                        }

                    }
                }

                // decimal html codes
                else {
                    for (int k = 0; k < 7; k++) {
                        if (encoded[i+2+k] == ';') {
                            if (k == 0) {
                                break;
                            }

                            long value = strtol_10_unsafe(&encoded[i+2], k);
                            size_t len = append_unicode( decoded, j, value );
                            i += k+2;
                            j += (len-1);

                            found = true;
                            break;
                        }

                        if (encoded[i+2+k] < '0' || encoded[i+2+k] > '9') {
                            break;
                        }

                    }
                }
                if (found == false) {
                    decoded[j] = encoded[i];
                }

            } else {
                decoded[j] = encoded[i];
            }
        }

        // url_decode_0
        else if (encoded[i] == '+') {
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

bool unify_decode(const char* encoded, int level, char* decoded ) {
    if (level == 0) {
        return unify_decode_2(encoded, decoded);
    }

    return unify_decode_2(encoded, decoded);
}
