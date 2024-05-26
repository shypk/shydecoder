#include "html.h"
#include "escape.h"

#include <stdio.h>
#include <string.h>

void test_html( const char* data, int level)
{
    int limit = strlen(data);
    char ret[limit];

    printf( "orginal : %s\n", data);
    html_decode( data, level, (char*)ret);
    printf( "done %d : %s\n", level, ret );
}


void test_escape( const char* data, int level)
{
    int limit = strlen(data);
    char ret[limit];

    printf( "orginal : %s\n", data);
    escape_decode( data, level, (char*)ret);
    printf( "done %d : %s\n", level, ret );
}

int main() {
    
    test_html("&lt;Hello, World!&gt;", 0);
    test_html("&lt;a onclick=&quot;inner(&#039;args&#039;)&quot;&gt;", 0);
    test_html("&lt;a onclick=&quot;inner(&#039;args&#039;)&quot;&gt;", 1);
    test_html("&lt;a onclick=&quot;inner(&#0039;args&#0039;)&quot;&gt;", 1);
    test_html("&lt;a onclick=&quot;inner(&#x27;args&#x27;)&quot;&gt;", 1);
    test_html("&lt;a onclick=&quot;inner(&#x0027;args&#x0027;)&quot;&gt;", 1);

    test_html("&lt;a&nbsp;onclick=&quot;inner(&#x0027;args&#x0027;)&quot;&gt;", 1);
    test_html("&lt;a&nbsp;onclick=&quot;inner(&#x0027;args&#x0027;)&quot;&gt;", 2);

    test_html("some trap value&; or &#; or &#x;", 2);

    test_escape("a onclick='\\U01D54Finner(\\x27args\\x27\\u3042)'", 0);
    test_escape("a onclick='\\U01D54Finner(\\x27args\\x27\\u3042)'", 1);
    test_escape("a onclick='\\U01D54Finner(\\x27args\\x27\\u3042)'", 2);

    test_escape("some trap value '\\U01D5Finner(\\x7args\\xg7\\u302)'", 2);

    return 0;
}



