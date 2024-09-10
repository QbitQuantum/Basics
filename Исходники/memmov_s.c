void main( void )
{
    char buffer[80] = "0123456789";

    memmove_s( buffer + 1, sizeof( buffer ), buffer, 79 );
    buffer[0] = '*';
    printf( buffer );
}