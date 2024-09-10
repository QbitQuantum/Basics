static
rc_t make_absolute_and_transform_to_utf8_and_make_vpath ( const VFSManager * self,
    VPath ** new_path, const wchar_t * src, bool have_drive )
{
    rc_t rc;
    wchar_t full [ 4096 ];

    /* expand to full path - this is temporary, and will be replaced after KFS is updated */
    DWORD len = GetFullPathNameW ( src, sizeof full / sizeof full [ 0 ], full, NULL );
    if ( len == 0 )
    {
        /* we have an error */
        DWORD status = GetLastError ();
        DBGMSG ( DBG_VFS, DBG_FLAG_ANY, ( "GetFullPathNameW: error code - %u.\n", status ) );
        rc = RC ( rcVFS, rcMgr, rcConstructing, rcPath, rcInvalid );
    }
    else if ( len >= sizeof full / sizeof full [ 0 ] )
    {
        /* the buffer is too small ! */
        wchar_t * big_buf = malloc( ( ++len ) * ( sizeof full[ 0 ] ) );
        if ( big_buf == NULL )
            rc = RC ( rcVFS, rcMgr, rcConstructing, rcMemory, rcExhausted );
        else
        {
            DWORD len2 = GetFullPathNameW ( src, len, big_buf, NULL );
            if ( len2 == 0 )
            {
                /* we have an error */
                DWORD status = GetLastError ();
                DBGMSG ( DBG_VFS, DBG_FLAG_ANY, ( "GetFullPathNameW: error code - %u.\n", status ) );
                rc = RC ( rcVFS, rcMgr, rcConstructing, rcPath, rcInvalid );
            }
            else if ( len2 >= len )
            {
                DBGMSG ( DBG_VFS, DBG_FLAG_ANY, ( "GetFullPathNameW: buffer too small again - %u.\n", len2 ) );
                rc = RC ( rcVFS, rcMgr, rcConstructing, rcPath, rcInvalid );
            }
            else
            {
                /* now we can call the final transform and make */
                rc = transform_to_utf8_and_make_vpath( self, new_path, big_buf, true );
            }
            free( big_buf );
        }
    }
    else
    {
        /* now we can call the final transform and make */
        rc = transform_to_utf8_and_make_vpath( self, new_path, full, true );
    }
    return rc;
}