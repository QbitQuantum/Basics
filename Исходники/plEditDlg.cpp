BOOL HandleCommandMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int wmID, wmEvent;
    wmID = LOWORD(wParam);
    wmEvent = HIWORD(wParam);

    switch (wmEvent)
    {
    case BN_CLICKED:
        switch (wmID)
        {
        case IDC_ADD:
            {
                SaveLocalizationText(); // save any current changes to the database

                plString buttonText;
                wchar_t buff[256];
                GetDlgItemText(gEditDlg, IDC_ADD, buff, 256);
                buttonText = plString::FromWchar(buff);

                if (buttonText == "Add Element")
                {
                    plAddElementDlg dlg(gCurrentPath);
                    if (dlg.DoPick(gEditDlg))
                    {
                        plString path = dlg.GetValue(); // path is age.set.name
                        if (!pfLocalizationDataMgr::Instance().AddElement(path))
                            MessageBox(gEditDlg, L"Couldn't add new element because one already exists with that name!", L"Error", MB_ICONERROR | MB_OK);
                        else
                        {
                            gCurrentPath = "";
                            plLocTreeView::ClearTreeView(gTreeView);
                            plLocTreeView::FillTreeViewFromData(gTreeView, path);
                            UpdateEditDlg(path);
                        }
                    }
                }
                else if (buttonText == "Add Localization")
                {
                    plAddLocalizationDlg dlg(gCurrentPath);
                    if (dlg.DoPick(gEditDlg))
                    {
                        plString newLanguage = dlg.GetValue();
                        plString ageName, setName, elementName, elementLanguage;
                        SplitLocalizationPath(gCurrentPath, ageName, setName, elementName, elementLanguage);
                        plString key = plString::Format("%s.%s.%s", ageName.c_str(), setName.c_str(), elementName.c_str());
                        if (!pfLocalizationDataMgr::Instance().AddLocalization(key, newLanguage))
                            MessageBox(gEditDlg, L"Couldn't add additional localization!", L"Error", MB_ICONERROR | MB_OK);
                        else
                        {
                            plString path = plString::Format("%s.%s", key.c_str(), newLanguage.c_str());
                            gCurrentPath = "";
                            plLocTreeView::ClearTreeView(gTreeView);
                            plLocTreeView::FillTreeViewFromData(gTreeView, path);
                            UpdateEditDlg(path);
                        }
                    }
                }
                return FALSE;
            }
        case IDC_DELETE:
            {
                SaveLocalizationText(); // save any current changes to the database

                plString messageText = plString::Format("Are you sure that you want to delete %s?", gCurrentPath.c_str());
                int res = MessageBoxW(gEditDlg, messageText.ToWchar(), L"Delete", MB_ICONQUESTION | MB_YESNO);
                if (res == IDYES)
                {
                    plString buttonText;
                    wchar_t buff[256];
                    GetDlgItemText(gEditDlg, IDC_DELETE, buff, 256);
                    buttonText = plString::FromWchar(buff);

                    if (buttonText == "Delete Element")
                    {
                        if (!pfLocalizationDataMgr::Instance().DeleteElement(gCurrentPath))
                            MessageBox(gEditDlg, L"Couldn't delete element!", L"Error", MB_ICONERROR | MB_OK);
                        else
                        {
                            plString path = gCurrentPath;
                            gCurrentPath = "";
                            plLocTreeView::ClearTreeView(gTreeView);
                            plLocTreeView::FillTreeViewFromData(gTreeView, path);
                            UpdateEditDlg(path);
                        }
                    }
                    else if (buttonText == "Delete Localization")
                    {
                        plString ageName, setName, elementName, elementLanguage;
                        SplitLocalizationPath(gCurrentPath, ageName, setName, elementName, elementLanguage);
                        plString key = plString::Format("%s.%s.%s", ageName.c_str(), setName.c_str(), elementName.c_str());
                        if (!pfLocalizationDataMgr::Instance().DeleteLocalization(key, elementLanguage))
                            MessageBox(gEditDlg, L"Couldn't delete localization!", L"Error", MB_ICONERROR | MB_OK);
                        else
                        {
                            plString path = gCurrentPath;
                            gCurrentPath = "";
                            plLocTreeView::ClearTreeView(gTreeView);
                            plLocTreeView::FillTreeViewFromData(gTreeView, path);
                            UpdateEditDlg(path);
                        }
                    }
                }
            }
            return FALSE;
        }
    }
    return (BOOL)DefWindowProc(hWnd, msg, wParam, lParam);
}