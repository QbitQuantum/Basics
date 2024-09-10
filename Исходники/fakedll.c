static void register_fake_dll( const WCHAR *name, const void *data, size_t size )
{
    static const WCHAR atlW[] = {'a','t','l','.','d','l','l',0};
    static const WCHAR moduleW[] = {'M','O','D','U','L','E',0};
    static const WCHAR regtypeW[] = {'W','I','N','E','_','R','E','G','I','S','T','R','Y',0};
    static const WCHAR manifestW[] = {'W','I','N','E','_','M','A','N','I','F','E','S','T',0};
    const IMAGE_RESOURCE_DIRECTORY *resdir;
    LDR_RESOURCE_INFO info;
    HRESULT hr = S_OK;
    HMODULE module = (HMODULE)((ULONG_PTR)data | 1);
    HRSRC rsrc;

    if ((rsrc = FindResourceW( module, manifestW, MAKEINTRESOURCEW(RT_MANIFEST) )))
    {
        char *manifest = LoadResource( module, rsrc );
        register_manifest( name, manifest, SizeofResource( module, rsrc ), data, size );
    }

    info.Type = (ULONG_PTR)regtypeW;
    if (LdrFindResourceDirectory_U( module, &info, 1, &resdir )) return;

    if (!registrar)
    {
        /* create the object by hand since we can't guarantee that atl and ole32 are registered */
        IClassFactory *cf;
        HRESULT (WINAPI *pDllGetClassObject)( REFCLSID clsid, REFIID iid, LPVOID *ppv );
        HMODULE atl = LoadLibraryW( atlW );

        if ((pDllGetClassObject = (void *)GetProcAddress( atl, "DllGetClassObject" )))
        {
            hr = pDllGetClassObject( &CLSID_Registrar, &IID_IClassFactory, (void **)&cf );
            if (SUCCEEDED( hr ))
            {
                hr = IClassFactory_CreateInstance( cf, NULL, &IID_IRegistrar, (void **)&registrar );
                IClassFactory_Release( cf );
            }
        }
        if (!registrar)
        {
            ERR( "failed to create IRegistrar: %x\n", hr );
            return;
        }
    }

    TRACE( "registering %s\n", debugstr_w(name) );
    IRegistrar_ClearReplacements( registrar );
    IRegistrar_AddReplacement( registrar, moduleW, name );
    EnumResourceNamesW( module, regtypeW, register_resource, (LONG_PTR)&hr );
    if (FAILED(hr)) ERR( "failed to register %s: %x\n", debugstr_w(name), hr );
}