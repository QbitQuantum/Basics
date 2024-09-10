void CTransparentCheckBox::OnEraseBackground(wxEraseEvent& event)
{
    if (m_pParentsBgBmp && *m_pParentsBgBmp) {
        wxMemoryDC memDC(**m_pParentsBgBmp);
        wxSize sz = GetClientSize();
        wxDC *dc = event.GetDC();
        wxCoord x=0, y=0, xx, yy;
        wxWindow* win = this;
        do {
            win->GetPosition(&xx, &yy);
            x += xx;
            y += yy;
            win = win->GetParent();
        } while (!win->IsTopLevel());
        dc->Blit(0, 0, sz.GetWidth(), sz.GetHeight(), &memDC, x, y, wxCOPY);
    } else {
        event.Skip();
    }
}