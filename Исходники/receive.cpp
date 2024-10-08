INT_PTR CALLBACK RecvDlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
  TRecvContactsData* wndData = (TRecvContactsData*)GetWindowLong(hwndDlg, DWLP_USER);

  switch (msg)
  {
    case WM_INITDIALOG:
    {
      CLISTEVENT* pcle = (CLISTEVENT*)lParam; /// got it

      TranslateDialogDefault(hwndDlg);
      WindowList_Add(ghRecvWindowList, hwndDlg, pcle->hContact);
      SendMessageT(hwndDlg, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDI_CONTACTS)));
      EnableDlgItem(hwndDlg, IDOK, FALSE);
      EnableDlgItem(hwndDlg, IDDETAILS, FALSE);
      wndData = new TRecvContactsData(pcle->hContact);
      SetWindowLong(hwndDlg, DWLP_USER, (LONG)wndData);
      wndData->mhDbEvent = pcle->hDbEvent; /// initialized, pcle not needed anymore
      wndData->mhListIcon = ImageList_Create(GetSystemMetrics(SM_CXSMICON),GetSystemMetrics(SM_CYSMICON),ILC_COLORDDB|ILC_MASK, 0, 1);
      wndData->mhPopup = LoadMenu(hInst, MAKEINTRESOURCE(IDR_CONTACTMENU));
      CallService(MS_LANGPACK_TRANSLATEMENU, (WPARAM)wndData->mhPopup, 0);
      wndData->hHook = HookEventMessage(ME_PROTO_ACK, hwndDlg, HM_EVENTSENT);

      char *szProto = GetContactProto(wndData->mhContact);

      HWND hLV = GetDlgItem(hwndDlg, IDC_CONTACTS);
      ListView_SetExtendedListViewStyle(hLV, LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT);
      // add columns
      RecvListView_AddColumn(hLV, 120, (char*)SRCCallProtoService(szProto, PS_GETCAPS, PFLAG_UNIQUEIDTEXT, 0), FALSE, 0);
      RecvListView_AddColumn(hLV, 100, "Nick", TRUE, 1);
      RecvListView_AddColumn(hLV, 100, "First Name", TRUE, 2);
      RecvListView_AddColumn(hLV, 100, "Last Name", TRUE, 3);

      // fill in groups
      SendMessageT(GetDlgItem(hwndDlg, IDC_ENABLEGROUPS), BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
      RebuildGroupCombo(hwndDlg);

      { // fill listview with received contacts
        DBEVENTINFO dbe = {0};

        dbe.cbSize = sizeof(DBEVENTINFO);
        dbe.cbBlob = CallService(MS_DB_EVENT_GETBLOBSIZE, (WPARAM)wndData->mhDbEvent, 0);
        if (dbe.cbBlob != -1)  // this marks an invalid hDbEvent - all smashed anyway...
          dbe.pBlob = (PBYTE)_malloca(dbe.cbBlob);
        CallService(MS_DB_EVENT_GET, (WPARAM)wndData->mhDbEvent, (LPARAM)&dbe);
        char* pcBlob = (char*)dbe.pBlob;
        char* pcEnd = (char*)dbe.pBlob + dbe.cbBlob;

        HICON hiProto = LoadContactProtoIcon(wndData->mhContact);
        ImageList_AddIcon(wndData->mhListIcon, hiProto);
        DestroyIcon(hiProto); // imagelist copied the resource
        ListView_SetImageList(hLV, wndData->mhListIcon, LVSIL_SMALL);
        LVITEM lvi = {0};
        lvi.iImage = 0;
        lvi.mask = LVIF_TEXT | LVIF_IMAGE;

        for (int nItem = 0; ; nItem++)
        { // Nick
          int strsize = (int)strlennull(pcBlob);
          TReceivedItem* pItem = wndData->AddReceivedItem();

          if (dbe.flags & DBEF_UTF)
            pItem->mcaNick = utf8_to_tchar((unsigned char*)pcBlob); 
          else
            pItem->mcaNick = ansi_to_tchar(pcBlob);
          pcBlob += strsize + 1;
          // UIN
          strsize = (int)strlennull(pcBlob);
          pItem->mcaUIN = null_strdup(pcBlob);
          pcBlob += strsize + 1;
          // add to listview
          lvi.iItem = nItem;
          lvi.pszText = pItem->mcaUIN;
          ListView_InsertItem(hLV, &lvi); // with image
          ListView_SetItemTextT(hLV, nItem, 1, pItem->mcaNick);
          // check for end of contacts
          if (pcBlob >= pcEnd)
            break;
        }
      }
      // new dlg init
      wndData->hIcons[0] = InitMButton(hwndDlg, IDC_ADD, MAKEINTRESOURCEA(IDI_ADDCONTACT), "Add Contact Permanently to List");
      wndData->hIcons[1] = InitMButton(hwndDlg, IDC_DETAILS, MAKEINTRESOURCEA(IDI_USERDETAILS), "View User's Details");
      wndData->hIcons[2] = InitMButton(hwndDlg, IDC_HISTORY, MAKEINTRESOURCEA(IDI_HISTORY), "View User's History");
      wndData->hIcons[3] = InitMButton(hwndDlg, IDC_USERMENU, MAKEINTRESOURCEA(IDI_DOWNARROW), "User Menu");

      SendMessageT(hwndDlg,DM_UPDATETITLE,0,0);
      // new dialog init done
      Utils_RestoreWindowPosition(hwndDlg, NULL, MODULENAME, "");
      return TRUE;
    }
    case WM_NOTIFY:
      if (((LPNMHDR)lParam)->idFrom == IDC_CONTACTS)
      {
        switch (((LPNMHDR)lParam)->code)
        {
          case NM_DBLCLK:
          {
            HWND hLV = GetDlgItem(hwndDlg, IDC_CONTACTS);
            if (ListView_GetSelectedCount(hLV) != 1) break; // if not clicking on item, bye
            wndData->iPopupItem = ListView_GetNextItem(hLV, -1, LVNI_ALL|LVNI_SELECTED);
            if (wndData->iPopupItem == -1) break; // if no item selected no user details available
            return SendMessageT(hwndDlg, WM_COMMAND, ID_POPUP_USERDETAILS, 0); // show user details
          }
          case LVN_ITEMCHANGED:
          {
            LPNMLISTVIEW pNMLV = (LPNMLISTVIEW)lParam;
            HWND hLV = GetDlgItem(hwndDlg, IDC_CONTACTS); // optimisation, for FOR-Cycle
            bool bExistsCheckedItem = false;     // there must be no checked items to disable "Add" button

            if (ListView_GetCheckState(hLV, pNMLV->iItem))
            { // the user has checked this item
              bExistsCheckedItem = true; // enable "Add" button
            }
            else
            { // loop thru items and check if at least one is checked
              for (int i = 0; i < ListView_GetItemCount(hLV); i++)
                if (ListView_GetCheckState(hLV, i))
                {  // we found checked item, enable add, exit loop
                  bExistsCheckedItem = true;
                  break;
                }
            }
            EnableDlgItem(hwndDlg, IDOK, bExistsCheckedItem);
            EnableDlgItem(hwndDlg, IDDETAILS, ListView_GetSelectedCount(hLV) > 0);
            break;
          }
        }
      }
      break;

    case WM_COMMAND:
    {
      if (!lParam && CallService(MS_CLIST_MENUPROCESSCOMMAND, MAKEWPARAM(LOWORD(wParam), MPCF_CONTACTMENU), (LPARAM)wndData->mhContact))
        break;

      switch(LOWORD(wParam))
      {
        case IDOK:  // "Add Selected" button click
        { // for each selected item, find its index in the hDbEvent
          // and after that add this item to the DB permanently
          char* caUIN;
          HWND hLV = GetDlgItem(hwndDlg, IDC_CONTACTS);
          HWND hGroupsCombo = GetDlgItem(hwndDlg, IDC_GROUPS);
          HWND hGroupsCheck = GetDlgItem(hwndDlg, IDC_ENABLEGROUPS);
          int curs = SendMessageT(hGroupsCombo, CB_GETCURSEL, 0, 0);
          TCHAR* caGroup = NULL;
          int nGroupId = -1;
          if (curs != CB_ERR && IsWindowEnabled(hGroupsCheck) && SendMessageT(hGroupsCheck, BM_GETCHECK, 0, 0))
          { //got groups, get the one selected in combo
            TCHAR* caGroup = (TCHAR*)_malloca((SendMessageT(hGroupsCombo, CB_GETLBTEXTLEN, curs, 0) + 1) * sizeof(WCHAR));
            SendMessageT(hGroupsCombo, CB_GETLBTEXT, curs, (LPARAM)caGroup);
            nGroupId = SendMessageT(hGroupsCombo, CB_GETITEMDATA, curs, 0);
          }

          for (int i = 0; i < ListView_GetItemCount(hLV); i++)
            if (ListView_GetCheckState(hLV, i))
            {  // found checked contact item, add it
              caUIN = ListView_GetItemTextEx(hLV, i, 0);
              for (int j = 0; j < wndData->cbReceived; j++)   // determine item index in packet
                if (!strcmpnull(wndData->maReceived[j]->mcaUIN, caUIN))
                {
                  char* szProto = GetContactProto(wndData->mhContact);
                  HANDLE hContact = (HANDLE)SRCCallProtoService(szProto, PS_ADDTOLISTBYEVENT, MAKEWPARAM(0, j), (LPARAM)wndData->mhDbEvent);
                  if (hContact && caGroup)
                  { // use newest group API if available
                    if (ServiceExists(MS_CLIST_CONTACTCHANGEGROUP))
                      CallService(MS_CLIST_CONTACTCHANGEGROUP, (WPARAM)hContact, (LPARAM)nGroupId);
                    else
                      DBWriteContactSettingStringT(hContact, "CList", "Group", caGroup);
                  }
                  break;
                }
              SAFE_FREE((void**)&caUIN);
            } // move to next item
          break;
        }                    
        case IDDETAILS:
        { // for each selected item, find its index in the hDbEvent
          // and after that add this item to the DB
          // finally, request Details window for this hContact
          HWND hLV = GetDlgItem(hwndDlg, IDC_CONTACTS);
          for (int i = 0; i < ListView_GetItemCount(hLV); i++)
            if (ListView_GetItemState(hLV, i, LVIS_SELECTED))
            {
              HANDLE hContact = CreateTemporaryContactForItem(hwndDlg, wndData, i);
              if (hContact)
                CallService(MS_USERINFO_SHOWDIALOG, (WPARAM)hContact, 0);
            }
          break;
        }
        case IDCANCEL:
        {
          SendMessageT(hwndDlg, WM_CLOSE, 0, 0);
          break;
        }
        case IDC_ENABLEGROUPS:
        {
          EnableGroupCombo(hwndDlg);
          break;
        }
        case IDC_GROUPS:
        { // rebuild group list on popup
          if (HIWORD(wParam) == CBN_DROPDOWN)
            RebuildGroupCombo(hwndDlg);
          break;
        }
        case ID_POPUP_ADDUSER:
        {
          HANDLE hContact = CreateTemporaryContactForItem(hwndDlg, wndData, wndData->iPopupItem);

          if (hContact)
            DialogAddContactExecute(hwndDlg, hContact);
          break;
        }
        case ID_POPUP_USERDETAILS:
        {
          HANDLE hContact = CreateTemporaryContactForItem(hwndDlg, wndData, wndData->iPopupItem);

          if (hContact)
            CallService(MS_USERINFO_SHOWDIALOG, (WPARAM)hContact, 0 );
          break;
        }
        case ID_POPUP_SENDMESSAGE:
        {
          HANDLE hContact = CreateTemporaryContactForItem(hwndDlg, wndData, wndData->iPopupItem);

          if (hContact)
            CallService(MS_MSG_SENDMESSAGE, (WPARAM)hContact, 0);
          break;   
        }
        case IDC_USERMENU:
        {
          RECT rc;
          HMENU hMenu = (HMENU)CallService(MS_CLIST_MENUBUILDCONTACT, (WPARAM)wndData->mhContact, 0);
          GetWindowRect(GetDlgItem(hwndDlg,IDC_USERMENU), &rc);
          TrackPopupMenu(hMenu, 0, rc.left, rc.bottom, 0, hwndDlg, NULL);
          DestroyMenu(hMenu);
          break;
        }
        case IDC_HISTORY:
          CallService(MS_HISTORY_SHOWCONTACTHISTORY,(WPARAM)wndData->mhContact,0);
          break;
        case IDC_DETAILS:
          CallService(MS_USERINFO_SHOWDIALOG,(WPARAM)wndData->mhContact,0);
          break;
        case IDC_ADD:
          DialogAddContactExecute(hwndDlg, wndData->mhContact);
          break;
      }
      break;
    }
    case WM_CONTEXTMENU:
    {
      HWND hLV = GetDlgItem(hwndDlg, IDC_CONTACTS);
      LVHITTESTINFO lvh;
      RECT rt;

      wndData->iPopupItem = -1;
      if ((HWND)wParam != hLV) break;  // if not our ListView go away
      lvh.pt.x = LOWORD(lParam);
      lvh.pt.y = HIWORD(lParam);
      if (GetWindowRect(hLV, &rt)==0) return FALSE; // ?? why this, some check ??
      ScreenToClient(hLV, &lvh.pt); // convert to ListView local coordinates
      int ci = ListView_HitTest(hLV, &lvh);
      if (ci==-1) break; // mouse is not over any item
      wndData->iPopupItem = ci;
      TrackPopupMenu(GetSubMenu(wndData->mhPopup, 0), TPM_LEFTALIGN|TPM_TOPALIGN, LOWORD(lParam), HIWORD(lParam), 0, hwndDlg, NULL);
      break;
    }
    case HM_EVENTSENT:
    {
      ACKDATA *ack=(ACKDATA*)lParam;
      if (ack->type!=ACKTYPE_SEARCH) break;      // not search ack, go away
      if (ack->hProcess!=wndData->rhSearch) break; //not our search, go away
      if (ack->result==ACKRESULT_DATA) 
      {
        HWND hLV = GetDlgItem(hwndDlg, IDC_CONTACTS);
        PROTOSEARCHRESULT* psr = (PROTOSEARCHRESULT*)ack->lParam;
        LVFINDINFO fi;
        fi.flags = LVFI_STRING;
        fi.psz = wndData->haUin;
        int iLPos = ListView_FindItem(hLV, -1, &fi);
        if (iLPos==-1) iLPos=0;
//        ListView_SetItemText(hLV, iLPos, 0, psr->email);  // not sent by ICQ, and currently unsupported either
        if (strcmpnull(psr->nick, "") && psr->nick) ListView_SetItemText(hLV, iLPos, 1, psr->nick);
        ListView_SetItemText(hLV, iLPos, 2, psr->firstName);
        ListView_SetItemText(hLV, iLPos, 3, psr->lastName);
        break;
      }
      SAFE_FREE((void**)&wndData->haUin);
      break;
    }
    case WM_CLOSE:  // user closed window, so destroy it
    {
      WindowList_Remove(ghRecvWindowList, hwndDlg);
      DestroyWindow(hwndDlg);
      break;
    }
    case WM_DESTROY: // last message received by this dialog, cleanup
    {
      CallService(MS_DB_EVENT_MARKREAD, (WPARAM)wndData->mhContact, (LPARAM)wndData->mhDbEvent);
      Utils_SaveWindowPosition(hwndDlg, NULL, MODULENAME, "");
      ImageList_Destroy(wndData->mhListIcon);
      UnhookEvent(wndData->hHook);
      DestroyMenu(wndData->mhPopup);
      for (int i=0; i < SIZEOF(wndData->hIcons); i++)
        DestroyIcon(wndData->hIcons[i]);
      delete wndData; // automatically calls destructor
      break;
    }
    case WM_MEASUREITEM:
      return CallService(MS_CLIST_MENUMEASUREITEM, wParam, lParam);

    case WM_DRAWITEM:
    {
      DrawProtocolIcon(hwndDlg, lParam, wndData->mhContact);
      return CallService(MS_CLIST_MENUDRAWITEM, wParam, lParam);
    }
    case WM_SIZE:
    { // make the dlg resizeable
      UTILRESIZEDIALOG urd = {0};

      if (IsIconic(hwndDlg)) break;
      urd.cbSize = sizeof(urd);
      urd.hInstance = hInst;
      urd.hwndDlg = hwndDlg;
      urd.lParam = 0; // user-defined
      urd.lpTemplate = MAKEINTRESOURCEA(IDD_RECEIVE);
      urd.pfnResizer = RecvDlg_Resize;
      CallService(MS_UTILS_RESIZEDIALOG, 0, (LPARAM) & urd);
      break;
    }
    case WM_GETMINMAXINFO:
    {
      MINMAXINFO* mmi=(MINMAXINFO*)lParam;
      mmi->ptMinTrackSize.x = 480+2*GetSystemMetrics(SM_CXSIZEFRAME);
      mmi->ptMinTrackSize.y = 130+2*GetSystemMetrics(SM_CYSIZEFRAME);
      break;
    }
    case DM_UPDATETITLE:
    {
      UpdateDialogTitle(hwndDlg, wndData?wndData->mhContact:NULL, "Contacts from");
      if (wndData)
        UpdateDialogAddButton(hwndDlg, wndData->mhContact);
      break;        
    }
  }
  return FALSE;
}