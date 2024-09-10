/*--------------------------------------------------
  clear up
----------------------------------------------------*/
void EndTrayNotify(void)
{
	if(m_hwndTrayNotify && IsWindow(m_hwndTrayNotify))
	{
		SetWindowLong(m_hwndTrayNotify, GWL_STYLE, m_oldStyle);
		
		RemoveWindowSubclass(m_hwndTrayNotify, SubclassProcTrayNotify, 0);
		
		SetClassLong(m_hwndTrayNotify, GCL_STYLE, m_oldClassStyle);
		
		InvalidateRect(m_hwndTrayNotify, NULL, TRUE);
		
		if(m_hwndToolbar)
		{
			SendMessage(m_hwndToolbar, WM_SYSCOLORCHANGE, 0, 0);
			InvalidateRect(m_hwndToolbar, NULL, TRUE);
		}
	}
	
	m_hwndTrayNotify = NULL;
	m_hwndToolbar = NULL;
}