void CFunctionView::OnInitialUpdate()
{
    CRichEditView::OnInitialUpdate();

    //Set Word Wrap OFF
    m_nWordWrap = WrapNone;

    //To turn on the horizontal scroll bar
    WrapChanged();

    //Try to create a Font
    BOOL bSuccess = m_omFont.CreateFont(10, 0, 0, 0, 400, FALSE, FALSE, 0,
                                        ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                                        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                        DEFAULT_PITCH | FF_MODERN, DEFAULT_FONT);

    //If succeeded, Set the Font
    if ( bSuccess )
    {
        SetFont(&m_omFont);
    }

    //Set the Richedit control to be Read-only
    GetRichEditCtrl().SetReadOnly();

    RevokeDragDrop(m_hWnd);
}