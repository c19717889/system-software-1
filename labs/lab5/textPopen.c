/*
 * upper:  executes a given program, converting all input
 *      to upper case.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>

char   buffer[_POSIX_ARG_MAX];

int main( int argc, char** argv )
  {
    int  i;
    int  c;
    FILE* f;

    for( i = 1; i < argc; i++ ) {
      strcat( buffer, argv[i] );
      strcat( buffer, " " );
    }
    if( ( f = popen( buffer, "w" ) ) == NULL ) {
      perror( "popen" );
      return EXIT_FAILURE;
    }
    while( ( c = getchar() ) != EOF ) {
      if( islower( c ) )
        c = toupper( c );
      putc( c, f );
    }
    pclose( f );
    return EXIT_SUCCESS;
  }