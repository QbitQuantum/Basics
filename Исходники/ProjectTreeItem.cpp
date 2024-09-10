//TODO: Double check/ensure this function is only called via the gui thread..
SIZE ProjectTreeItem::GetPreferredSize()
{
	SIZE sz = defaultSize;
	if(!m_size.cx)
	{
		m_size.cy = defaultSize.cy;
		HDC dc = GetDC(m_parentHwnd);
		if(dc)
		{
			HGDIOBJ oldFont = SelectObject(dc, s_hFont);
			SetTextAlign(dc, TA_LEFT);
			loadngo::gui::NativeString title(m_pTask->GetTitle());
			const TCHAR *pTitle = title;
            long strLen = _tcslen(pTitle);
			SCRIPT_STRING_ANALYSIS ssa;
			SecureZeroMemory(&ssa, sizeof(SCRIPT_STRING_ANALYSIS));
			HRESULT hr = ScriptStringAnalyse(dc, pTitle, strLen, 0, -1, SSA_GLYPHS, 0, 0, 0, 0, 0, 0, &ssa);
			if(SUCCEEDED(hr))
			{
				sz.cx = ScriptString_pSize(ssa)->cx + 20;
				ScriptStringFree(&ssa);
				m_size.cx = sz.cx > defaultSize.cx? sz.cx: defaultSize.cx;
			}
			SelectObject(dc, oldFont);
			ReleaseDC(m_parentHwnd, dc);
		}
	}
	return m_size.cx? m_size: sz;
}