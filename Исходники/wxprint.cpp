void WinEDA_PrintFrame::SetPenWidth(wxSpinEvent& event)
/*********************************************************/
{
	PenMinWidth = m_ButtPenWidth->GetValue();
	if ( PenMinWidth > WIDTH_MAX_VALUE )
		{
		PenMinWidth = WIDTH_MAX_VALUE;
		wxBell();
		}
	if ( PenMinWidth < WIDTH_MIN_VALUE )
		{
		PenMinWidth = WIDTH_MIN_VALUE;
		wxBell();
		}
	m_Buff_Width.Printf(wxT("%d"), PenMinWidth);
	m_ButtPenWidth->SetValue(m_Buff_Width);
}