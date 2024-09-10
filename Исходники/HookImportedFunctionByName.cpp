/*----------------------------------------------------------------------
FUNCTION        :   GetNamedImportDescriptor
DISCUSSION      :
    Gets the import descriptor for the requested module.  If the module
is not imported in hModule, NULL is returned.
    This is a potential useful function in the future.
PARAMETERS      :
    hModule      - The module to hook in.
    szImportMod  - The module name to get the import descriptor for.
RETURNS         :
    NULL  - The module was not imported or hModule is invalid.
    !NULL - The import descriptor.
----------------------------------------------------------------------*/
PIMAGE_IMPORT_DESCRIPTOR
                     GetNamedImportDescriptor ( HMODULE hModule     ,
                                                LPCSTR  szImportMod  )
{
    // Always check parameters.
    ASSERT ( NULL != szImportMod ) ;
    ASSERT ( NULL != hModule     ) ;
    if ( ( NULL == szImportMod ) || ( NULL == hModule ) )
    {
        SetLastErrorEx ( ERROR_INVALID_PARAMETER , SLE_ERROR ) ;
        return ( NULL ) ;
    }

    PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)hModule ;

    // Is this the MZ header?
    if ( ( TRUE == IsBadReadPtr ( pDOSHeader                  ,
                                 sizeof ( IMAGE_DOS_HEADER )  ) ) ||
         ( IMAGE_DOS_SIGNATURE != pDOSHeader->e_magic           )   )
    {
        ASSERT ( FALSE ) ;
        SetLastErrorEx ( ERROR_INVALID_PARAMETER , SLE_ERROR ) ;
        return ( NULL ) ;
    }

    // Get the PE header.
    PIMAGE_NT_HEADERS pNTHeader = MakePtr ( PIMAGE_NT_HEADERS       ,
                                            pDOSHeader              ,
                                            pDOSHeader->e_lfanew     ) ;

    // Is this a real PE image?
    if ( ( TRUE == IsBadReadPtr ( pNTHeader ,
                                  sizeof ( IMAGE_NT_HEADERS ) ) ) ||
         ( IMAGE_NT_SIGNATURE != pNTHeader->Signature           )   )
    {
        ASSERT ( FALSE ) ;
        SetLastErrorEx ( ERROR_INVALID_PARAMETER , SLE_ERROR ) ;
        return ( NULL ) ;
    }

    // If there is no imports section, leave now.
    if ( 0 == pNTHeader->OptionalHeader.
                         DataDirectory[ IMAGE_DIRECTORY_ENTRY_IMPORT ].
                                                      VirtualAddress   )
    {
        return ( NULL ) ;
    }

    // Get the pointer to the imports section.
    PIMAGE_IMPORT_DESCRIPTOR pImportDesc
     = MakePtr ( PIMAGE_IMPORT_DESCRIPTOR ,
                 pDOSHeader               ,
                 pNTHeader->OptionalHeader.
                         DataDirectory[ IMAGE_DIRECTORY_ENTRY_IMPORT ].
                                                      VirtualAddress ) ;

    // Loop through the import module descriptors looking for the
    //  module whose name matches szImportMod.
    while ( NULL != pImportDesc->Name )
    {
        PSTR szCurrMod = MakePtr ( PSTR              ,
                                   pDOSHeader        ,
                                   pImportDesc->Name  ) ;
        if ( 0 == _stricmp ( szCurrMod , szImportMod ) )
        {
            // Found it.
            break ;
        }
        // Look at the next one.
        pImportDesc++ ;
    }

    // If the name is NULL, then the module is not imported.
    if ( NULL == pImportDesc->Name )
    {
        return ( NULL ) ;
    }

    // All OK, Jumpmaster!
    return ( pImportDesc ) ;

}