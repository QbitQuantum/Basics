/*
 *	funkcja callback obs³uguj¹ca stronê z opcjami tab 2
 */
INT_PTR CALLBACK DlgProcOpts_Tab2(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam) {

	static HANDLE hItemAll;

	switch ( msg ) {
	case WM_INITDIALOG:
	{
		TranslateDialogDefault(hwndDlg);

		mirfoxMiranda.getMirfoxData().setTab2OptionsState(MFENUM_OPTIONS_INIT);

		//load icons
		HIMAGELIST hIml;
		int smCx = GetSystemMetrics(SM_CXSMICON);
		int smCy = GetSystemMetrics(SM_CYSMICON);
		hIml = ImageList_Create(smCx,smCy,((LOBYTE(LOWORD(GetVersion()))>=5 && LOWORD(GetVersion())!=5) ? ILC_COLOR32 : ILC_COLOR16) | ILC_MASK, 4, 4);

		//load icons (direct)
		icoHandle_ICON_OFF = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_OFF));
		icoHandle_ICON_FF = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_FF));

		//TODO load icons (icolib) - no need to use DestroyIcon
		//HICON icoHandle_ICON_OFF = (HICON)CallService(MS_SKIN2_GETICONBYHANDLE, 0, (LPARAM)mirfoxData.icoHandle_ICON_OFF);
		//HICON icoHandle_ICON_FF = (HICON)CallService(MS_SKIN2_GETICONBYHANDLE, 0, (LPARAM)mirfoxData.icoHandle_ICON_FF);

		//add icons to ImageList list
		ImageList_AddIcon(hIml, icoHandle_ICON_OFF);
		ImageList_AddIcon(hIml, icoHandle_ICON_FF);
		SendDlgItemMessage(hwndDlg, IDC2_CONTACTS_LIST, CLM_SETEXTRAIMAGELIST, 0, (LPARAM)hIml); //m_clc.h


		//list params init
		resetListOptions(GetDlgItem(hwndDlg, IDC2_CONTACTS_LIST));
		SendDlgItemMessage(hwndDlg, IDC2_CONTACTS_LIST, CLM_SETEXTRACOLUMNS, 1, 0);

		//add 'All contacts' list record
		{
			CLCINFOITEM cii = {0};
			cii.cbSize = sizeof(cii);
			cii.flags = CLCIIF_GROUPFONT;
			cii.pszText =TranslateT("** All contacts **");
			hItemAll = (HANDLE)SendDlgItemMessage(hwndDlg, IDC2_CONTACTS_LIST, CLM_ADDINFOITEM, 0, (LPARAM)&cii);
		}

		//set contacts and groups icons
		setListContactIcons(GetDlgItem(hwndDlg, IDC2_CONTACTS_LIST));
		setListGroupIcons(GetDlgItem(hwndDlg, IDC2_CONTACTS_LIST), (HANDLE)SendDlgItemMessage(hwndDlg, IDC2_CONTACTS_LIST, CLM_GETNEXTITEM, CLGN_ROOT, 0), hItemAll, NULL);


		mirfoxMiranda.getMirfoxData().setTab2OptionsState(MFENUM_OPTIONS_WORK);
		return FALSE;

	}
	case WM_SETFOCUS:

		SetFocus(GetDlgItem(hwndDlg, IDC2_CONTACTS_LIST));
		break;

	case WM_NOTIFY:

		if (mirfoxMiranda.getMirfoxData().getTab2OptionsState() != MFENUM_OPTIONS_WORK){
			break; //options not inited yet
		}

		switch(((LPNMHDR)lParam)->idFrom) {
		case IDC2_CONTACTS_LIST:

			switch (((LPNMHDR)lParam)->code){

			case CLN_NEWCONTACT:
			case CLN_LISTREBUILT:
				setListContactIcons(GetDlgItem(hwndDlg, IDC2_CONTACTS_LIST));
				//fall through
			case CLN_CONTACTMOVED:
				setListGroupIcons(GetDlgItem(hwndDlg, IDC2_CONTACTS_LIST), (HANDLE)SendDlgItemMessage(hwndDlg, IDC2_CONTACTS_LIST, CLM_GETNEXTITEM, CLGN_ROOT, 0), hItemAll, NULL);
				break;
			case CLN_OPTIONSCHANGED:
				resetListOptions(GetDlgItem(hwndDlg, IDC2_CONTACTS_LIST));
				break;
			case NM_CLICK:
			{

				NMCLISTCONTROL *nm=(NMCLISTCONTROL*)lParam;

				// Make sure we have an extra column
				if (nm->iColumn == -1){
					break;
				}

				// Find clicked item
				DWORD hitFlags;
				HANDLE hItem = (HANDLE)SendDlgItemMessage(hwndDlg, IDC2_CONTACTS_LIST, CLM_HITTEST, (WPARAM)&hitFlags, MAKELPARAM(nm->pt.x, nm->pt.y));

				// Nothing was clicked
				if (hItem == NULL){
					break;
				}
				// It was not a visbility icon
				if (!(hitFlags & CLCHT_ONITEMEXTRA)){
					break;
				}

				// Get image in clicked column (0=off, 1=on)
				int iImage = SendDlgItemMessage(hwndDlg, IDC2_CONTACTS_LIST, CLM_GETEXTRAIMAGE, (WPARAM)hItem, MAKELPARAM(nm->iColumn, 0));
				if (iImage == 0){
					iImage=nm->iColumn + 1;
				} else {
					if (iImage == 1){
						iImage = 0;
					}
				}

				// Get item type (contact, group, etc...)
				int itemType = SendDlgItemMessage(hwndDlg, IDC2_CONTACTS_LIST, CLM_GETITEMTYPE, (WPARAM)hItem, 0);

				// Update list
				if (itemType == CLCIT_CONTACT) { // A contact
					SendDlgItemMessage(hwndDlg, IDC2_CONTACTS_LIST, CLM_SETEXTRAIMAGE, (WPARAM)hItem, MAKELPARAM(nm->iColumn, iImage));
				} else if (itemType == CLCIT_INFO) {	 // All Contacts
					setAllChildIcons(GetDlgItem(hwndDlg, IDC2_CONTACTS_LIST), hItem, nm->iColumn, iImage);
				} else if (itemType == CLCIT_GROUP) { // A group
					hItem = (HANDLE)SendDlgItemMessage(hwndDlg, IDC2_CONTACTS_LIST, CLM_GETNEXTITEM, CLGN_CHILD, (LPARAM)hItem);
					if (hItem) {
						setAllChildIcons(GetDlgItem(hwndDlg, IDC2_CONTACTS_LIST), hItem, nm->iColumn, iImage);
					}
				}

				// Update the all/none icons
				setListGroupIcons(GetDlgItem(hwndDlg, IDC2_CONTACTS_LIST), (HANDLE)SendDlgItemMessage(hwndDlg, IDC2_CONTACTS_LIST, CLM_GETNEXTITEM, CLGN_ROOT, 0), hItemAll, NULL);

				// Activate Apply button
				SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);

				break;
			}//end case NM_CLICK

			}//end switch

			break;

		case 0:
			switch (((LPNMHDR)lParam)->code)
			{
				case PSN_APPLY:
				{

					for (MCONTACT hContact = db_find_first(); hContact; hContact = db_find_next(hContact)){

						HANDLE hItem = (HANDLE)SendDlgItemMessage(hwndDlg, IDC2_CONTACTS_LIST, CLM_FINDCONTACT, hContact, 0);
						if(hItem) {

							int iImage = SendDlgItemMessage(hwndDlg, IDC2_CONTACTS_LIST, CLM_GETEXTRAIMAGE, (WPARAM)hItem, MAKELPARAM(0,0));
							MFENUM_MIRANDACONTACT_STATE contactState;

							if (iImage == 0xFF){ //TODO impossible??
							} else {
								if (iImage == 1){
									contactState = MFENUM_MIRANDACONTACT_STATE_ON;
								} else {
									contactState = MFENUM_MIRANDACONTACT_STATE_OFF;
								}
							}

							//save to mirfoxData
							int result = mirfoxMiranda.getMirfoxData().updateMirandaContactState(hContact, contactState);
							if (result != 0){
								//todo errors handling
							}

							//save to db	1 - on, 2 - off
							if (contactState == MFENUM_MIRANDACONTACT_STATE_OFF){
								db_set_b(hContact, PLUGIN_DB_ID, "state", 2);
							} else {
								db_set_b(hContact, PLUGIN_DB_ID, "state", 1);
							}


						}//TODO else { ...    (and at others if(hItem))
						//TODO contacts witch are not ay mirfoxData but on list
						//( check hash concat(all id) on mirfoxData and on list, if doesn't match - refresh mirfoxData
						//same for protocols
						//for now it schould be ok

					}

					//TODO contacts at MirfoxData but not on list now

					return TRUE;
				}
			}
			break;
		}

		break;

	case WM_DESTROY:
	{
		HIMAGELIST hIml=(HIMAGELIST)SendDlgItemMessage(hwndDlg, IDC2_CONTACTS_LIST, CLM_GETEXTRAIMAGELIST, 0, 0); //m_clc.h
		ImageList_Destroy(hIml);

		//   use DestroyIcon only witchout icolib
		DestroyIcon(icoHandle_ICON_OFF);
		icoHandle_ICON_OFF = NULL;
		DestroyIcon(icoHandle_ICON_FF);
		icoHandle_ICON_FF = NULL;

		break;

	}
	}//end switch

	return 0;
}