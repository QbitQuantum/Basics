/******************************************************************************
* CounterPaneProc *
*-----------------*
*   Description:
*       Handles messages specifically for the counter (order) pane.
*
******************************************************************************/
LRESULT CounterPaneProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    HRESULT hr;
    
    switch ( message )
    {
        case WM_ESPRESSOORDER:
        {
            ID_TEXT *pulIds = (ID_TEXT *) lParam;
            _ASSERTE( pulIds );
            if ( pulIds == NULL )
            {
                return 0;
            }
            KillTimer( hWnd, 0 );
            int i = 0, ilen = 0;
            TCHAR szTempBuf[NORMAL_LOADSTRING];
            TCHAR szSpace[] =  _T(" ");
            int iTemplen;
            
            g_szCounterDisplay[0] = '\0';

            // Sort the array
            while ( 0 != pulIds[i].ulId )
            {
                i++;
            }
            for ( int j = 0; j < i; j++ )
            {
                int iminIndex = j;               
                for ( int k = j; k < i; k++ )
                {
                    if ( pulIds[iminIndex].ulId > pulIds[k].ulId )
                    {
                        iminIndex = k;
                    }
                }
                ULONG ulId = pulIds[iminIndex].ulId;
                WCHAR *pwstr = pulIds[iminIndex].pwstrCoMemText;
                pulIds[iminIndex].pwstrCoMemText = pulIds[j].pwstrCoMemText;
                pulIds[j].pwstrCoMemText = pwstr;
                pulIds[iminIndex].ulId = pulIds[j].ulId;
                pulIds[j].ulId = ulId;
            }
            
            i = 0;
            // Put in the first order words if we actually have an order
            if ( 0 != pulIds[0].ulId )
            {
                iTemplen = LoadString( g_hInst, IDS_ORDERBEGIN, szTempBuf, NORMAL_LOADSTRING );                
                _tcscat_s( g_szCounterDisplay + ilen, _countof(g_szCounterDisplay) - ilen, szTempBuf );
                ilen += iTemplen;
            }
            while ( i < MAX_ID_ARRAY && 0 != pulIds[i].ulId )
            {
                CW2T pTempStr( pulIds[i].pwstrCoMemText );

                iTemplen = lstrlen( pTempStr );
                // We'll quit now so we dont overrun the buffer
                if ( ilen + iTemplen >= MAX_LOADSTRING )
                {
                    break;
                }
                if ( i > 0 )
                {
                    _tcscat_s( g_szCounterDisplay + ilen, _countof(g_szCounterDisplay) - ilen, szSpace );
                    ilen += 1;
                }
                _tcscat_s( g_szCounterDisplay, _countof(g_szCounterDisplay), pTempStr );
                ilen += iTemplen;
                i++;
            }
            // Put the thank you on this order
            if ( 0 < i )
            {
                iTemplen = LoadString( g_hInst, IDS_ORDEREND, szTempBuf, NORMAL_LOADSTRING );                
                if ( ilen + iTemplen < MAX_LOADSTRING )
                {
                    _tcscat_s( g_szCounterDisplay + ilen, _countof(g_szCounterDisplay) - ilen, szTempBuf );
                    ilen += iTemplen;
                }
            }

            InvalidateRect( hWnd, NULL, TRUE );
            SetTimer( hWnd, 0, TIMEOUT, NULL );

            // Delete the CoTaskMem we were given initially by ISpPhrase->GetText
            i = 0;
            while ( i < MAX_ID_ARRAY && 0 != pulIds[i].ulId )
            {
                CoTaskMemFree( pulIds[i].pwstrCoMemText );
                i++;
            }
            delete [] pulIds;
            return ( 1 );
        }
        case WM_PAINT:
            CounterPanePaint( hWnd, g_szCounterDisplay );
            return ( 1 );

        case WM_INITPANE:
            LoadString( g_hInst, IDS_PLEASEORDER, g_szCounterDisplay, MAX_LOADSTRING );
            // Set the rule recognizing an espresso order to active, now that we are ready for it
            g_cpCmdGrammar->SetRuleIdState( VID_EspressoDrinks, SPRS_ACTIVE );
            // Set our interests to include false recognitions
            hr = g_cpRecoCtxt->SetInterest( SPFEI(SPEI_RECOGNITION)|SPFEI(SPEI_FALSE_RECOGNITION),
                                                    SPFEI(SPEI_RECOGNITION)|SPFEI(SPEI_FALSE_RECOGNITION) );
            _ASSERTE( SUCCEEDED( hr ) );

            return ( 1 );

        case WM_TIMER:
            // Revert back to 'go ahead and order' message
            LoadString( g_hInst, IDS_PLEASEORDER, g_szCounterDisplay, MAX_LOADSTRING );
            InvalidateRect( hWnd, NULL, TRUE );
            KillTimer( hWnd, 0 );
            return ( 1 );

        case WM_GOTOOFFICE:
            KillTimer( hWnd, 0 );
            // Set the rule recognizing an espresso order to inactive
            // since you cant order from the office
            g_cpCmdGrammar->SetRuleIdState( VID_EspressoDrinks, SPRS_INACTIVE );
            // Set our interests to include only recognitions
            hr = g_cpRecoCtxt->SetInterest( SPFEI(SPEI_RECOGNITION),SPFEI(SPEI_RECOGNITION) );
            _ASSERTE( SUCCEEDED( hr ) );
            
            // Set the right message handler and repaint
            g_fpCurrentPane = OfficePaneProc;
            PostMessage( hWnd, WM_INITPANE, NULL, NULL );
            InvalidateRect( hWnd, NULL, TRUE );
            return ( 1 );

        case WM_DIDNTUNDERSTAND:
            KillTimer( hWnd, 0 );
            LoadString( g_hInst, IDS_DIDNTUNDERSTAND, g_szCounterDisplay, MAX_LOADSTRING );
            InvalidateRect( hWnd, NULL, TRUE );
            SetTimer( hWnd, 0, TIMEOUT, NULL );
            return ( 1 );

    }
    return ( 0 );
}