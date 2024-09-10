BOOL CCheckStatic::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (wParam == ID_STATICCHECKBOX)
	{
		BOOL check = m_Check.GetCheck();
		m_Check.SetCheck(!check);

		// If we have specified some items to include, step through them
		if (m_ItemID.GetSize() > 0)
		{
			for (int i = 0; i < m_ItemID.GetSize(); i++)
			{
				GetParent()->GetDlgItem(m_ItemID[i])->EnableWindow(!check);
			}
		}
		// Otherwise, we step through the entire dialog list generated earlier
		else
		{
			for (int i = 0; i < m_IDList.GetSize(); i++)
			{
				CWnd * pWnd = GetParent()->GetDlgItem(m_IDList[i]);

				// We grab the rect of the item, put it into client co-ord's and only modify items inside our static box
				CRect rc;

				pWnd->GetWindowRect(&rc);
				ScreenToClient(&rc);

				if (m_rcStatic.PtInRect(rc.TopLeft()) && m_rcStatic.PtInRect(rc.BottomRight()))
					pWnd->EnableWindow(!check);
			}		
		}
// 
// 2001.10
// Change by Tadeusz Dracz
//	
		GetParent()->SendMessage(WM_COMMAND, MAKELONG(GetDlgCtrlID(), STN_CLICKED), (LPARAM)m_hWnd);
	}

	return CStatic::OnCommand(wParam, lParam);
}