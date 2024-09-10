static BOOL CALLBACK QunDetailsDlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{

	case WM_INITDIALOG:
		{
			TranslateDialogDefault(hwndDlg);
			SetWindowLong(hwndDlg,GWL_USERDATA,lParam);

			return TRUE;
		}

	case WM_TIMER:
		if (LocalDetails_t* ldt=networkmap[(HANDLE)GetWindowLong(hwndDlg,GWL_USERDATA)]) {
			LPSTR m_szModuleName=ldt->network->m_szModuleName;
			HANDLE hContact=ldt->hContact;
			unsigned int qunid=READC_D2(UNIQUEIDSETTING);
			/*
			ldt->network->UpdateQunContacts(hwndDlg,qunid);
			*/
			KillTimer(hwndDlg,1);
			ldt->network->append(new QunGetOnlineMemberPacket(qunid));
		}
		return TRUE;

	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->idFrom) {
			case 0:
				switch (((LPNMHDR)lParam)->code) {
					case PSN_INFOCHANGED:
						if (LocalDetails_t* ldt=networkmap[(HANDLE)((LPPSHNOTIFY)lParam)->lParam]) {
							LPTSTR pszTemp;
							LPSTR m_szModuleName=ldt->network->m_szModuleName;
							char szTemp[MAX_PATH];
							TCHAR wszTemp[MAX_PATH];
							HANDLE hContact = (HANDLE)((LPPSHNOTIFY)lParam)->lParam;
							HANDLE hContact2=hContact;
							DBVARIANT dbv;
							unsigned int nTemp;

							unsigned int qunid=0;

							qunid=READC_D2(UNIQUEIDSETTING);

							nTemp=READC_D2("Creator");
							ultoa(nTemp,szTemp,10);

							if (!READC_S2(szTemp,&dbv)) {
								// Qun creator info available
								pszTemp=mir_a2u_cp(dbv.pszVal,936);
								swprintf(wszTemp,L"%s (%u)", pszTemp, nTemp);
								mir_free(pszTemp);
								DBFreeVariant(&dbv);
							} else
								_ultow(nTemp,wszTemp,10);

							SetDlgItemText(hwndDlg,IDC_QUNINFO_CREATOR,wszTemp);

							_ultow(READC_D2("ExternalID"),wszTemp,10);
							SetDlgItemText(hwndDlg,IDC_QUNINFO_QID,wszTemp);

							if (!READC_TS2("Nick",&dbv)) {
								// Qun name available
								SetDlgItemText(hwndDlg,IDC_QUNINFO_NAME,wcschr(dbv.ptszVal,L')')+2);
								DBFreeVariant(&dbv);
							}

							if (!DBGetContactSettingTString(hContact,"CList","StatusMsg",&dbv)) {
								// Notice available
								SetDlgItemText(hwndDlg,IDC_QUNINFO_NOTICE,dbv.ptszVal);
								DBFreeVariant(&dbv);
							}

							if (!READC_TS2("Description",&dbv)) {
								// Description available
								SetDlgItemText(hwndDlg,IDC_QUNINFO_DESC,dbv.ptszVal);
								DBFreeVariant(&dbv);
							}

							switch (READC_B2("GetInfoOnline")) {
								case 1: // Just retrieved info, send member online update call
									PostMessage(hwndDlg,WM_TIMER,1,0);
									{
										unsigned int myqq=ldt->network->GetMyQQ();
										Qun* qun=ldt->network->m_qunList.getQun(READC_D2(UNIQUEIDSETTING));
										if (qun==NULL || !(qun->isAdmin(myqq)||qun->getDetails().getCreator()==myqq)) {
											EnableWindow(GetDlgItem(hwndDlg,IDC_QUNINFO_DELMEMBER),FALSE);
										} else
											EnableWindow(GetDlgItem(hwndDlg,IDC_QUNINFO_DELMEMBER),TRUE);

										if (qun->getDetails().getCreator()==myqq) {
											EnableWindow(GetDlgItem(hwndDlg,IDC_QUNINFO_SETADMIN),TRUE);
											EnableWindow(GetDlgItem(hwndDlg,IDC_QUNINFO_UNSETADMIN),TRUE);
											EnableWindow(GetDlgItem(hwndDlg,IDC_QUNINFO_TRANSFER),TRUE);
										}
									}
									break;
								case 2: // Retrieved online info
									ldt->network->UpdateQunContacts(hwndDlg,qunid);
									WRITEC_B("GetInfoOnline",0);
									ldt->timer=SetTimer(hwndDlg,1,60000,NULL);
									break;
							}
						}
					break;
				}
				break;
		}
		break;

	case WM_DESTROY:
		if (LocalDetails_t* ldt=networkmap[hwndDlg]) {
			if (ldt->timer) KillTimer(hwndDlg,1);
			delete ldt;
			networkmap.erase(hwndDlg);
		}
		break;
	case WM_COMMAND:
		{
			if (LocalDetails_t* ldt=networkmap[(HANDLE)GetWindowLong(hwndDlg,GWL_USERDATA)]) {
				char szTemp[MAX_PATH]={0};
				if (SendDlgItemMessageA(hwndDlg,IDC_QUNINFO_MEMBERLIST,LB_GETTEXT,SendDlgItemMessage(hwndDlg,IDC_QUNINFO_MEMBERLIST,LB_GETCURSEL,0,0),(LPARAM)&szTemp)!=LB_ERR && *szTemp!=0) {
					LPSTR pszChk=strrchr(szTemp,'(');

					unsigned int qqid=strtoul(strrchr(szTemp,pszChk?'(':' ')+1,NULL,10);
					LPSTR m_szModuleName=ldt->network->m_szModuleName;
					HANDLE hContact=ldt->hContact;
					unsigned int qunid=READC_D2(UNIQUEIDSETTING);

					switch (LOWORD(wParam)) {
						case IDC_QUNINFO_ADDTOME:
							{
								if (HANDLE hContact=ldt->network->FindContact(qqid)) {
									MessageBox(hwndDlg,TranslateT("The member is already in your contact list."),NULL,MB_ICONERROR);
								} else {
									ldt->network->AddContactWithSend(qqid);
								}
							}
							break;
						case IDC_QUNINFO_DELMEMBER:
							{
								TCHAR szMsg[MAX_PATH];
								_stprintf(szMsg,TranslateT("Are you sure you want to kick user %u out of this Qun %d?"),qqid,READC_D2("ExternalID"));
								if (MessageBox(NULL,szMsg,APPNAME,MB_ICONWARNING|MB_YESNO)==IDYES) {
									std::list<unsigned int> list;
									QunModifyMemberPacket *out=new QunModifyMemberPacket(READC_D2(UNIQUEIDSETTING),false);
									list.insert(list.end(),qqid);
									out->setMembers(list);
									ldt->network->append(out);
								}
							}
							break;
						case IDC_QUNINFO_SETADMIN:
						case IDC_QUNINFO_UNSETADMIN:
							{
								QunAdminOpPacket* out=new QunAdminOpPacket(qunid,qqid,LOWORD(wParam)==IDC_QUNINFO_SETADMIN);
								ldt->network->append(out);
							}
							break;
						case IDC_QUNINFO_TRANSFER:
							{
								TCHAR szMsg[MAX_PATH];
								_stprintf(szMsg,TranslateT("Are you sure you want to transfer Qun %u to user %u?"),READC_D2("ExternalID"),qqid);
								if (MessageBox(NULL,szMsg,APPNAME,MB_ICONWARNING|MB_YESNO)==IDYES) {
									std::list<unsigned int> list;
									QunTransferPacket *out=new QunTransferPacket(qunid,qqid);
									ldt->network->append(out);
								}
							}
							break;
					}
				}
			}
		}
		break;
#if 0
	case WM_COMMAND:
		/*switch(LOWORD(wParam))
		{

		case IDC_CHANGEDETAILS:
		{
		CallService(MS_UTILS_OPENURL, 1, (LPARAM)"http://www.icq.com/whitepages/user_details.php");
		}
		break;

		case IDCANCEL:
		SendMessage(GetParent(hwndDlg),msg,wParam,lParam);
		break;
		}*/
		break;
#endif
	}

	return FALSE;	
}