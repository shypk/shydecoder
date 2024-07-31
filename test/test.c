#include "html.h"
#include "escape.h"
#include "url.h"
#include "unify.h"
#include "base64.h"

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

void test_url( const char* data)
{
    int limit = strlen(data);
    char ret[limit];

    printf( "orginal : %s\n", data);
    url_decode( data, (char*)ret);
    printf( "done : %s\n", ret );
}

void test_base64( const char* data)
{
    int limit = strlen(data);
    char ret[limit];

    printf( "orginal : %s\n", data);
    base64_decode( data, (char*)ret);
    printf( "done : %s\n", ret );
}

void test_unify( const char* data, int level)
{
    int limit = strlen(data);
    char ret[limit];

    printf( "orginal : %s\n", data);
    unify_decode( data, level, (char*)ret);
    printf( "done %d : %s\n", level, ret );
}

int main() {
    

    printf( "====================================\n" );
    printf( "==  html test\n" );
    printf( "====================================\n" );
    test_html("&lt;Hello, World!&gt;", 0);
    test_html("&lt;a onclick=&quot;inner(&#039;args&#039;)&quot;&gt;", 0);
    test_html("&lt;a onclick=&quot;inner(&#039;args&#039;)&quot;&gt;", 1);
    test_html("&lt;a onclick=&quot;inner(&#0039;args&#0039;)&quot;&gt;", 1);
    test_html("&lt;a onclick=&quot;inner(&#x27;args&#x27;)&quot;&gt;", 1);
    test_html("&lt;a onclick=&quot;inner(&#x0027;args&#x0027;)&quot;&gt;", 1);

    test_html("&lt;a&nbsp;onclick=&quot;inner(&#x0027;args&#x0027;)&quot;&gt;", 1);
    test_html("&lt;a&nbsp;onclick=&quot;inner(&#x0027;args&#x0027;)&quot;&gt;", 2);
    test_html("&lt;a&nbsp;onclick=&quot;inner(&#x0027;args&#x1D54F;&#x0027;)&quot;&gt;", 2);
    test_html("&lt;a&nbsp;onclick=&quot;inner(&#x0027;args&#x01D54F;&#x0027;)&quot;&gt;", 2);
    test_html("&lt;a&nbsp;onclick=&quot;inner(&#x0027;args&#120143;&#x0027;)&quot;&gt;", 2);

    test_html("some trap value&; or &#; or &#x;", 2);

    printf( "====================================\n" );
    printf( "==  escape test\n" );
    printf( "====================================\n" );
    test_escape("a onclick='\\U01D54Finner(\\x27args\\x27\\u3042)'", 0);
    test_escape("a onclick='\\U01D54Finner(\\x27args\\x27\\u3042)'", 1);
    test_escape("a onclick='\\U01D54Finner(\\x27args\\x27\\u3042)'", 2);

    test_escape("some trap value '\\U01D5Finner(\\x7args\\xg7\\u302)'", 2);


    printf( "====================================\n" );
    printf( "==  url test\n" );
    printf( "====================================\n" );
    test_url("a onclick='\%F0\%9D\%95\%8Finner(\%27args\%27\%E3\%81\%82)'" );

    printf( "====================================\n" );
    printf( "==  base64 test\n" );
    printf( "====================================\n" );
    test_base64("44G+44GE44Ob44O844Og");
    test_base64("d2l0aOODj+ODg+ODlOODvA==");
    test_base64("44G+44GE44Ob44O844Og=\%25\%32");
    test_base64("d2l0aOODj+ODg+ODlOODvA===\%25\%32");
    test_base64("{ ");

    printf( "====================================\n" );
    printf( "==  unify test\n" );
    printf( "====================================\n" );
    test_unify("&lt;a&nbsp;onclick=&quot;inner(&#x0027;args&#x01D54F;&#x0027;)&quot;&gt;\na onclick='\\U01D54Finner(\\x27args\\x27\\u3042)'\nas url = '\%F0\%9D\%95\%8Finner(\%27args\%27\%E3\%81\%82)'", 2);



    return 0;
}



