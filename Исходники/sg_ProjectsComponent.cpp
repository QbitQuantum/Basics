void CProjectsComponent::OnEraseBackground(wxEraseEvent& event){
    CSkinSimple* pSkinSimple = wxGetApp().GetSkinManager()->GetSimple();

    wxASSERT(pSkinSimple);
    wxASSERT(wxDynamicCast(pSkinSimple, CSkinSimple));

	wxDC* dc = event.GetDC();
    dc->DrawBitmap(*pSkinSimple->GetProjectAreaBackgroundImage()->GetBitmap(), 0, 0);
}