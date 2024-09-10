INT_PTR CALLBACK CDialogPackage::SelectPluginDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        EnableThemeDialogTexture(hWnd, ETDT_ENABLETAB);
        c_Dialog->SetDialogFont(hWnd);

        auto plugins = (std::pair<std::wstring, std::wstring>*)lParam;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)plugins);
    }
    break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_PACKAGESELECTPLUGIN_32BITBROWSE_BUTTON:
        case IDC_PACKAGESELECTPLUGIN_64BITBROWSE_BUTTON:
        {
            WCHAR buffer[MAX_PATH];
            buffer[0] = L'\0';

            OPENFILENAME ofn = { sizeof(OPENFILENAME) };
            ofn.Flags = OFN_FILEMUSTEXIST;
            ofn.lpstrFilter = L"Plugins (.dll)\0*.dll";
            ofn.lpstrTitle = L"Select plugin file";
            ofn.lpstrDefExt = L"dll";
            ofn.nFilterIndex = 0;
            ofn.lpstrFile = buffer;
            ofn.nMaxFile = _countof(buffer);
            ofn.hwndOwner = c_Dialog->GetWindow();

            if (!GetOpenFileName(&ofn))
            {
                break;
            }

            bool x32 = LOWORD(wParam) == IDC_PACKAGESELECTPLUGIN_32BITBROWSE_BUTTON;

            LOADED_IMAGE* loadedImage = ImageLoad(StringUtil::NarrowUTF8(buffer).c_str(), NULL);
            if (loadedImage)
            {
                WORD machine = loadedImage->FileHeader->FileHeader.Machine;
                ImageUnload(loadedImage);

                if ((x32 && machine == IMAGE_FILE_MACHINE_I386) || (!x32 && machine == IMAGE_FILE_MACHINE_AMD64))
                {
                    // Check if same name as other DLL
                    auto plugins = (std::pair<std::wstring, std::wstring>*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
                    const WCHAR* otherName = PathFindFileName(x32 ? plugins->second.c_str() : plugins->first.c_str());
                    if (*otherName && _wcsicmp(otherName, PathFindFileName(buffer)) != 0)
                    {
                        MessageBox(hWnd, L"Plugins must have same name.", L"Rainmeter Skin Packager", MB_OK | MB_TOPMOST);
                        break;
                    }

                    PathSetDlgItemPath(hWnd, x32 ? IDC_PACKAGESELECTPLUGIN_32BIT_EDIT : IDC_PACKAGESELECTPLUGIN_64BIT_EDIT, buffer);

                    (x32 ? plugins->first : plugins->second) = buffer;

                    if (!plugins->first.empty() && !plugins->second.empty())
                    {
                        // Enable Add button if both plugins have been selected
                        EnableWindow(GetDlgItem(hWnd, IDOK), TRUE);
                    }
                    break;
                }
            }

            MessageBox(hWnd, L"Invalid plugin.", L"Rainmeter Skin Packager", MB_OK | MB_TOPMOST);
        }
        break;

        case IDOK:
            EndDialog(hWnd, 1);
            break;
        }
        break;

    case WM_CLOSE:
        EndDialog(hWnd, 0);
        break;

    default:
        return FALSE;
    }

    return TRUE;
}