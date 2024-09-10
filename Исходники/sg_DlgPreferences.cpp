void CPanelPreferences::OnEraseBackground( wxEraseEvent& event ) {
    if (!m_backgroundBitmap) {
        MakeBackgroundBitmap();
    }
    // Create a buffered device context to reduce flicker
    wxSize sz = GetClientSize();
    wxBufferedDC dc(event.GetDC(), sz, wxBUFFER_CLIENT_AREA);

#if TEST_BACKGROUND_WITH_MAGENTA_FILL
    // Fill the dialog with a magenta color so people can detect when something
    //   is wrong
    dc.SetBrush(wxBrush(wxColour(255,0,255)));
    dc.SetPen(wxPen(wxColour(255,0,255)));
    dc.DrawRectangle(0, 0, sz.GetWidth(), sz.GetHeight());
#else
    CSkinSimple* pSkinSimple = wxGetApp().GetSkinManager()->GetSimple();
    
    wxASSERT(pSkinSimple);
    wxASSERT(wxDynamicCast(pSkinSimple, CSkinSimple));

    wxColour bgColor(*pSkinSimple->GetDialogBackgroundImage()->GetBackgroundColor());
    SetBackgroundColour(bgColor);
#endif

    if (m_backgroundBitmap->IsOk()) {
       dc.DrawBitmap(*m_backgroundBitmap, 0, 0);
    }
}