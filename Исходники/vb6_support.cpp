int __declspec(dllexport) __stdcall
vbCStringToVB6( VARIANT *vResult, char *pszInput )

{
    USES_CONVERSION;

    VariantClear( vResult );

    if( pszInput != NULL )
    {
        vResult->vt = VT_BSTR;
        vResult->bstrVal = SysAllocString( A2BSTR(pszInput) );
        return 0;
    }
    else
        return 1;
}