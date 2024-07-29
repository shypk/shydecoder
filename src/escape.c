#include "escape.h"

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


bool escape_decode_2(const char* encoded, char* decoded ) {
    size_t len = strlen(encoded);
    size_t i, j;
    for (i = 0, j = 0; i < len; i++, j++) {
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
        } else {
            decoded[j] = encoded[i];
        }
    }
    decoded[j] = '\0';
    return true;
}

bool escape_decode_1(const char* encoded, char* decoded ) {
    size_t len = strlen(encoded);
    size_t i, j;
    for (i = 0, j = 0; i < len; i++, j++) {
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
            } else {
                decoded[j] = encoded[i];
            }
        } else {
            decoded[j] = encoded[i];
        }
    }
    decoded[j] = '\0';
    return true;
}

bool escape_decode_0(const char* encoded, char* decoded ) {
    size_t len = strlen(encoded);

    size_t i, j;
    for (i = 0, j = 0; i < len; i++, j++) {
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
            } else {
                decoded[j] = encoded[i];
            }
        } else {
            decoded[j] = encoded[i];
        }
    }
    decoded[j] = '\0';
    return true;
}

bool escape_decode(const char* encoded, int level, char* decoded ) {
    if (level == 0) {
        return escape_decode_0(encoded, decoded);
    } else if (level == 1) {
        return escape_decode_1(encoded, decoded);
    } else if (level == 2) {
        return escape_decode_2(encoded, decoded);
    } else {
        return escape_decode_0(encoded, decoded);
    }

    return false;
}
