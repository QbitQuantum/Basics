void CGitProgressList::OnContextMenu(CWnd* pWnd, CPoint point)
{
	if (m_options & ProgOptDryRun)
		return;	// don't do anything in a dry-run.

	if (pWnd != this)
		return; 

	int selIndex = GetSelectionMark();
	if ((point.x == -1) && (point.y == -1))
	{
		// Menu was invoked from the keyboard rather than by right-clicking
		CRect rect;
		GetItemRect(selIndex, &rect, LVIR_LABEL);
		ClientToScreen(&rect);
		point = rect.CenterPoint();
	}

	if ((selIndex < 0) || m_bThreadRunning || GetSelectedCount() == 0)
		return;

	// entry is selected, thread has finished with updating so show the popup menu
	CIconMenu popup;
	if (!popup.CreatePopupMenu())
		return;

	ContextMenuActionList actions;
	NotificationData* data = m_arData[selIndex];
	if (data && GetSelectedCount() == 1)
		data->GetContextMenu(popup, actions);

	if (!actions.empty())
		popup.AppendMenu(MF_SEPARATOR, NULL);
	actions.push_back([&]()
	{
		CString sLines;
		POSITION pos = GetFirstSelectedItemPosition();
		while (pos)
		{
			int nItem = GetNextSelectedItem(pos);
			NotificationData* data = m_arData[nItem];
			if (data)
			{
				sLines += data->sPathColumnText;
				sLines += _T("\r\n");
			}
		}
		sLines.TrimRight();
		if (!sLines.IsEmpty())
			CStringUtils::WriteAsciiStringToClipboard(sLines, GetSafeHwnd());
	});
	popup.AppendMenuIcon(actions.size(), IDS_LOG_POPUP_COPYTOCLIPBOARD, IDI_COPYCLIP);

	if (actions.empty())
		return;

	int cmd = popup.TrackPopupMenu(TPM_RETURNCMD | TPM_LEFTALIGN | TPM_NONOTIFY, point.x, point.y, this, 0);

	if (cmd <= 0 || cmd > actions.size())
		return;

	theApp.DoWaitCursor(1);
	actions.at(cmd - 1)();
	theApp.DoWaitCursor(-1);
}