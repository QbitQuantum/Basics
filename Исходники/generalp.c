/* Property page dialog callback */
INT_PTR CALLBACK
GeneralPageProc(HWND hwndDlg,
                UINT uMsg,
                WPARAM wParam,
                LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_INITDIALOG:
            CreateLanguagesList(GetDlgItem(hwndDlg, IDC_LANGUAGELIST));
            UpdateLocaleSample(hwndDlg, LOCALE_USER_DEFAULT);
            CreateLocationsList(GetDlgItem(hwndDlg, IDC_LOCATION_COMBO));
            if (IsUnattendedSetupEnabled)
            {
                if (VerifyUnattendLCID(hwndDlg))
                {
                    SetNewLocale(UnattendLCID);
                    PostQuitMessage(0);
                }
                return TRUE;
            }
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case IDC_LANGUAGELIST:
                    if (HIWORD(wParam) == CBN_SELCHANGE)
                    {
                        LCID NewLcid;
                        INT iCurSel;

                        iCurSel = SendMessage(hList,
                                              CB_GETCURSEL,
                                              0,
                                              0);
                        if (iCurSel == CB_ERR)
                            break;

                        NewLcid = SendMessage(hList,
                                              CB_GETITEMDATA,
                                              iCurSel,
                                              0);
                        if (NewLcid == (LCID)CB_ERR)
                            break;

                        UpdateLocaleSample(hwndDlg, NewLcid);

                        PropSheet_Changed(GetParent(hwndDlg), hwndDlg);
                    }
                    break;

                case IDC_LOCATION_COMBO:
                    if (HIWORD(wParam) == CBN_SELCHANGE)
                    {
                        PropSheet_Changed(GetParent(hwndDlg), hwndDlg);
                    }
                    break;
                case IDC_SETUP_BUTTON:
                    {
                        LCID NewLcid;
                        INT iCurSel;

                        iCurSel = SendMessage(hList,
                                              CB_GETCURSEL,
                                              0,
                                              0);
                        if (iCurSel == CB_ERR)
                            break;

                        NewLcid = SendMessage(hList,
                                              CB_GETITEMDATA,
                                              iCurSel,
                                              0);
                        if (NewLcid == (LCID)CB_ERR)
                            break;

                         SetupApplet(GetParent(hwndDlg), NewLcid);
                    }
                    break;
            }
            break;

        case WM_NOTIFY:
            {
                LPNMHDR lpnm = (LPNMHDR)lParam;

                if (lpnm->code == (UINT)PSN_APPLY)
                {
                    /* Apply changes */
                    LCID NewLcid;
                    GEOID NewGeoID;
                    INT iCurSel;

                    PropSheet_UnChanged(GetParent(hwndDlg), hwndDlg);

                    /* Acquire new value */
                    iCurSel = SendMessage(hList,
                                          CB_GETCURSEL,
                                          0,
                                          0);
                    if (iCurSel == CB_ERR)
                        break;

                    NewLcid = SendMessage(hList,
                                          CB_GETITEMDATA,
                                          iCurSel,
                                          0);
                    if (NewLcid == (LCID)CB_ERR)
                        break;

                    iCurSel = SendMessage(GetDlgItem(hwndDlg, IDC_LOCATION_COMBO),
                                          CB_GETCURSEL,
                                          0,
                                          0);
                    if (iCurSel == CB_ERR)
                        break;

                    NewGeoID = SendMessage(GetDlgItem(hwndDlg, IDC_LOCATION_COMBO),
                                           CB_GETITEMDATA,
                                           iCurSel,
                                           0);
                    if (NewGeoID == (GEOID)CB_ERR)
                        break;

                    /* Set new locale */
                    SetNewLocale(NewLcid);
                    AddNewKbLayoutsByLcid(NewLcid);
                    SetUserGeoID(NewGeoID);
                    SetNonUnicodeLang(hwndDlg, NewLcid);
                }
            }
            break;
    }

    return FALSE;
}