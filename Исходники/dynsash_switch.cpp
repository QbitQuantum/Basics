void SwitchView::OnFocus(wxFocusEvent& event) {
    wxScrollBar *hscroll = m_dyn_sash->GetHScrollBar(this);
    wxScrollBar *vscroll = m_dyn_sash->GetVScrollBar(this);

    if (event.GetEventObject() == hscroll || event.GetEventObject() == vscroll) {
        m_view->SetFocus();
    } else {
        event.Skip();
    }
}