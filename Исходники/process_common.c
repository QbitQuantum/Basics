static wchar_t * fwreadFile( FILE ** file, const char * fileName, char * fileMode ) {
    wchar_t * result   ;
    long      oldOffset;
    int       resultLen;
    int       i        ;
    if ( * file == NULL || fileName == NULL || fileMode == NULL ) { return NULL; }
    // save old file state
    oldOffset = ftell( * file );
    fclose( * file );
    // read file contents
    if ( ( * file = fopen( fileName, "r" ) ) == NULL ) { return NULL; }
    //fwide( * file, 1 );
    resultLen = 0;
    while ( fgetwc( * file ) != WEOF ) { resultLen++; }
    // ta_debug_printf( "fwreadFile : resultLen is %d\n", resultLen );
    fseek( * file, 0, SEEK_SET );
    if ( ( result = (wchar_t *)ta_alloc_memory( ( resultLen + 1 ) * sizeof( wchar_t ) ) ) != NULL ) { // + 1 - for final 0
        // fread( result, resultLen, sizeof( wchar_t ), * file );
        int i;
        for ( i = 0; i < resultLen; i++ ) { result[ i ] = fgetwc( * file ); }
        result[ resultLen ] = 0;
    }
    fclose( * file );
    // ta_debug_printf( "fwreadFile : result is [%s|%ls]\n", result, result );
    // restore old file state
    // fileMode = [analog replace_CString for char *]( fileMode, 'w', 'a' );
    for ( i = 0; i < strlen( fileMode ); i++ ) { if ( fileMode[ i ] == 'w' ) { fileMode[ i ] = 'a'; } }
    * file = fopen( fileName, fileMode );
    fwide( * file, 1 );
    fseek( * file, oldOffset, SEEK_SET );
    return result;
}