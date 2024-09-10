/******************************************************************************
* ManageEmployeesPaneProc *
*-------------------------*
*   Description:
*       Handles messages specifically for the manage employees pane.
*
******************************************************************************/
LRESULT ManageEmployeesPaneProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    static ULONG ulNumTokens;
    static ULONG ulCurToken;
    static WCHAR**  ppszTokenIds;
    static CSpDynamicString*  ppcDescriptionString;     // This is string helper class in sphelper.h
    static UINT iCurEnum;       // Indicates if we should list males, females, or both
    
    switch ( message )
    {
        case WM_GOTOOFFICE:
        {
            // Set the right message handler and repaint
            g_fpCurrentPane = OfficePaneProc;
            //Cleanup our variables
            ManageEmployeesPaneCleanup( ppszTokenIds, ppcDescriptionString, ulNumTokens );            
            ppszTokenIds = NULL;
            ppcDescriptionString = NULL;
            ulNumTokens = 0;

            // Set the hear voice rule to inactive
            HRESULT hr = g_cpCmdGrammar->SetRuleIdState( VID_HearTheVoice, SPRS_INACTIVE );            
            _ASSERTE( SUCCEEDED( hr ) );
            hr = g_cpCmdGrammar->SetRuleIdState( VID_OtherRules, SPRS_INACTIVE );            
            _ASSERTE( SUCCEEDED( hr ) );
            hr = g_cpCmdGrammar->SetRuleIdState( DYN_TTSVOICERULE, SPRS_ACTIVE );            
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
            ManageEmployeesPaneCleanup( ppszTokenIds, ppcDescriptionString, ulNumTokens );            
            ppszTokenIds = NULL;
            ppcDescriptionString = NULL;
            ulNumTokens = 0;

            // Set the hear voice rule to inactive
            HRESULT hr = g_cpCmdGrammar->SetRuleIdState( VID_HearTheVoice, SPRS_INACTIVE );            
            _ASSERTE( SUCCEEDED( hr ) );
            hr = g_cpCmdGrammar->SetRuleIdState( VID_OtherRules, SPRS_INACTIVE );            
            _ASSERTE( SUCCEEDED( hr ) );
            hr = g_cpCmdGrammar->SetRuleIdState( DYN_TTSVOICERULE, SPRS_ACTIVE );            
            _ASSERTE( SUCCEEDED( hr ) );

            PostMessage( hWnd, WM_INITPANE, NULL, NULL );
            InvalidateRect( hWnd, NULL, TRUE );
            return ( 1 );
        }
        case WM_PAINT:
        {
            // Do the actual UI paint
            ManageEmployeesPanePaint( hWnd, ulNumTokens, ppcDescriptionString, ulCurToken, iCurEnum );
            return ( 1 );
        }

        case WM_INITPANE:
        {
            ISpObjectToken                  *pToken = NULL;  // Token interface pointer
            CComPtr<IEnumSpObjectTokens>    cpEnum;          // Pointer to token enumerator
            ULONG                           ulIndex = 0;
            ulCurToken = 0xffffffff;
            WCHAR *szRequiredAttributes = NULL;
            SPSTATEHANDLE                   hDynamicRuleHandle;  // Handle to our dynamic rule

            // Set the required attributes field for the enum if we have special needs
            // based on our LPARAM in
            if ( 0 == lParam )
            {
                szRequiredAttributes = L"Gender=Male";
            }
            else if ( 1 == lParam )
            {
                szRequiredAttributes = L"Gender=Female";
            }

            // Get a token enumerator for tts voices available
            HRESULT hr = SpEnumTokens(SPCAT_VOICES, szRequiredAttributes, NULL, &cpEnum);
            if ( S_OK == hr )
            {
                // Get the numbers of tokens found
                hr = cpEnum->GetCount( &ulNumTokens );

                if ( SUCCEEDED( hr ) && 0 != ulNumTokens )
                {
                    // Create arrays we need for storing data
                    ppcDescriptionString = new CSpDynamicString [ulNumTokens];
                    if ( NULL == ppcDescriptionString )
                    {
                        break;
                    }

                    ppszTokenIds = new WCHAR* [ulNumTokens];
                    if ( NULL == ppszTokenIds )
                    {
                        break;
                    }
                    ZeroMemory( ppszTokenIds, ulNumTokens*sizeof( WCHAR* ) );                    
                    
                    // Get the next token in the enumeration
                    // State is maintained in the enumerator
                    while (cpEnum->Next(1, &pToken, NULL) == S_OK)
                    {
                        // Get a string which describes the token, in our case, the voice name
                        hr = SpGetDescription( pToken, &ppcDescriptionString[ulIndex] );
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
                    ManageEmployeesPaneCleanup( ppszTokenIds, ppcDescriptionString, ulNumTokens );

                    ppszTokenIds = NULL;
                    ppcDescriptionString = NULL;
                    ulNumTokens = 0;
                }
                // Find out which token corresponds to our voice which is currently in use
                else
                {
                    WCHAR *pszCurTokenId = NULL;

                    // Get the token representing the current voice
                    hr = g_cpVoice->GetVoice( &pToken );
                    if ( SUCCEEDED( hr ) )
                    {
                        // Get the current token ID, and compare it against others to figure out
                        // which description string is the one currently selected.
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

            // Initially, we see both genders
            _ASSERTE( lParam >= 0 && lParam <= 2);
            iCurEnum = (UINT)lParam;

            // Create a dynamic rule containing the description strings of the voice tokens
            hr = g_cpCmdGrammar->GetRule(NULL, DYN_TTSVOICERULE, SPRAF_TopLevel | SPRAF_Active | SPRAF_Dynamic, TRUE, &hDynamicRuleHandle);
            if ( SUCCEEDED( hr ) )
            {
                // Clear the rule first
                hr = g_cpCmdGrammar->ClearRule( hDynamicRuleHandle );
                _ASSERTE( SUCCEEDED( hr ) );

                // Commit the changes
                hr = g_cpCmdGrammar->Commit(0);
                _ASSERTE( SUCCEEDED( hr ) );
                
                // Add description names as the word, ulIndex as id
                for ( ulIndex = 0; ulIndex < ulNumTokens; ulIndex++ )
                {
                    SPPROPERTYINFO prop;
                    prop.pszName = L"Id";
                    prop.pszValue = L"Property";
                    prop.vValue.vt = VT_I4;
                    prop.vValue.ulVal = ulIndex;
                    hr = g_cpCmdGrammar->AddWordTransition( hDynamicRuleHandle, NULL, ppcDescriptionString[ulIndex], L" ",
                                                           SPWT_LEXICAL, 1.0, &prop);
                    _ASSERTE( SUCCEEDED( hr ) );                   
                }

                // Commit the changes
                hr = g_cpCmdGrammar->Commit(0);
                _ASSERTE( SUCCEEDED( hr ) );

                // Set the dynamic rules to active
                hr = g_cpCmdGrammar->SetRuleIdState( DYN_TTSVOICERULE, SPRS_ACTIVE );            
                _ASSERTE( SUCCEEDED( hr ) );
            }

            // Set the hear voice rule to active
            hr = g_cpCmdGrammar->SetRuleIdState( VID_HearTheVoice, SPRS_ACTIVE );            
            _ASSERTE( SUCCEEDED( hr ) );
            hr = g_cpCmdGrammar->SetRuleIdState( VID_OtherRules, SPRS_ACTIVE );            
            _ASSERTE( SUCCEEDED( hr ) );

            InvalidateRect( hWnd, NULL, TRUE );
            return ( 1 );
        }

        case WM_DESTROY:
            // Windows is closing down, so we should cleanup
            ManageEmployeesPaneCleanup( ppszTokenIds, ppcDescriptionString, ulNumTokens );
            ppszTokenIds = NULL;
            ppcDescriptionString = NULL;
            ulNumTokens = 0;
            return ( 1 );

        case WM_HEARTHEVOICE:
            // Set the voice to play
            LoadString( g_hInst, IDS_VOICESPEAK, g_szCounterDisplay, MAX_LOADSTRING );
            g_cpVoice->Speak( CT2W(g_szCounterDisplay), SPF_ASYNC | SPF_PURGEBEFORESPEAK, NULL );
            return ( 1 );

        case WM_MISCCOMMAND:
        {
            // Find out the offset from the first property we're interested in, so we can verify that
            // it's within range.
            UINT iSelection = (UINT)(lParam - VID_MalesOnly);
            if ( 2 >= iSelection )
            {
                // If we have a new listing criteria, we basically shutdown the pane and start it again
                if ( iSelection != iCurEnum )
                {
                    HRESULT hr = g_cpCmdGrammar->SetRuleIdState( VID_HearTheVoice, SPRS_INACTIVE );            
                    _ASSERTE( SUCCEEDED( hr ) );
                    hr = g_cpCmdGrammar->SetRuleIdState( VID_OtherRules, SPRS_INACTIVE );            
                    _ASSERTE( SUCCEEDED( hr ) );

                    ManageEmployeesPaneCleanup( ppszTokenIds, ppcDescriptionString, ulNumTokens );
                    ppszTokenIds = NULL;
                    ppcDescriptionString = NULL;
                    ulNumTokens = 0;
        
                    PostMessage( hWnd, WM_INITPANE, 0, (LPARAM) iSelection );
                }
            }
            return ( 1 );
        }

        case WM_TTSVOICESEL:
        {
            // If we are out of range, it is a programming error
            _ASSERTE( 0 <= lParam && ulNumTokens > (ULONG) lParam );

            // The returned Id is an index into our tokenId table, so create a token from the id
            CComPtr< ISpObjectToken >   pToken;
            HRESULT hr = SpGetTokenFromId( ppszTokenIds[lParam], &pToken, FALSE);
            if ( SUCCEEDED( hr ) )
            {
                // Set our current voice from the returned token
                hr = g_cpVoice->SetVoice( pToken );
                _ASSERTE( SUCCEEDED( hr ) );

                // Change our current voice index
                ulCurToken = (UINT)lParam;
            }

            InvalidateRect( hWnd, NULL, TRUE );
            return ( 1 );
        }

    }
    return ( 0 );
}