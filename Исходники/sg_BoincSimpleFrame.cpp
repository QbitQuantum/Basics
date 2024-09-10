// We don't reliably get EraseBackground events under Linux, 
// so there is a workaround at CSimplePanelBase::MakeBGBitMap()
void CSimpleGUIPanel::OnEraseBackground(wxEraseEvent& event) {
    wxDC *dc = event.GetDC();
    
#ifdef __WXMAC__
    // Avoid unnecessary drawing due to Mac progress indicator's animation
    wxRect clipRect;
    wxRect taskRect = m_taskPanel->GetRect();
    dc->GetClippingBox(&clipRect.x, &clipRect.y, &clipRect.width, &clipRect.height);
    if (clipRect.IsEmpty() || taskRect.Contains(clipRect)) {
        return;
    }
#endif
    dc->DrawBitmap(m_bmpBg, 0, 0);
}