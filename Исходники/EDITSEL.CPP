void CSelection::Extend( Direction eDirection, Amount eAmount, BOOL bScrollIfNeccessary, BOOL bDamage, BOOL bAllowPastEndOfLine )
{
    CBuffer *pBuffer = m_pCtrl->GetBuffer();
    int nLineCount = pBuffer->GetLineCount();
    BOOL bEnforceSelBounds = BoundSelection();
    int nSaveEndRow = m_nEndRow;
    int nSaveEndCol = m_nEndCol;
    BOOL bUsePreferredCol = FALSE;

    if ( nLineCount )
    {
        int nOldEndRow = m_nEndRow;
        int nOldStartRow = m_nStartRow;
        LPCTSTR pszEndLineStart = pBuffer->GetLineText( m_nEndRow );
        int nEndLineLen = pBuffer->GetLineLength( m_nEndRow );

        BOOL bStartRowChanged = FALSE;

        switch ( eDirection )
        {
        case eUp:
        {
            switch ( eAmount )
            {
            case eChar:
            {
                m_nEndRow--;
                bUsePreferredCol = TRUE;
                break;
            }
            case ePage:
            {
                m_nEndRow -= ( m_pView->GetBottomIndex( FALSE ) - m_pView->GetTopIndex() );
                break;
            }
            case eSmartAll:
            case eAll:
            {
                m_nEndRow = 0;
                break;
            }
            }
            break;
        }
        case eDown:
        {
            switch ( eAmount )
            {
            case eChar:
            {
                m_nEndRow++;
                bUsePreferredCol = TRUE;
                break;
            }
            case ePage:
            {
                int nTemp = m_nEndRow + ( m_pView->GetBottomIndex( FALSE ) - m_pView->GetTopIndex() );
                m_nEndRow = min( nLineCount, nTemp );
                break;
            }
            case eAll:
            case eSmartAll:
            {
                m_nEndRow = nLineCount - 1;
                break;
            }
            }
            break;
        }
        case eLeft:
        {
            switch ( eAmount )
            {
            case eChar:
            {
                if ( m_nEndCol == 0 || m_nEndCol > nEndLineLen )
                    m_nEndCol--;
                else
                    m_nEndCol -= _tclen_prev( pszEndLineStart, pszEndLineStart + m_nEndCol );
                if ( m_nEndCol < 0 )
                {
                    if ( bAllowPastEndOfLine && m_nEndRow > 0 )
                    {
                        m_nEndRow--;
                        m_nEndCol = pBuffer->GetLineLength( m_nEndRow );
                        bEnforceSelBounds = FALSE;	// already enforced by previous statement!
                    }
                    else
                    {
                        m_nEndCol = 0;
                    }
                }
                break;
            }
            case ePage:
            {
                m_nEndCol -= ( m_pView->GetRightIndex( FALSE ) - m_pView->GetLeftIndex() );
                break;
            }
            case eAll:
            {
                m_nEndCol = 0;
                break;
            }
            case eSmartAll:
            {
                LPCTSTR pszLine = pBuffer->GetLineText( m_nEndRow );
                int nFirstNonSpace = 0;
                while ( *pszLine && ( *pszLine == _T(' ') || *pszLine == _T('\t') ) )
                {
                    nFirstNonSpace++;
                    pszLine = _tcsinc( pszLine );
                }

                // jump between absolute left and 'textual' left
                m_nEndCol = ( m_nEndCol == nFirstNonSpace ? 0 : nFirstNonSpace );
                break;
            }
            case eWord:
            {
                pBuffer->AdvanceToWordStart( m_nEndRow, m_nEndCol, FALSE, TRUE );
                break;
            }
            case eWordEnd:
            {
                pBuffer->AdvanceToWordEnd( m_nEndRow, m_nEndCol, FALSE, TRUE );
                break;
            }
            case eSentence:
            {
                pBuffer->AdvanceToSentenceStart( m_nEndRow, m_nEndCol, FALSE );
                break;
            }
            }
            break;
        }
        case eRight:
        {
            switch ( eAmount )
            {
            case eChar:
            {
                if ( m_nEndCol >= nEndLineLen )
                    m_nEndCol++;
                else
                    m_nEndCol += _tclen( pszEndLineStart + m_nEndCol );
                break;
            }
            case ePage:
            {
                m_nEndCol += ( m_pView->GetRightIndex( FALSE ) - m_pView->GetLeftIndex() );
                break;
            }
            case eAll:
            {
                m_nEndCol = pBuffer->GetLineLength( m_nEndRow );
                break;
            }
            case eSmartAll:
            {
                LPCTSTR pszStart = pBuffer->GetLineText( m_nEndRow );
                int nLastChar = pBuffer->GetLineLength( m_nEndRow );
                int nFirstNonSpace = nLastChar;
                LPCTSTR pszEnd = pszStart + nFirstNonSpace - 1;
                while ( ( pszEnd >= pszStart ) && ( *pszEnd == _T(' ') || *pszEnd == _T('\t') ) )
                {
                    nFirstNonSpace--;
                    pszEnd = _tcsdec( pszStart, pszEnd );
                }

                // jump between absolute right and 'textual' right
                m_nEndCol = ( m_nEndCol <= nFirstNonSpace ? nLastChar : nFirstNonSpace );
                break;
            }
            case eWord:
            {
                pBuffer->AdvanceToWordStart( m_nEndRow, m_nEndCol, TRUE, TRUE );
                break;
            }
            case eWordEnd:
            {
                pBuffer->AdvanceToWordEnd( m_nEndRow, m_nEndCol, TRUE, TRUE );
                break;
            }
            case eSentence:
            {
                pBuffer->AdvanceToSentenceStart( m_nEndRow, m_nEndCol, TRUE );
                break;
            }
            }
            break;
        }
        case eOutward:
        {
            switch ( eAmount )
            {
            case eWord:
            {
                m_nStartCol = m_nEndCol;
                int nLineLen = pBuffer->GetLineLength( m_nEndRow );
                if ( m_nStartCol <= nLineLen )
                {
                    if ( m_nStartCol )
                    {
                        pBuffer->AdvanceToWordStart( m_nEndRow, m_nStartCol, FALSE, FALSE );
                    }
                    m_nEndCol = m_nStartCol;
                    if ( m_nStartCol < nLineLen )
                    {
                        pBuffer->AdvanceToWordEnd( m_nEndRow, m_nEndCol, TRUE, FALSE );
                    }
                }
                break;
            }
            case eSentence:
            {
                m_nStartRow = m_nEndRow;
                m_nStartCol = 0;
                pBuffer->AdvanceToSentenceStart( m_nStartRow, m_nStartCol, FALSE );
                m_nEndCol = m_nStartCol;
                m_nEndRow = m_nStartRow;
                pBuffer->AdvanceToSentenceStart( m_nEndRow, m_nEndCol, TRUE );
                bStartRowChanged = ( m_nStartRow != nOldStartRow );
                break;
            }
            }
            break;
        }
        }

        int nTemp = nLineCount - 1;
        m_nEndRow = min( m_nEndRow, nTemp );
        m_nEndRow = max( 0, m_nEndRow );

        m_nEndCol = ( nLineCount == 0 ) ? 0 : max( 0, m_nEndCol );
        BOOL bEndViewColUpToDate = FALSE;

        // keep cursor within the line's bounds if requested to
        if ( bEnforceSelBounds )
        {
            // special case: if moving left one char and beyond the end of the line,
            // do the fixup now or else the one-char move will be nullified by
            // EnforceSelBounds()
            if ( nLineCount && eDirection == eLeft && eAmount == eChar )
            {
                int nEndRowLen = pBuffer->GetLineLength( m_nEndRow );
                if ( m_nEndCol >= nEndRowLen )
                {
                    m_nEndCol = nEndRowLen - 1;
                    m_nEndCol = max( 0, m_nEndCol );
                }
            }

            if ( bUsePreferredCol && nSaveEndRow != m_nEndRow )
            {
                m_nEndCol = pBuffer->ConvertViewColToBufferCol( m_nEndRow, m_nEndViewColPreferred );
            }

            BOOL bFixup = EnforceSelBounds();

            // if we didn't have to fix-up the selection, remember this new col position
            // as the preferred position.
            if ( !bFixup )
            {
                if ( bUsePreferredCol && nSaveEndRow != m_nEndRow )
                {
                    // moved vertically -- need to translate view col from one row to another
                    int nBuffCol = pBuffer->ConvertViewColToBufferCol( m_nEndRow, m_nEndViewColPreferred );
                    m_nEndViewCol = pBuffer->ConvertBufferColToViewCol( m_nEndRow, nBuffCol );
                    m_nEndCol = pBuffer->ConvertViewColToBufferCol( m_nEndRow, m_nEndViewCol );
                }
                else if ( nSaveEndCol != m_nEndCol )
                {
                    m_nEndViewCol = pBuffer->ConvertBufferColToViewCol( m_nEndRow, m_nEndCol );
                    m_nEndViewColPreferred = m_nEndViewCol;
                }
                bEndViewColUpToDate = TRUE;
            }
        }

        // since m_nEndCol may have changed, we need to recalc the view position and re-snap m_nEndCol to the current row
        if ( !bEndViewColUpToDate )
        {
            m_nEndViewCol = pBuffer->ConvertBufferColToViewCol( m_nEndRow, m_nEndCol );
            m_nEndCol = pBuffer->ConvertViewColToBufferCol( m_nEndRow, m_nEndViewCol );
        }

        if ( eDirection == eOutward )
        {
            m_nStartViewCol = pBuffer->ConvertBufferColToViewCol( m_nStartRow, m_nStartCol );
        }

        if ( bDamage )
        {
            int nDamageStart = min( nOldEndRow, m_nEndRow );
            int nDamageEnd = max( nOldEndRow, m_nEndRow );
            if ( m_bColumnSel )
            {
                nDamageStart = min( nDamageStart, nOldStartRow );
                nDamageStart = min( nDamageStart, m_nStartRow );
                nDamageEnd = max( nDamageEnd, nOldStartRow );
                nDamageEnd = max( nDamageEnd, m_nStartRow );
            }
            if ( bStartRowChanged )
            {
                nDamageStart = min( nDamageStart, nOldStartRow );
                nDamageStart = min( nDamageStart, m_nStartRow );
                nDamageEnd = max( nDamageEnd, nOldEndRow );
                nDamageEnd = max( nDamageEnd, m_nEndRow );
            }

            m_pView->DamageView( nDamageStart, nDamageEnd );
        }

        // if user changed lines, notify the control so it can normalize the text case in the
        // line that was just left.
        if ( eDirection == eUp || eDirection == eDown )
        {
            m_pCtrl->OnChangeLineSelection();
        }
    }
    else
    {
        m_nEndCol = m_nEndRow = m_nEndViewCol = m_nStartViewCol = m_nStartCol = m_nStartRow = 0;
    }
    if ( bScrollIfNeccessary )
    {
        EnsureVisible( TRUE );
    }
}