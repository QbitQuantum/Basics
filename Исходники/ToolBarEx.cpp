LRESULT CToolBarPopup::OnPrint( WPARAM wParam, LPARAM lParam )
{
    LRESULT lResult = DefWindowProc( WM_PRINT, wParam, lParam );

    if ( m_bFlatMenu && ( lParam & PRF_NONCLIENT ) )
    {
        CDC* pDC = CDC::FromHandle( ( HDC )wParam );
        int nSavedDC = pDC->SaveDC();
        DrawBorder( pDC );
        pDC->RestoreDC( nSavedDC );
    }

    return lResult;
}