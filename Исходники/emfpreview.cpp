void EMFPreviewWindow::OnPaint( wxPaintEvent& event )
{
    wxPaintDC dc(this);

    dc.Clear();
    
    RECT rc;
    rc.top = 0;
    rc.left = 0;
    rc.bottom = GetClientSize().GetHeight();
    rc.right = GetClientSize().GetWidth();

    PlayEnhMetaFile((HDC)dc.GetHDC(), m_meta, &rc);
}