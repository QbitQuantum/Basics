std::string PlayerFileDialogServiceWin::saveFile(const std::string &title,
                                                 const std::string &path) const
{
    std::u16string u16title;
    cocos2d::StringUtils::UTF8ToUTF16(title, u16title);

    WCHAR buff[MAX_PATH + 1] = {0};
    if (path.length() > 0)
    {
        std::u16string u16filename;
        cocos2d::StringUtils::UTF8ToUTF16(path, u16filename);
        wcscpy_s(buff, (WCHAR*)u16filename.c_str());
    }

    OPENFILENAME ofn = {0};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = _hwnd;
    ofn.lpstrFilter = L"All Files (*.*)\0*.*\0";
    ofn.lpstrTitle = (LPCTSTR)u16title.c_str();
    ofn.Flags = OFN_DONTADDTORECENT | OFN_ENABLESIZING | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_LONGNAMES;
    ofn.lpstrFile = buff;
    ofn.nMaxFile = MAX_PATH;

    std::string result;
    if (!GetSaveFileName(&ofn))
    {
        // user cancel dialog, GetSaveFileName() will return FALSE
        DWORD err = CommDlgExtendedError();
        if (err)
        {
            CCLOG("PlayerFileDialogServiceWin::saveFile() - failed, title (%s),  error code = %u", title.c_str(), err);
        }
        return result;
    }

    cocos2d::StringUtils::UTF16ToUTF8((char16_t*)buff, result);
    return result;
}