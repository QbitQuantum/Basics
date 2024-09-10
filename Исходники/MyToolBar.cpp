void CMyToolBar::OnUpdate(const Observable* source, const Message* message)
{
	if (message->code == APP_LANGUAGE_CHANGED)
	{
		CScreenDC dcScreen;
		for (size_t nLabel = 0; nLabel < m_labels.size(); ++nLabel)
		{
			Label& label = m_labels[nLabel];
			label.strText = LoadString(label.nID);

			CFont* pOldFont = dcScreen.SelectObject(label.pFont);
			int nWidth = dcScreen.GetTextExtent(label.strText).cx + 3;
			dcScreen.SelectObject(pOldFont);

			TBBUTTONINFO info;
			ZeroMemory(&info, sizeof(info));
			info.cbSize = sizeof(info);
			info.dwMask = TBIF_SIZE;
			info.cx = nWidth;

			GetToolBarCtrl().SetButtonInfo(label.nID, &info);
		}

		if (!m_labels.empty())
		{
			for (int nButton = 0; nButton < GetToolBarCtrl().GetButtonCount(); ++nButton)
			{
				TBBUTTON btn;
				ZeroMemory(&btn, sizeof(btn));
				GetToolBarCtrl().GetButton(nButton, &btn);
				CWnd* pWnd = m_toolBar.GetDlgItem(btn.idCommand);

				if (btn.fsStyle == TBSTYLE_BUTTON && pWnd != NULL)
				{
					CRect rcItem;
					m_toolBar.GetItemRect(nButton, rcItem);
					rcItem.DeflateRect(3, 0);

					pWnd->MoveWindow(rcItem);
				}
			}

			GetToolBarCtrl().AutoSize();
			Invalidate(false);
		}
	}
}