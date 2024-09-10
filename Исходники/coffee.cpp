/******************************************************************************
* ManageEmployeesPaneProc *
*-------------------------*
*   Description:
*       Handles messages specifically for the manage employees pane.
*
******************************************************************************/
LRESULT ManageEmployeesPaneProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    USES_CONVERSION;
    
    static ULONG ulNumTokens;
    static ULONG ulCurToken;
    static WCHAR**  ppszTokenIds;
    static CSpDynamicString*  ppcDesciptionString;     // This is string helper class in sphelper.h
    
    switch ( message )
    {
        case WM_GOTOOFFICE:
        {
            // Set the right message handler and repaint
            g_fpCurrentPane = OfficePaneProc;
            //Cleanup our variables
            ManageEmployeesPaneCleanup( ppszTokenIds, ppcDesciptionString, ulNumTokens );            
            ppszTokenIds = NULL;
            ppcDesciptionString = NULL;
            ulNumTokens = 0;

            // Set the hear voice rule to inactive
            HRESULT hr = g_cpCmdGrammar->SetRuleIdState( VID_HearTheVoice, SPRS_INACTIVE );            
            _ASSERTE( SUCCEEDED( hr ) );

            PostMessage( hWnd, WM_INITPANE, NULL, NULL );
            InvalidateRect( hWnd, NULL, TRUE );
            return ( 1 );
        }

        case WM_GOTOCOUNTER:
        {
            // Set the right message handler and repaint
            g_fpCurrentPane = CounterPaneProc;
            //Cleanup our variables
            ManageEmployeesPaneCleanup( ppszTokenIds, ppcDesciptionString, ulNumTokens );            
            ppszTokenIds = NULL;
            ppcDesciptionString = NULL;
            ulNumTokens = 0;

            // Set the hear voice rule to inactive
            HRESULT hr = g_cpCmdGrammar->SetRuleIdState( VID_HearTheVoice, SPRS_INACTIVE );            
            _ASSERTE( SUCCEEDED( hr ) );

            PostMessage( hWnd, WM_INITPANE, NULL, NULL );
            InvalidateRect( hWnd, NULL, TRUE );
            return ( 1 );
        }
        case WM_PAINT:
        {
            // Do the actual UI paint
            ManageEmployeesPanePaint( hWnd, ulNumTokens, ppcDesciptionString, ulCurToken );
            return ( 1 );
        }

        case WM_INITPANE:
        {
            ISpObjectToken                  *pToken = NULL;  // Token interface pointer
            CComPtr<IEnumSpObjectTokens>    cpEnum;          // Pointer to token enumerator
            ULONG                           ulIndex = 0;
            ulCurToken = 0xffffffff;

            // Get a token enumerator for tts voices available
            HRESULT hr = SpEnumTokens(SPCAT_VOICES, NULL, NULL, &cpEnum);
            if ( S_OK == hr )
            {
                // Get the numbers of tokens found
                hr = cpEnum->GetCount( &ulNumTokens );

                if ( SUCCEEDED( hr ) && 0 != ulNumTokens )
                {
                    // Create arrays we need for storing data
                    ppcDesciptionString = new CSpDynamicString [ulNumTokens];
                    if ( NULL == ppcDesciptionString )
                    {
                        hr = E_OUTOFMEMORY;
                        break;
                    }

                    ppszTokenIds = new WCHAR* [ulNumTokens];
                    if ( NULL == ppszTokenIds )
                    {
                        hr = E_OUTOFMEMORY;
                        break;
                    }
                    ZeroMemory( ppszTokenIds, ulNumTokens*sizeof( WCHAR* ) );                    
                    
                    // Get the next token in the enumeration
                    // State is maintained in the enumerator
                    while (cpEnum->Next(1, &pToken, NULL) == S_OK)
                    {
                        // Get a string which describes the token, in our case, the voice name
                        hr = SpGetDescription( pToken, &ppcDesciptionString[ulIndex] );
                        _ASSERTE( SUCCEEDED( hr ) );
                        
                        // Get the token id, for a low overhead way to retrieve the token later
                        // without holding on to the object itself
                        hr = pToken->GetId( &ppszTokenIds[ulIndex] );
                        _ASSERTE( SUCCEEDED( hr ) );
                        
                        ulIndex++;
                        
                        // Release the token itself
                        pToken->Release();
                        pToken = NULL;
                    }                   
                }
                
                // if we've failed to properly initialize, then we should completely shut-down
                if ( S_OK != hr )
                {
                    if ( pToken )
                    {
                        pToken->Release();
                    }
                    ManageEmployeesPaneCleanup( ppszTokenIds, ppcDesciptionString, ulNumTokens );

                    ppszTokenIds = NULL;
                    ppcDesciptionString = NULL;
                    ulNumTokens = 0;
                }
                // Find out which token corresponds to our voice which is currently in use
                else
                {
                    WCHAR *pszCurTokenId = NULL;

                    // Get the token representing the current voice
                    HRESULT hr = g_cpVoice->GetVoice( &pToken );
                    if ( SUCCEEDED( hr ) )
                    {
                        // Get the current token ID, and compare it against others to figure out
                        // which desciption string is the one currently selected.
                        hr = pToken->GetId( &pszCurTokenId );
                        if ( SUCCEEDED( hr ) )
                        {
                            ulIndex = 0;
                            while ( ulIndex < ulNumTokens && 
                                    0 != _wcsicmp( pszCurTokenId, ppszTokenIds[ulIndex] ) )
                            {
                                ulIndex++;
                            }

                            // We found it, so set the current index to that of the current token
                            if ( ulIndex < ulNumTokens )
                            {
                                ulCurToken = ulIndex;
                            }

                            CoTaskMemFree( pszCurTokenId );
                        }

                        pToken->Release();

                    }                                       

                }
            
            }

            // Set the hear voice rule to active
            hr = g_cpCmdGrammar->SetRuleIdState( VID_HearTheVoice, SPRS_ACTIVE );            
            _ASSERTE( SUCCEEDED( hr ) );

            return ( 1 );
        }

        case WM_DESTROY:
            // Windows is closing down, so we should cleanup
            ManageEmployeesPaneCleanup( ppszTokenIds, ppcDesciptionString, ulNumTokens );
            return ( 1 );

        case WM_HEARTHEVOICE:
            // Set the voice to play
            LoadString( g_hInst, IDS_VOICESPEAK, g_szCounterDisplay, MAX_LOADSTRING );
            g_cpVoice->Speak( T2W(g_szCounterDisplay), SPF_ASYNC | SPF_PURGEBEFORESPEAK, NULL );
    }
    return ( 0 );
}