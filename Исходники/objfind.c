static void ProcFileModRef( FILE *fp )
/************************************/
{
    byte        hdr[ 3 ];
    unsigned_16 page_len;
    unsigned_32 offset;
    char        *module_name;

    page_len = 0;
    RecBuff = NULL;
    RecMaxLen = 0;
    module_name = NULL;
    for(;;) {
        offset = ftell( fp );
        if( fread( hdr, 1, 3, fp ) != 3 )
            break;
        RecLen = hdr[ 1 ] | ( hdr[ 2 ] << 8 );
        ResizeBuff( RecLen );
        RecPtr = RecBuff;
        if( fread( RecBuff, RecLen, 1, fp ) == 0 )
            break;
        RecLen--;
        isMS386 = hdr[ 0 ] & 1;
        switch( hdr[ 0 ] & ~1 ) {
        case CMD_THEADR:
            if( module_name != NULL )
                free( module_name );
            GetName();
            *RecPtr = 0;
            module_name = malloc( strlen( (char *)NamePtr ) + 1 );
            strcpy( module_name, (char *)NamePtr );
            break;
        case CMD_MODEND:
            if( module_name != NULL )
                free( module_name );
            module_name = NULL;
            if( page_len != 0 ) {
                offset = ftell( fp );
                offset = page_len - offset % page_len;
                if( offset != page_len ) {
                    fseek( fp, offset, SEEK_CUR );
                }
            }
            break;
        case CMD_PUBDEF:
            if( ( GetIndex() | GetIndex() ) == 0 )
                GetUInt();
            while( ! EndRec() ) {
                GetName();
                *RecPtr = 0;
                if( SymbolExists( pubdef_tab, (char *)NamePtr ) != 0 ) {
                    if( SymbolExists( extdef_tab, module_name ) == 0 ) {
                        AddSymbol( extdef_tab, module_name, NULL );
                        printf( "%s\n", module_name );
                    }
                }
                GetOffset();
                GetIndex();
            }
            break;
        case LIB_HEADER_REC:
            if( isMS386 ) {
                fseek( fp, 0L, SEEK_END );
                page_len = 0;
            } else {
                page_len = RecLen + 4;
            }
            break;
        default:
            break;
        }
    }
    free( RecBuff );
}