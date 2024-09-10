void ChromeClient::runOpenPanel(WebCore::Frame*, PassRefPtr<WebCore::FileChooser> chooser)
{
    //cexer 实现文件选择
    wchar_t* pathList = new wchar_t[10 * MAX_PATH];
    memset(pathList, 0, 10 * MAX_PATH * sizeof(wchar_t));

    OPENFILENAMEW ofn = { 0 };
    ofn.Flags = OFN_DONTADDTORECENT|OFN_EXPLORER|OFN_FILEMUSTEXIST|OFN_NONETWORKBUTTON|OFN_PATHMUSTEXIST;
    if (chooser->settings().allowsMultipleFiles)
        ofn.Flags |= OFN_ALLOWMULTISELECT;

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = L"*.*\0*.*\0\0";
    ofn.lpstrFile = pathList;
    ofn.nMaxFile = 10 * MAX_PATH;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrTitle = NULL;
    if (0 != GetOpenFileNameW(&ofn))
    {
        Vector<String> chosenFiles;

        wchar_t* path = pathList;
        while (*path)
        {
            size_t pathLen = wcslen(path);

            String pathString((const UChar*)path, pathLen);
            chosenFiles.append(pathString);

            path += pathLen + 1;
        }

        if (!chosenFiles.isEmpty())
            chooser->chooseFiles(chosenFiles);
    }

    delete [] pathList;
}