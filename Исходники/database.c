UINT WINAPI MsiDatabaseExportA( MSIHANDLE handle, LPCSTR szTable,
               LPCSTR szFolder, LPCSTR szFilename )
{
    LPWSTR path = NULL, file = NULL, table = NULL;
    UINT r = ERROR_OUTOFMEMORY;

    TRACE("%lx %s %s %s\n", handle, debugstr_a(szTable),
          debugstr_a(szFolder), debugstr_a(szFilename));

    if( szTable )
    {
        table = strdupAtoW( szTable );
        if( !table )
            goto end;
    }

    if( szFolder )
    {
        path = strdupAtoW( szFolder );
        if( !path )
            goto end;
    }

    if( szFilename )
    {
        file = strdupAtoW( szFilename );
        if( !file )
            goto end;
    }

    r = MsiDatabaseExportW( handle, table, path, file );

end:
    msi_free( table );
    msi_free( path );
    msi_free( file );

    return r;
}