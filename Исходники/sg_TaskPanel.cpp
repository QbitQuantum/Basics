void CSlideShowPanel::OnEraseBackground(wxEraseEvent& event) {
    wxDC *dc = event.GetDC();
    wxRect r = GetRect();
    wxBitmap backgroundBitmap = ((CSimpleTaskPanel*)GetParent())->GetBackgroundBmp().GetSubBitmap(r);
    dc->DrawBitmap(backgroundBitmap, 0, 0);
}