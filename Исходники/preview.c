UINT WINAPI MsiPreviewDialogA( MSIHANDLE hPreview, LPCSTR szDialogName )
{
    UINT r;
    LPWSTR strW = NULL;

    TRACE("%ld %s\n", hPreview, debugstr_a(szDialogName));

    if( szDialogName )
    {
        strW = strdupAtoW( szDialogName );
        if( !strW )
            return ERROR_OUTOFMEMORY;
    }
    r = MsiPreviewDialogW( hPreview, strW );
    msi_free( strW );
    return r;
}