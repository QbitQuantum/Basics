static void test_CreateAssemblyNameObject( void )
{
    static const WCHAR emptyW[] = {0};
    IAssemblyName *name;
    HRESULT hr;

    hr = CreateAssemblyNameObject( NULL, wine1W, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok(hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr);

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, NULL, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, emptyW, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, NULL, CANOF_SET_DEFAULT_VALUES, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, emptyW, CANOF_SET_DEFAULT_VALUES, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = NULL;
    hr = CreateAssemblyNameObject( &name, wine1W, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == S_OK, "expected S_OK got %08x\n", hr );
    ok( name != NULL, "expected non-NULL name\n" );
    IAssemblyName_Release( name );

    hr = CreateAssemblyNameObject( NULL, wine1W, CANOF_SET_DEFAULT_VALUES, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, NULL, CANOF_SET_DEFAULT_VALUES, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, emptyW, CANOF_SET_DEFAULT_VALUES, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, NULL, CANOF_SET_DEFAULT_VALUES, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, emptyW, CANOF_SET_DEFAULT_VALUES, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, wine1W, CANOF_SET_DEFAULT_VALUES, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    hr = CreateAssemblyNameObject( NULL, wine1W, 0, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, NULL, 0, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, emptyW, 0, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, NULL, 0, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, emptyW, 0, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, wine1W, 0, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );

    hr = CreateAssemblyNameObject( NULL, wine1W, CANOF_SET_DEFAULT_VALUES|CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, NULL, CANOF_SET_DEFAULT_VALUES|CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, emptyW, CANOF_SET_DEFAULT_VALUES|CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, NULL, CANOF_SET_DEFAULT_VALUES|CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, emptyW, CANOF_SET_DEFAULT_VALUES|CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, wine1W, CANOF_SET_DEFAULT_VALUES|CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = NULL;
    hr = CreateAssemblyNameObject( &name, wine3W, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == S_OK, "expected S_OK got %08x\n", hr );
    ok( name != NULL, "expected non-NULL name\n" );
    IAssemblyName_Release( name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, wine4W, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, wine5W, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == HRESULT_FROM_WIN32( ERROR_SXS_INVALID_ASSEMBLY_IDENTITY_ATTRIBUTE_NAME ),
        "expected ERROR_SXS_INVALID_ASSEMBLY_IDENTITY_ATTRIBUTE_NAME got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, wine6W, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == HRESULT_FROM_WIN32( ERROR_SXS_INVALID_ASSEMBLY_IDENTITY_ATTRIBUTE_NAME ),
        "expected ERROR_SXS_INVALID_ASSEMBLY_IDENTITY_ATTRIBUTE_NAME got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, wine7W, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = NULL;
    hr = CreateAssemblyNameObject( &name, wine8W, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == S_OK, "expected S_OK got %08x\n", hr );
    ok( name != NULL, "expected non-NULL name\n" );
    IAssemblyName_Release( name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, wine9W, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );

    name = NULL;
    hr = CreateAssemblyNameObject( &name, wine10W, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == S_OK, "expected S_OK got %08x\n", hr );
    ok( name != NULL, "expected non-NULL name\n" );
    IAssemblyName_Release( name );

    name = (IAssemblyName *)0xdeadbeef;
    hr = CreateAssemblyNameObject( &name, wine11W, CANOF_PARSE_DISPLAY_NAME, NULL );
    ok( hr == E_INVALIDARG, "expected E_INVALIDARG got %08x\n", hr );
    ok( !name, "expected NULL got %p\n", name );
}