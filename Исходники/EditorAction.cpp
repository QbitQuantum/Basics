void CEditorAction::Render(CRect &Pos, CDC& dc,bool EventSelected, CChronoEventEditor& Ed, int renderType, bool bEnabled)
{
	COLORREF ActionBG	=m_select(&Ed)? ACTION_BG_SEL : (EventSelected? ACTION_BG_EVSEL : ACTION_BG);
	// Animating
	if(m_Anim.m_bDestroyed)
	{
		if(renderType == 3)
		{
			Pos.OffsetRect(0,m_Anim.Space);
		}
		if(renderType == 1)
		{
			Pos.OffsetRect(-30 + m_Anim.Space, 0);
		}
		//dc.FillSolidRect(Calc,BG);
		return;
	}

	

	switch(renderType)
	{
/*		case 0:
		{
			if(m_select(&Ed))
			{
				dc.FillSolidRect(Pos,ActionBG);
				dc.Draw3dRect(Pos,ACTION_BG_SEL2,ACTION_BG_SEL2);
			}

			HBITMAP load = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DOT));
			HDC hdcScreenCompat = CreateCompatibleDC(dc.m_hDC);
			HBITMAP hbmpOld = (HBITMAP)SelectObject(hdcScreenCompat, load);
			BitBlt(dc.m_hDC, Pos.left + 1, Pos.top + 1, 16, 16, hdcScreenCompat, 0, 0, SRCCOPY);
			SelectObject(hdcScreenCompat, hbmpOld);
			DeleteDC(hdcScreenCompat);
			DeleteObject(load);
		}
		break;*/

		case 1:
		{
			if(m_select(&Ed))
			{
				Pos.InflateRect(3,3);
				dc.FillSolidRect(Pos,ActionBG);
				dc.Draw3dRect(Pos,ACTION_BG_SEL2,ACTION_BG_SEL2);
				Pos.DeflateRect(3,3);
			}
			int icon = 0;
			if(m_Family)
				((EventSheetEditor*)(&Ed))->m_familyhbitmaps.Lookup(oid, icon);
			else
				((EventSheetEditor*)(&Ed))->m_objecthbitmaps.Lookup(oid, icon);

			static HDC dcMem = CreateCompatibleDC(dc.m_hDC);
						HBITMAP old = (HBITMAP)SelectObject(dcMem, Ed.GetIcon(icon));
						BitBlt(dc.m_hDC,Pos.left, Pos.top
							,16
							,16,dcMem,0,0,SRCCOPY);
			SelectObject(dcMem, old);
			//DeleteDC(dcMem); - its static so we cant delete it

			m_Anim.Space = 30;
		}
		break;

		case 2:
		{
			CHTMLFont f;
			f.SetBold(false);
			f.SetSize(8);
			f.SetName("Arial");
			f.SetImage(false);

			if (!bEnabled)
				f.SetStrike(true);

			CRect Calc = Pos;
			Calc.bottom  += m_rect(&Ed).Height();

			// Draw the action
			CString Out = m_Text;
			g_HTMLDraw.DrawText(&dc, Out, f, Calc, 0, &Ed, &m_imgs,&params);
			m_Readable = Out;

			Pos.bottom = Pos.top + Calc.Height();
			Calc = Pos;
			dc.FillSolidRect(Pos,ActionBG);

			// We may be hovering over something.
			CPoint mouse;
			GetCursorPos(&mouse);
			Ed.ScreenToClient(&mouse);

			if(Pos.PtInRect(mouse) && m_select(&Ed))
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
			Out = m_Text;
			g_HTMLDraw.DrawText(&dc, Out, f, Calc, 0, &Ed, &m_imgs,&params);
			m_Readable = Out;

			if(m_select(&Ed))
				dc.Draw3dRect(Calc,ACTION_BG_SEL2,ACTION_BG_SEL2);
		}
		break;

		case 3:
		{
			CHTMLFont f;
			f.SetBold(false);
			f.SetSize(8);
			f.SetName("Arial");
			f.SetImage(false);

			if (!bEnabled)
				f.SetStrike(true);

			CRect Calc = Pos;
			Calc.bottom  += m_rect(&Ed).Height();

			CString newtext;			
			CObjType* objectType =	((EventSheetEditor*)&Ed)->application->FindObjTypeFromNumber(oid);

			int icon = 0;

			if(m_Family)
				((EventSheetEditor*)(&Ed))->m_familyhbitmaps.Lookup(oid, icon);
			else
				((EventSheetEditor*)(&Ed))->m_objecthbitmaps.Lookup(oid, icon);

			bool show_name = true;
			bool show_icon = true;
			bool show_quotes = true;

			if (m_Text.Find("#noname") != -1) show_name = false;
			if (m_Text.Find("#noicon") != -1) show_icon = false;
			if (m_Text.Find("#noquotes") != -1) show_quotes = false;

			CString display_text = m_Text;

			display_text.Replace("#noname", "");
			display_text.Replace("#noicon", "");
			display_text.Replace("#noquotes", "");

			if (!show_quotes) display_text.Replace("\"", "");

			if (show_name && show_icon)
				newtext.Format("<img>%d</img> %s: %s",  icon, objectType->GetName(), display_text);
			else if (show_name && !show_icon)
				newtext.Format("%s: %s", objectType->GetName(), display_text);
			else if (!show_name && show_icon)
				newtext.Format("<img>%d</img> %s", icon, display_text);
			else
				newtext.Format("%s", display_text);

			CString Out = newtext;
			g_HTMLDraw.DrawText(&dc, Out, f, Calc, 0, &Ed, &m_imgs,&params);

			dc.FillSolidRect(Calc,ActionBG);

			//We may be hovering over something.
			CPoint mouse;
			GetCursorPos(&mouse);
			Ed.ScreenToClient(&mouse);

			if(Calc.PtInRect(mouse) && m_select(&Ed))
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
			Calc = Pos;
			Calc.bottom  += m_rect(&Ed).Height();

			// Get readable text
			g_HTMLDraw.DrawText(&dc, newtext, f, Calc, 0, &Ed, &m_imgs,&params);
			m_Readable = newtext.Right(newtext.GetLength() - newtext.ReverseFind(':'));

			Pos.bottom = Pos.top + Calc.Height();
		
			if(m_select(&Ed))
				dc.Draw3dRect(Calc,ACTION_BG_SEL2,ACTION_BG_SEL2);

			m_Anim.Space = Calc.Height();
		}

		break;
	}

	m_visible = true;

	m_rect(&Ed) = Pos;
	if(renderType == 1)
	{
		Pos.InflateRect(3,3);
		m_rect(&Ed) = Pos;
		Pos.DeflateRect(3,3);
	}

	

}