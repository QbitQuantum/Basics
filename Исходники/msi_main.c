ITypeLib *get_msi_typelib( LPWSTR *path )
{
    EnterCriticalSection( &MSI_typelib_cs );

    if (!msi_typelib)
    {
        TRACE("loading typelib\n");

        if (GetModuleFileNameW( msi_hInstance, msi_path, MAX_PATH ))
            LoadTypeLib( msi_path, &msi_typelib );
    }

    LeaveCriticalSection( &MSI_typelib_cs );

    if (path)
        *path = msi_path;

    if (msi_typelib)
        ITypeLib_AddRef( msi_typelib );

    return msi_typelib;
}