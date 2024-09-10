void BaseToolBarControl::onEraseBG(wxEraseEvent& event)
{
	if (!m_imgBg.getImg() || !m_imgBg->IsOk())
	{
		event.Skip();
	}
	else
	{
		wxDC *dc = event.GetDC();
		wxBitmap temp(m_imgBg->Scale(GetSize().GetWidth(), GetSize().GetHeight()));
		dc->DrawBitmap(temp, 0,0, false);
	}
}