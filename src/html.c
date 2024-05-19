#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "html.h"

// html code table

// hex dec chr html       level 
// 20  32      &nbsp;          2       // nbsp is xA0 not a x20
// 21  33  !
// 22  34  "   &quot;      0
// 23  35  #
// 24  36  $
// 25  37  %
// 26  38  &   &amp;       0
// 27  39  '   &apos;      0
// 28  40  (
// 29  41  )
// 2A  42  *
// 2B  43  +   &plus;      0
// 2C  44  ,
// 2D  45  -   &minus;         2       // minus is x2212 not a x2D
// 2E  46  .
// 2F  47  /
// 3A  58  :
// 3B  59  ;
// 3C  60  <   &lt;        0
// 3D  61  =   &equals;    0
// 3E  62  >   &gt;        0
// 3F  63  ?
// 40  64  @
// 5B  91  [
// 5C  92  \
// 5D  93  ]
// 5E  94  ^
// 5F  95  _
// 60  96  `
// 7B  123 {
// 7C  124 |
// 7D  125 }
// 7E  126 ~



bool html_decode_2(const char* encoded, char* decoded ) {
    size_t len = strlen(encoded);

    size_t i, j;
    for (i = 0, j = 0; i < len; i++, j++) {
        if (encoded[i] == '&') {
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
                    for (int k = 0; k < 6; k++) {
                        if (encoded[i+3+k] == ';') {
                            if (k == 0) {
                                break;
                            }
                            char hex[k+1];
                            strncpy(hex, &encoded[i+3], k);
                            hex[k] = '\0';
                            int value = strtol(hex, NULL, 16);
                            decoded[j] = (char)value;
                            i += k+3;
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
                    for (int k = 0; k < 6; k++) {
                        if (encoded[i+2+k] == ';') {
                            if (k == 0) {
                                break;
                            }
                            char hex[k+1];
                            strncpy(hex, &encoded[i+2], k);
                            hex[k] = '\0';
                            int value = strtol(hex, NULL, 10);
                            decoded[j] = (char)value;
                            i += k+2;
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
        } else {
            decoded[j] = encoded[i];
        }
    }
    decoded[j] = '\0';

    return true;
}

bool html_decode_1(const char* encoded, char* decoded ) {
    size_t len = strlen(encoded);

    size_t i, j;
    for (i = 0, j = 0; i < len; i++, j++) {
        if (encoded[i] == '&') {
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
            
            // hex or decimal html codes
            else if (encoded[i+1] == '#') {
                bool found = false;

                // hex html codes
                if (encoded[i+2] == 'x') {
                    for (int k = 0; k < 6; k++) {
                        if (encoded[i+3+k] == ';') {
                            if (k == 0) {
                                break;
                            }
                            char hex[k+1];
                            strncpy(hex, &encoded[i+3], k);
                            hex[k] = '\0';
                            int value = strtol(hex, NULL, 16);
                            decoded[j] = (char)value;
                            i += k+3;
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
                    for (int k = 0; k < 6; k++) {
                        if (encoded[i+2+k] == ';') {
                            if (k == 0) {
                                break;
                            }
                            char hex[k+1];
                            strncpy(hex, &encoded[i+2], k);
                            hex[k] = '\0';
                            int value = strtol(hex, NULL, 10);
                            decoded[j] = (char)value;
                            i += k+2;
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
        } else {
            decoded[j] = encoded[i];
        }
    }
    decoded[j] = '\0';

    return true;
}


bool html_decode_0(const char* encoded, char* decoded ) {
    size_t len = strlen(encoded);

    size_t i, j;
    for (i = 0, j = 0; i < len; i++, j++) {
        if (encoded[i] == '&') {
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

bool html_decode(const char* encoded, int level, char* decoded ) {
    if (level == 0) {
        return html_decode_0(encoded, decoded);
    } else if (level == 1) {
        return html_decode_1(encoded, decoded);
    } else if (level == 2) {
        return html_decode_2(encoded, decoded);
    } else {
        return html_decode_0(encoded, decoded);
    }

    return false;
}
