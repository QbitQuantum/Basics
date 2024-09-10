BOOL TRecvDlg::EvCreate(LPARAM lParam)
{
	editSub.AttachWnd(GetDlgItem(RECV_EDIT));

	editSub.SendMessage(EM_AUTOURLDETECT, 1, 0);
	editSub.SendMessage(EM_SETBKGNDCOLOR, FALSE, ::GetSysColor(COLOR_3DFACE));
	editSub.SendMessage(EM_SETTARGETDEVICE, 0, 0);		// 折り返し

	SetDlgIcon(hWnd);
	SetDlgItemTextU8(RECV_HEAD, head);

	if (msg.command & IPMSG_BROADCASTOPT)
		SetDlgItemTextU8(RECV_TITLE, GetLoadStrU8(IDS_BROADCAST));
	else if (msg.command & IPMSG_MULTICASTOPT)
		SetDlgItemTextU8(RECV_TITLE, GetLoadStrU8(IDS_MULTICAST));
	else
		SetDlgItemTextU8(RECV_TITLE, GetLoadStrU8(IDS_UNICAST));

	if (msg.command & IPMSG_AUTORETOPT)
		SetDlgItemTextU8(RECV_TITLE, GetLoadStrU8(IDS_UNIABSENCE));

	char	buf[MAX_LISTBUF];
	if (msg.command & IPMSG_ENCRYPTOPT)
	{
		GetWindowText(buf, sizeof(buf));
		strcat(buf, (cryptCapa & IPMSG_BLOWFISH_128) ? " +" : " -");
		SetWindowText(buf);
	}

	wsprintf(head, "at %s", Ctime(&recvTime));
	SetDlgItemTextU8(RECV_HEAD2, head);

	editSub.ExSetText(msg.msgBuf);

	if (msg.command & IPMSG_SECRETOPT)
		editSub.ShowWindow(SW_HIDE), ::ShowWindow(GetDlgItem(QUOTE_CHECK), SW_HIDE);
	else {
		::ShowWindow(GetDlgItem(OPEN_BUTTON), SW_HIDE), openFlg = TRUE;
		if (shareInfo)
			SetFileButton(this, FILE_BUTTON, shareInfo);
	}

	if (msg.command & IPMSG_FILEATTACHOPT)
	{
		GetDlgItemTextU8(OPEN_BUTTON, buf, sizeof(buf));
		strcat(buf, " ");
		strcat(buf, GetLoadStrU8(IDS_FILEATTACH));
		SetDlgItemTextU8(OPEN_BUTTON, buf);
	}
	if (msg.command & IPMSG_PASSWORDOPT)
	{
		GetDlgItemTextU8(OPEN_BUTTON, buf, sizeof(buf));
		strcat(buf, GetLoadStrU8(IDS_KEYOPEN));
		SetDlgItemTextU8(OPEN_BUTTON, buf);
	}

	if (cfg->QuoteCheck)
		SendDlgItemMessage(QUOTE_CHECK, BM_SETCHECK, cfg->QuoteCheck, 0);

	if (cfg->AbnormalButton)
		SetDlgItemTextU8(IDOK, GetLoadStrU8(IDS_INTERCEPT));

	SetFont();
	SetSize();

	HMENU	hMenu = ::GetSystemMenu(hWnd, FALSE);
	AppendMenuU8(hMenu, MF_SEPARATOR, NULL, NULL);
	SetMainMenu(hMenu);

	if (IsNewShell() != TRUE)
	{
		ULONG	style = GetWindowLong(GWL_STYLE);
		style &= 0xffffff0f;
		style |= 0x00000080;
		SetWindowLong(GWL_STYLE, style);
	}
	SetForegroundWindow();

	if (msg.command & IPMSG_NOADDLISTOPT)
		::EnableWindow(GetDlgItem(IDOK), FALSE);
	EvSize(SIZE_RESTORED, 0, 0);

	return	TRUE;
}