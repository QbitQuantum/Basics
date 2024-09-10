/* Retrieve the default category/categories from the document */
UInt16 GetDefaultCategories
    (
    DocumentInfo* docInfo
    )
    /* THROWS */
{
    UInt16      categories;
    MemHandle   handle;
    Err         err;

    handle      = NULL;
    categories  = 0;

    if ( docInfo->location == RAM )
        err = OpenRAMDocument( docInfo );
    else
        err = OpenVFSDocument( docInfo );
    THROW_IF( err != errNone, err );

    GetIndexData();

    ErrTry {
        Header* categoryRecord;
        Char*   name;
        UInt16  totalSize;
        UInt16  size;
        UInt8   index;

        handle = FindRecord( CATEGORY_ID, NULL );
        if ( handle != NULL ) {
            categoryRecord  = MemHandleLock( handle );
            size            = 0;
            totalSize       = categoryRecord->size;
            name            = (Char*)( categoryRecord + 1 );
            do {
                index = GetCategoryIndex( name );
                if ( index == dmAllCategories ) {
                    index = AddCategoryToFreePosition( name );
                }
                if ( index != dmAllCategories )
                    categories |= ( 1 << index );

                size    += StrLen( name ) + 1;
                name    += StrLen( name ) + 1;
            } while ( size < totalSize );

            MemHandleUnlock( handle );
            FreeRecordHandle( &handle );
        }
        else {
            categories = 0;
        }
    }
    ErrCatch( UNUSED_PARAM( err ) ) {
        categories = 0;
    } ErrEndCatch

    if ( docInfo->location == RAM ) {
        CloseRAMDocument();
    }
    else {
        if ( handle != NULL )
            MemHandleFree( handle );
        CloseVFSDocument();
    }

    if ( categories == 0 )
        return UNFILED_CATEGORY;
    else
        return categories;
}