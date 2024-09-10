int readstream( FILE* stream, StatefulString* ss ) {
    unsigned int max_length = BASE_STRING_LENGTH;
    wchar_t *temp = malloc( ( max_length + 1 ) * sizeof( wchar_t ) );
    int length = 0;

    if ( temp == NULL ) {
        allocationerror( ( max_length + 1 ), L"StatefulString::readstream" );
        exit( EXIT_FAILURE );
    }
    
    while ( ( temp[ length++ ] = fgetwc( stream ) ) != WEOF ) { 
        if ( temp[ length - 1 ] == L'\n'  ) {
            addlinebreak( ss, length - 1 );
        }
        if ( length == max_length ) {
            max_length *= 2;
            temp        = realloc( temp, ( max_length + 1 ) * sizeof( wchar_t ) );
            if ( temp == NULL ) {
                allocationerror( max_length, L"StatefulString::readstream" );
                exit( EXIT_FAILURE );
            }
        }
    }
    length--;
    temp[ length ] = L'\0';

    ss->value   = temp;
    ss->length  = length;
    return ss->length;
}