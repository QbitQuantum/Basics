void CEmoticons::Draw(CDC* pDC, int nIndex, int nX, int nY, COLORREF crBack)
{
    if ( m_pTokens == NULL ) return;
    ImageList_DrawEx( m_pImage.m_hImageList, nIndex, pDC->GetSafeHdc(),
                      nX, nY, 16, 16, crBack, CLR_DEFAULT, ILD_NORMAL );
    // if ( crBack != CLR_NONE ) pDC->ExcludeClipRect( nX, nY, nX + 16, nY + 16 );
}