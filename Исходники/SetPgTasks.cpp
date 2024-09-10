INT_PTR CSetPgTasks::OnComboBox(HWND hWnd2, WORD nCtrlId, WORD code)
{
	// Other codes are not interesting yet
	if (code != CBN_SELCHANGE)
	{
		return 0;
	}

	switch (nCtrlId)
	{
	case lbCmdTasks:
		{
			if (mb_IgnoreCmdGroupList)
				break;
			MSetter lIgnoreEdit(&mb_IgnoreCmdGroupEdit);

			const CommandTasks* pCmd = NULL;
			int* Items = NULL;
			int iSelCount = GetListboxSelection(hWnd2, lbCmdTasks, Items);
			int iCur = (iSelCount == 1) ? Items[0] : -1;
			if (iCur >= 0)
				pCmd = gpSet->CmdTaskGet(iCur);
			bool lbEnable = false;
			if (pCmd)
			{
				_ASSERTE(pCmd->pszName);
				wchar_t* pszNoBrk = lstrdup(!pCmd->pszName ? L"" : (pCmd->pszName[0] != TaskBracketLeft) ? pCmd->pszName : (pCmd->pszName+1));
				if (*pszNoBrk && (pszNoBrk[_tcslen(pszNoBrk)-1] == TaskBracketRight))
					pszNoBrk[_tcslen(pszNoBrk)-1] = 0;
				SetDlgItemText(hWnd2, tCmdGroupName, pszNoBrk);
				SafeFree(pszNoBrk);

				wchar_t szKey[128] = L"";
				SetDlgItemText(hWnd2, tCmdGroupKey, pCmd->HotKey.GetHotkeyName(szKey));

				SetDlgItemText(hWnd2, tCmdGroupGuiArg, pCmd->pszGuiArgs ? pCmd->pszGuiArgs : L"");
				SetDlgItemText(hWnd2, tCmdGroupCommands, pCmd->pszCommands ? pCmd->pszCommands : L"");

				checkDlgButton(hWnd2, cbCmdGrpDefaultNew, (pCmd->Flags & CETF_NEW_DEFAULT) ? BST_CHECKED : BST_UNCHECKED);
				checkDlgButton(hWnd2, cbCmdGrpDefaultCmd, (pCmd->Flags & CETF_CMD_DEFAULT) ? BST_CHECKED : BST_UNCHECKED);
				checkDlgButton(hWnd2, cbCmdGrpTaskbar, ((pCmd->Flags & CETF_NO_TASKBAR) == CETF_NONE) ? BST_CHECKED : BST_UNCHECKED);
				checkDlgButton(hWnd2, cbCmdGrpToolbar, (pCmd->Flags & CETF_ADD_TOOLBAR) ? BST_CHECKED : BST_UNCHECKED);

				lbEnable = true;
			}
			else
			{
				SetDlgItemText(hWnd2, tCmdGroupName, L"");
				SetDlgItemText(hWnd2, tCmdGroupGuiArg, L"");
				SetDlgItemText(hWnd2, tCmdGroupCommands, L"");
			}
			//for (size_t i = 0; i < countof(SettingsNS::nTaskCtrlId); i++)
			//	EnableWindow(GetDlgItem(hWnd2, SettingsNS::nTaskCtrlId[i]), lbEnable);
			EnableDlgItems(hWnd2, eTaskCtrlId, lbEnable);

			delete[] Items;

			break;
		} // lbCmdTasks:

	#ifdef _DEBUG
	default:
		_ASSERTE(FALSE && "ComboBox was not processed by CSetPgTasks::OnComboBox");
	#endif
	}
	return 0;
}