#include "html.h"

#include <stdio.h>
#include <string.h>

void decode( const char* data, int level)
{
    int limit = strlen(data);

    char ret[limit];

    printf( "orginal : %s\n", data);
    html_decode( data, level, (char*)ret);
    printf( "done %d : %s\n", level, ret );
}

int main() {
    
    decode("&lt;Hello, World!&gt;", 0);
    decode("&lt;a onclick=&quot;inner(&#039;args&#039;)&quot;&gt;", 0);
    decode("&lt;a onclick=&quot;inner(&#039;args&#039;)&quot;&gt;", 1);
    decode("&lt;a onclick=&quot;inner(&#0039;args&#0039;)&quot;&gt;", 1);
    decode("&lt;a onclick=&quot;inner(&#x27;args&#x27;)&quot;&gt;", 1);
    decode("&lt;a onclick=&quot;inner(&#x0027;args&#x0027;)&quot;&gt;", 1);

    decode("&lt;a&nbsp;onclick=&quot;inner(&#x0027;args&#x0027;)&quot;&gt;", 1);
    decode("&lt;a&nbsp;onclick=&quot;inner(&#x0027;args&#x0027;)&quot;&gt;", 2);

    decode("some trap value&; or &#; or &#x;", 2);

    return 0;
}



