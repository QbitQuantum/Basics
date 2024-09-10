void WinEDA_PlotHPGLFrame::SetPenWidth(wxSpinEvent & event)
/************************************************************/
{
	g_HPGL_Pen_Descr.m_Pen_Diam = m_ButtPenWidth->GetValue();
	if ( g_HPGL_Pen_Descr.m_Pen_Diam > 100 ) g_HPGL_Pen_Descr.m_Pen_Diam = 100;
	if ( g_HPGL_Pen_Descr.m_Pen_Diam < 1 ) g_HPGL_Pen_Descr.m_Pen_Diam = 1;

	m_Buff_Width.Printf( wxT("%d"), g_HPGL_Pen_Descr.m_Pen_Diam);
	m_ButtPenWidth->SetValue(m_Buff_Width);
}