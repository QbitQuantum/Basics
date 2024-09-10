void CEditorCondition::Render(CRect &Pos, CDC &dc, bool EventSelected, CChronoEventEditor& Ed, bool bBookmarked, bool bEnabled)
{
	COLORREF BG;
	BG = m_select(&Ed)? CONDITION_BG_SEL : (EventSelected? CONDITION_BG_EVSEL : CONDITION_BG);
	if(IsTrigger(NULL))
	{
		BG = m_select(&Ed)? CONDITION_BG_SEL : (EventSelected? CONDITION_BG_EVSEL : EVENT_BG);	
	}

	// Animating
	if(m_Anim.m_bDestroyed)
	{
		CRect Calc = Pos;
		Pos.OffsetRect(0,m_Anim.Space);
		Calc.bottom = Pos.bottom;
		dc.FillSolidRect(Calc,BG);
		return;
	}

	CRect Box = Pos;

	Box.bottom+= m_rect(&Ed).Height();

	CRect Calc = Pos;
	Calc.bottom = Box.bottom;

	CHTMLFont f;
	f.SetBold(false);
	f.SetSize(8);
	f.SetName("Segoe UI");
	f.SetImage(false);

	// Is it enabled?
	if (!bEnabled)
		f.SetStrike(true);

	CString Out;
	Out.Format("%s", m_Text);
	g_HTMLDraw.DrawText(&dc, Out, f, Calc, 0, &Ed, &m_imgs,&params);
	m_Readable.Format("%s", Out);

	dc.FillSolidRect(Calc,BG);
	{
		CRect Calc2 = Calc;
		CRect Calc = Pos;
		Calc.bottom = Box.bottom;

		//We may be hovering over something.
		CPoint mouse;
		GetCursorPos(&mouse);
		Ed.ScreenToClient(&mouse);

		if(Calc2.PtInRect(mouse) && m_select(&Ed))
		{
			for(int p = 0; p < params.size(); p++)
				for(int d = 0; d < params[p]->displayrects.size(); d++)
					if(params[p]->displayrects[d].PtInRect(mouse))
					{
						for(int a = 0; a < params[p]->displayrects.size(); a++)
							dc.FillSolidRect(params[p]->displayrects[a], RGB(100,255,100));
						continue;
					}
		}

		// End hover
		CString Out;

		bool show_quotes = true;
		if (m_Text.Find("#noquotes") != -1) show_quotes = false;

		CString display_text = m_Text;
		display_text.Replace("#noquotes", "");
		if (!show_quotes) display_text.Replace("\"", "");

		Out.Format("%s", display_text);
		g_HTMLDraw.DrawText(&dc, Out, f, Calc, 0, &Ed, &m_imgs,&params);
		m_Readable.Format("%s", Out);

		if(m_select(&Ed))
			dc.Draw3dRect(Calc2,CONDITION_BG_SEL2,CONDITION_BG_SEL2);
	}


	m_rect(&Ed) = Calc;
	
	Pos.OffsetRect(CPoint(0,Calc.Height()));
	m_Anim.Space = Calc.Height();

	if(IsLoop(NULL))
	{
		Pos.left += 10;
	}
}