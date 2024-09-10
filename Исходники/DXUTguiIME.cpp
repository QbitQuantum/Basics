//--------------------------------------------------------------------------------------
bool CDXUTIMEEditBox::HandleMouse( UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam )
{
    if( !m_bEnabled || !m_bVisible )
        return false;
    
    switch( uMsg )
    {
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
            {
                DXUTFontNode* pFont = m_pDialog->GetFont( m_Elements.GetAt( 9 )->iFont );

                // Check if this click is on top of the composition string
                int nCompStrWidth;
                s_CompString.CPtoX( s_CompString.GetTextSize(), FALSE, &nCompStrWidth );

                if( s_ptCompString.x <= pt.x &&
                    s_ptCompString.y <= pt.y &&
                    s_ptCompString.x + nCompStrWidth > pt.x &&
                    s_ptCompString.y + pFont->nHeight > pt.y )
                {
                    int nCharBodyHit, nCharHit;
                    int nTrail;

                    // Determine the character clicked on.
                    s_CompString.XtoCP( pt.x - s_ptCompString.x, &nCharBodyHit, &nTrail );
                    if( nTrail && nCharBodyHit < s_CompString.GetTextSize() )
                        nCharHit = nCharBodyHit + 1;
                    else
                        nCharHit = nCharBodyHit;


                    switch( GetPrimaryLanguage() )
                    {
                        case LANG_JAPANESE:
                            // For Japanese, there are two cases.  If s_nFirstTargetConv is
                            // -1, the comp string hasn't been converted yet, and we use
                            // s_nCompCaret.  For any other value of s_nFirstTargetConv,
                            // the string has been converted, so we use clause information.

                            if( s_nFirstTargetConv != -1 )
                            {
                                int nClauseClicked = 0;
                                while( ( int )s_adwCompStringClause[nClauseClicked + 1] <= nCharBodyHit )
                                    ++nClauseClicked;

                                int nClauseSelected = 0;
                                while( ( int )s_adwCompStringClause[nClauseSelected + 1] <= s_nFirstTargetConv )
                                    ++nClauseSelected;

                                BYTE nVirtKey = nClauseClicked > nClauseSelected ? VK_RIGHT : VK_LEFT;
                                int nSendCount = abs( nClauseClicked - nClauseSelected );
                                while( nSendCount-- > 0 )
                                    SendKey( nVirtKey );

                                return true;
                            }

                            // Not converted case. Fall thru to Chinese case.

                        case LANG_CHINESE:
                        {
                            // For Chinese, use s_nCompCaret.
                            BYTE nVirtKey = nCharHit > ( int )ImeUi_GetImeCursorChars() ? VK_RIGHT : VK_LEFT;
                            int nSendCount = abs( nCharHit - ( int )ImeUi_GetImeCursorChars() );
                            while( nSendCount-- > 0 )
                                SendKey( nVirtKey );
                            break;
                        }
                    }

                    return true;
                }

                // Check if the click is on top of the candidate window
                if( ImeUi_IsShowCandListWindow() && PtInRect( &s_CandList.rcCandidate, pt ) )
                {
                    if( ImeUi_IsVerticalCand() )
                    {
                        // Vertical candidate window

                        // Compute the row the click is on
                        int nRow = ( pt.y - s_CandList.rcCandidate.top ) / pFont->nHeight;

                        if( nRow < ( int )ImeUi_GetCandidateCount() )
                        {
                            // nRow is a valid entry.
                            // Now emulate keystrokes to select the candidate at this row.
                            switch( GetPrimaryLanguage() )
                            {
                                case LANG_CHINESE:
                                case LANG_KOREAN:
                                    // For Chinese and Korean, simply send the number keystroke.
                                    SendKey( ( BYTE )( '0' + nRow + 1 ) );
                                    break;

                                case LANG_JAPANESE:
                                    // For Japanese, move the selection to the target row,
                                    // then send Right, then send Left.

                                    BYTE nVirtKey;
                                    if( nRow > ( int )ImeUi_GetCandidateSelection() )
                                        nVirtKey = VK_DOWN;
                                    else
                                        nVirtKey = VK_UP;
                                    int nNumToHit = abs( int( nRow - ImeUi_GetCandidateSelection() ) );
                                    for( int nStrike = 0; nStrike < nNumToHit; ++nStrike )
                                        SendKey( nVirtKey );

                                    // Do this to close the candidate window without ending composition.
                                    SendKey( VK_RIGHT );
                                    SendKey( VK_LEFT );

                                    break;
                            }
                        }
                    }
                    else
                    {
                        // Horizontal candidate window

                        // Determine which the character the click has hit.
                        int nCharHit;
                        int nTrail;
                        s_CandList.HoriCand.XtoCP( pt.x - s_CandList.rcCandidate.left, &nCharHit, &nTrail );

                        // Determine which candidate string the character belongs to.
                        int nCandidate = ImeUi_GetCandidateCount() - 1;

                        int nEntryStart = 0;
                        for( UINT i = 0; i < ImeUi_GetCandidateCount(); ++i )
                        {
                            if( nCharHit >= nEntryStart )
                            {
                                // Haven't found it.
                                nEntryStart += lstrlenW( ImeUi_GetCandidate( i ) ) + 1;  // plus space separator
                            }
                            else
                            {
                                // Found it.  This entry starts at the right side of the click point,
                                // so the char belongs to the previous entry.
                                nCandidate = i - 1;
                                break;
                            }
                        }

                        // Now emulate keystrokes to select the candidate entry.
                        switch( GetPrimaryLanguage() )
                        {
                            case LANG_CHINESE:
                            case LANG_KOREAN:
                                // For Chinese and Korean, simply send the number keystroke.
                                SendKey( ( BYTE )( '0' + nCandidate + 1 ) );
                                break;
                        }
                    }

                    return true;
                }
            }
    }

    // If we didn't care for the msg, let the parent process it.
    return CDXUTEditBox::HandleMouse( uMsg, pt, wParam, lParam );
}