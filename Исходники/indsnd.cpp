INT_PTR CALLBACK DlgProcFiltering(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HANDLE hItemAll;
    switch (msg)
    {
    case WM_INITDIALOG:
    {
        TranslateDialogDefault(hwndDlg);

        HIMAGELIST hImageList = ImageList_Create(GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), IsWinVerXPPlus() ? ILC_COLOR32 : ILC_COLOR16 | ILC_MASK, 3, 3);

        ImageList_AddIcon(hImageList, LoadIcon(hInst,MAKEINTRESOURCE(IDI_SOUND)));
        SendDlgItemMessage(hwndDlg,IDC_SOUNDICON,STM_SETICON, (WPARAM)ImageList_GetIcon(hImageList, EXTRA_IMAGE_SOUND, ILD_NORMAL), 0);
        ImageList_AddIcon(hImageList, LoadIcon(hInst, MAKEINTRESOURCE(IDI_POPUP)));
        SendDlgItemMessage(hwndDlg, IDC_POPUPICON, STM_SETICON, (WPARAM)ImageList_GetIcon(hImageList, EXTRA_IMAGE_POPUP, ILD_NORMAL), 0);
        ImageList_AddIcon(hImageList, LoadIcon(hInst,MAKEINTRESOURCE(IDI_XSTATUS)));
        SendDlgItemMessage(hwndDlg, IDC_XSTATUSICON, STM_SETICON, (WPARAM)ImageList_GetIcon(hImageList, EXTRA_IMAGE_XSTATUS, ILD_NORMAL), 0);
        ImageList_AddIcon(hImageList, LoadIcon(hInst,MAKEINTRESOURCE(IDI_LOGGING)));
        SendDlgItemMessage(hwndDlg, IDC_LOGGINGICON, STM_SETICON, (WPARAM)ImageList_GetIcon(hImageList, EXTRA_IMAGE_LOGGING, ILD_NORMAL), 0);
        ImageList_AddIcon(hImageList, LoadIcon(hInst,MAKEINTRESOURCE(IDI_DISABLEALL)));
        SendDlgItemMessage(hwndDlg, IDC_DISABLEALLICON, STM_SETICON, (WPARAM)ImageList_GetIcon(hImageList, EXTRA_IMAGE_DISABLEALL, ILD_NORMAL), 0);
        ImageList_AddIcon(hImageList, LoadIcon(hInst,MAKEINTRESOURCE(IDI_ENABLEALL)));
        SendDlgItemMessage(hwndDlg, IDC_ENABLEALLICON, STM_SETICON, (WPARAM)ImageList_GetIcon(hImageList, EXTRA_IMAGE_ENABLEALL, ILD_NORMAL), 0);

        ImageList_AddIcon(hImageList, LoadSkinnedIcon(SKINICON_OTHER_SMALLDOT));

        SendDlgItemMessage(hwndDlg, IDC_INDSNDLIST, CLM_SETEXTRAIMAGELIST, 0, (LPARAM)hImageList);
        SendDlgItemMessage(hwndDlg, IDC_INDSNDLIST, CLM_SETEXTRACOLUMNS, 6, 0);

        HWND hList = GetDlgItem(hwndDlg, IDC_INDSNDLIST);
        ResetListOptions(hList);

        CLCINFOITEM cii = {0};
        cii.cbSize = sizeof(cii);
        cii.flags = CLCIIF_GROUPFONT;
        cii.pszText = TranslateT("** All contacts **");
        hItemAll = (HANDLE)SendDlgItemMessage(hwndDlg, IDC_INDSNDLIST, CLM_ADDINFOITEM, 0, (LPARAM)&cii);

        return TRUE;
    }
    case WM_SETFOCUS:
    {
        SetFocus(GetDlgItem(hwndDlg, IDC_INDSNDLIST));
        break;
    }
    case WM_NOTIFY:
    {
        HWND hList = GetDlgItem(hwndDlg, IDC_INDSNDLIST);
        switch(((LPNMHDR)lParam)->idFrom)
        {
        case IDC_INDSNDLIST:
            switch (((LPNMHDR)lParam)->code)
            {
            case CLN_NEWCONTACT:
            case CLN_LISTREBUILT:
                SetAllContactsIcons(hList);
            //fall through
            case CLN_CONTACTMOVED:
                SetGroupsIcons(hList, (HANDLE)SendMessage(hList, CLM_GETNEXTITEM, CLGN_ROOT, 0), hItemAll, NULL);
                break;
            case CLN_OPTIONSCHANGED:
                ResetListOptions(hList);
                break;
            case NM_CLICK:
            {
                NMCLISTCONTROL *nm = (NMCLISTCONTROL*)lParam;
                DWORD hitFlags;

                // Make sure we have an extra column
                if (nm->iColumn == -1) break;

                // Find clicked item
                HANDLE hItem = (HANDLE)SendMessage(hList, CLM_HITTEST, (WPARAM)&hitFlags, MAKELPARAM(nm->pt.x, nm->pt.y));
                if (hItem == NULL) break;
                if(!(hitFlags & CLCHT_ONITEMEXTRA)) break;

                int itemType = SendMessage(hList, CLM_GETITEMTYPE, (WPARAM)hItem, 0);

                // Get image in clicked column
                int image = GetExtraImage(hList, hItem, nm->iColumn);
                if (image == EXTRA_IMAGE_DOT)
                    image = nm->iColumn;
                else if (image >= EXTRA_IMAGE_SOUND && image <= EXTRA_IMAGE_LOGGING)
                    image = EXTRA_IMAGE_DOT;

                // Get item type (contact, group, etc...)
                if (itemType == CLCIT_CONTACT)
                {
                    if (image == EXTRA_IMAGE_DISABLEALL)
                    {
                        for (int i = 0; i < 4; i++)
                            SetExtraImage(hList, hItem, i, EXTRA_IMAGE_DOT);
                    }
                    else if (image == EXTRA_IMAGE_ENABLEALL)
                    {
                        for (int i = 0; i < 4; i++)
                            SetExtraImage(hList, hItem, i, i);
                    }
                    else
                    {
                        SetExtraImage(hList, hItem, nm->iColumn, image);
                    }
                }
                else if (itemType == CLCIT_INFO || itemType == CLCIT_GROUP)
                {
                    if (itemType == CLCIT_GROUP)
                        hItem = (HANDLE)SendMessage(hList, CLM_GETNEXTITEM, CLGN_CHILD, (LPARAM)hItem);

                    if (hItem)
                    {
                        if (image == EXTRA_IMAGE_DISABLEALL)
                        {
                            for (int i = 0; i < 4; i++)
                                SetAllChildrenIcons(hList, hItem, i, EXTRA_IMAGE_DOT);
                        }
                        else if (image == EXTRA_IMAGE_ENABLEALL)
                        {
                            for (int i = 0; i < 4; i++)
                                SetAllChildrenIcons(hList, hItem, i, i);
                        }
                        else
                        {
                            SetAllChildrenIcons(hList, hItem, nm->iColumn, image);
                        }
                    }
                }

                // Update the all/none icons
                SetGroupsIcons(hList, (HANDLE)SendMessage(hList, CLM_GETNEXTITEM, CLGN_ROOT, 0), hItemAll, NULL);
                // Activate Apply button
                SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
                break;
            }
            }
            break;
        case 0:
            switch (((LPNMHDR)lParam)->code)
            {
            case PSN_APPLY:
            {
                HANDLE hContact = (HANDLE)CallService(MS_DB_CONTACT_FINDFIRST, 0, 0);
                do
                {
                    HANDLE hItem = (HANDLE)SendMessage(hList, CLM_FINDCONTACT, (WPARAM)hContact, 0);
                    if (hItem)
                    {
                        if (GetExtraImage(hList, hItem, EXTRA_IMAGE_SOUND) == EXTRA_IMAGE_SOUND)
                            DBDeleteContactSetting(hContact, MODULE, "EnableSounds");
                        else
                            DBWriteContactSettingByte(hContact, MODULE, "EnableSounds", 0);

                        if (GetExtraImage(hList, hItem, EXTRA_IMAGE_POPUP) == EXTRA_IMAGE_POPUP)
                            DBDeleteContactSetting(hContact, MODULE, "EnablePopups");
                        else
                            DBWriteContactSettingByte(hContact, MODULE, "EnablePopups", 0);

                        if(GetExtraImage(hList, hItem, EXTRA_IMAGE_XSTATUS) == EXTRA_IMAGE_XSTATUS)
                            DBDeleteContactSetting(hContact, MODULE, "EnableXStatusNotify");
                        else
                            DBWriteContactSettingByte(hContact, MODULE, "EnableXStatusNotify", 0);

                        if (GetExtraImage(hList, hItem, EXTRA_IMAGE_LOGGING) == EXTRA_IMAGE_LOGGING)
                            DBDeleteContactSetting(hContact, MODULE, "EnableLogging");
                        else
                            DBWriteContactSettingByte(hContact, MODULE, "EnableLogging", 0);

                    }
                } while(hContact = (HANDLE)CallService(MS_DB_CONTACT_FINDNEXT, (WPARAM)hContact, 0));

                return TRUE;
            }
            }
            break;
        }
        break;
    }
    case WM_DESTROY:
    {
        HIMAGELIST hImageList = (HIMAGELIST)SendMessage(GetDlgItem(hwndDlg, IDC_INDSNDLIST), CLM_GETEXTRAIMAGELIST, 0, 0);
        for (int i = 0; i < ImageList_GetImageCount(hImageList); i++)
            DestroyIcon(ImageList_GetIcon(hImageList, i, ILD_NORMAL));
        ImageList_Destroy(hImageList);
        break;
    }
    }
    return FALSE;
}