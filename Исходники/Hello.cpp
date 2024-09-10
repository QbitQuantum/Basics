	void winx_msg OnPaint(HWND hWnd)
	{
		winx::PaintDC dc(hWnd);
		winx::ClientRect rect(hWnd);
		if(m_hTheme != NULL)
		{
			DrawThemeText(
				dc, BP_PUSHBUTTON, PBS_NORMAL,
				L"MyView", -1, DT_SINGLELINE | DT_CENTER | DT_VCENTER, 0, &rect);
		}
		else
		{
			dc.DrawText(_T("MyView"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		}
	}