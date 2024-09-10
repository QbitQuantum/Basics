int WINAPI WinMain(HINSTANCE hinstExe, HINSTANCE hinstPrev, LPSTR lpszCmdLine, int nCmdShow)
{
    int                result;
    TCHAR            filename[MAX_PATH];

    {
    OPENFILENAME    ofn;

    // Pick out where our DLL is located. We need to know its location in
    // order to register it as a COM component
    lstrcpy(&filename[0], &OurDllName[0]);
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.lpstrFilter = &FileDlgExt[0];
    ofn.lpstrFile = &filename[0];
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = &FileDlgTitle[0];
    ofn.Flags = OFN_FILEMUSTEXIST|OFN_EXPLORER|OFN_PATHMUSTEXIST;
    result = GetOpenFileName(&ofn);
    }

    if (result > 0)
    {
        HKEY        rootKey;
        HKEY        hKey;
        HKEY        hKey2;
        TCHAR        buffer[39];

        stringFromCLSID(&buffer[0], (REFCLSID)(&CLSID_IExample2));

        // Open "HKEY_LOCAL_MACHINE\Software\Classes"
        if (!RegOpenKeyEx(HKEY_LOCAL_MACHINE, &ClassKeyName[0], 0, KEY_WRITE, &rootKey))
        {
            // Delete ProgID subkey and everything under it
            if (!RegOpenKeyEx(rootKey, &OurProgID[0], 0, KEY_ALL_ACCESS, &hKey))
            {
                RegDeleteKey(hKey, &CLSID_Str[0]);
                RegCloseKey(hKey);
                RegDeleteKey(rootKey, &OurProgID[0]);

                // Delete our CLSID key and everything under it
                if (!RegOpenKeyEx(rootKey, &CLSID_Str[0], 0, KEY_ALL_ACCESS, &hKey))
                {
                    if (!RegOpenKeyEx(hKey, &buffer[0], 0, KEY_ALL_ACCESS, &hKey2))
                    {
                        RegDeleteKey(hKey2, &InprocServer32Name[0]);

                        RegDeleteKey(hKey2, &ProgIDName[0]);

                        RegCloseKey(hKey2);
                        RegDeleteKey(hKey, &buffer[0]);
                    }

                    RegCloseKey(hKey);
                }
            }

            RegCloseKey(rootKey);

            // Unregister type library
            UnRegisterTypeLib(&CLSID_TypeLib, 1, 0, LOCALE_NEUTRAL, SYS_WIN32);
        }

        MessageBox(0, "De-registered IExample2.DLL as a COM component.", &ObjectDescription[0], MB_OK|MB_ICONEXCLAMATION);
    }

    return(0);
}