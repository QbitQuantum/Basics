//**********************************************************************
//
// void RestoreImeUI()
//
// This repaints all displayed composition string if need.
// Main window procedure will call this upon receiving
// WM_PAINT message.
//
//**********************************************************************
void RestoreImeUI( 
    HWND hwnd )
{
    HIMC        hIMC;           // Storage for input context handle.
    LONG        bufLen;         // 

    
    //
    // If fail to get input context handle then do nothing.
    //

    if ( !( hIMC = ImmGetContext( hwnd ) ) )
        return;

    //
    // If IME conversion engine is open and there are any composition
    // string in the context then we redisplay them.
    //

    if ( ImmGetOpenStatus( hIMC ) && gImeUIData.ImeState &&
         ( bufLen = ImmGetCompositionString( hIMC, GCS_COMPSTR,
                      (void *)NULL, 0l ) ) > 0 )
    {
        LPSTR  lpCompStr;            // Pointer to composition string
        HLOCAL hMem;                 // Storage for memory handle.
        LPSTR  lpCompStrAttr = NULL; // Pointer to composition string's attribute
        LONG   bufLenAttr;           // 
        HLOCAL hMemAttr = NULL;      // Memory handle for composition string's
                                     // attributes.

        //
        // If fail to allocate and lock memory space for reading in
        // the composition string then do nothing.
        //

        if ( !( hMem = LocalAlloc( LPTR, (int)bufLen + 1 ) ) )
            goto exit2;

        if( !( lpCompStr = (LPSTR) LocalLock( hMem ) ) )
        {
            LocalFree( hMem );
            goto exit2;
        }

        //
        // Get composition string and redisplay them.
        //

        if ( ImmGetCompositionString( hIMC, GCS_COMPSTR, lpCompStr,
                                      bufLen ) > 0 )
        {

            //
            // Make sure whether we need to handle composition string's
            // attributes.
            //

            if ( ( bufLenAttr = ( ImmGetCompositionString( hIMC,
                       GCS_COMPATTR, (void FAR*)NULL, 0l ) ) ) > 0 )
            {
                //
                // If fail to allocate and lock memory space for reading in
                // the composition string's attribute then we assume
                // no attribute array.
                //

                if ( !( hMemAttr = LocalAlloc(LPTR, (int)bufLenAttr + 1 )))
                    goto nothing;

                if ( !( lpCompStrAttr = (LPSTR) LocalLock( hMemAttr ) ) )
                {
                    LocalFree( hMemAttr );
                    goto nothing;
                }

                ImmGetCompositionString( hIMC, GCS_COMPATTR, lpCompStrAttr,
                                         bufLenAttr );

                lpCompStrAttr[ bufLenAttr ] = 0;
            } 
            else
            {
nothing:
                lpCompStrAttr = NULL;
            }


            lpCompStr[ bufLen ] = 0;

            DisplayCompString( hwnd, lpCompStr, lpCompStrAttr );
     
        }

        LocalUnlock( hMem );
        LocalFree( hMem );
        
        if ( lpCompStrAttr )
        {
            if (NULL != hMemAttr)
            {
                LocalUnlock( hMemAttr );
                LocalFree( hMemAttr );
            }
        }


    }

exit2:

    ImmReleaseContext( hwnd, hIMC );

}