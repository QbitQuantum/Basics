/*************************************
*
*  Remove and free a menu info. structure
*  from a menu info. list.
*
**************************************/
BOOL __far __pascal DeleteMenuInfoForAlias( HTVMENUINFO __far * hFirstMenuInfo, WORD wParamAlias  )
{
    FPTVMENUINFO fpMenuInfo, fpTmpMenuInfo;
    HTVMENUINFO hMenuInfo, hTmpMenuInfo;


    /* Existing first node. */
    if( *hFirstMenuInfo == 0 ) return FALSE;

    /* Lock top handle. */
    fpMenuInfo = (FPTVMENUINFO) GlobalLock( *hFirstMenuInfo ) ;

    /* If deleting top node. */
    if( fpMenuInfo->wParamAlias == wParamAlias )
    {
        /* Remove the menu item from menu. */
        DeleteMenu( GetTVMenuHandle(), fpMenuInfo->wParamAlias, MF_BYCOMMAND );
        DrawMenuBar( GetTVWindowHandle());

        /* Next node is to be new top node. */
        hTmpMenuInfo = fpMenuInfo->Next;

        /* Unlock top handle. */
        GlobalUnlock( *hFirstMenuInfo );

        /* Free top. */
        FreeMenuInfo( *hFirstMenuInfo );

        /* Assign new top. */
        *hFirstMenuInfo = hTmpMenuInfo;

        /* Success. */
        return TRUE;
    }

    /* Unlock top handle. */
    GlobalUnlock( *hFirstMenuInfo );

    /* Find correct node and remove. */
    hTmpMenuInfo = *hFirstMenuInfo;
    hMenuInfo = GetNextMenuInfo( *hFirstMenuInfo );

    while( hMenuInfo != 0 )
    {
        /* Lock current node. */
        fpMenuInfo = (FPTVMENUINFO) GlobalLock( hMenuInfo ) ;

        /* If deleting current node. */
        if( fpMenuInfo->wParamAlias == wParamAlias )
        {
            /* Remove the menu item from menu. */
            DeleteMenu( GetTVMenuHandle(), fpMenuInfo->wParamAlias, MF_BYCOMMAND );
            DrawMenuBar( GetTVWindowHandle());

            /* Lock previous node. */
            fpTmpMenuInfo = (FPTVMENUINFO) GlobalLock( hTmpMenuInfo ) ;

            /* Previous node's "next node" is deleted node's "next node". */
            fpTmpMenuInfo->Next = fpMenuInfo->Next;

            /* Unlock previous node. */
            GlobalUnlock( hTmpMenuInfo );

            /* Unlock current node. */
            GlobalUnlock( hMenuInfo );

            /* Free top. */
            FreeMenuInfo( hMenuInfo );

            /* Success. */
            return TRUE;
        }

        /* Unlock it. */
        GlobalUnlock( hMenuInfo ) ;

        /* Get next node. */
        hTmpMenuInfo = hMenuInfo;
        hMenuInfo = GetNextMenuInfo( hMenuInfo );
    }

    /* Did not find menu. */
    return FALSE;
}