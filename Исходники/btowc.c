void main( void )
{
    printf( "EOF is %sa valid single-byte character\n",
        btowc( EOF ) == WEOF ? "not " : "" );
}