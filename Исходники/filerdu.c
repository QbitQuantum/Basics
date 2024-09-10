static rdos_handle_type *AllocHandleObj( const char *file_name )
{
    rdos_handle_type *h;
    char *buf = 0;

    if( file_name )
        buf = _fullpath( 0, file_name, 0 );

    h = ( rdos_handle_type * )lib_malloc( sizeof( rdos_handle_type ) );
    h->rdos_handle = HANDLE_TYPE_FILE;
    h->mode = 0;
    h->type = 0;
    h->ref_count = 1;
    h->file_name = buf;
    return( h );
}