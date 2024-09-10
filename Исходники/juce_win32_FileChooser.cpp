void FileChooser::showPlatformDialog (Array<File>& results, const String& title_, const File& currentFileOrDirectory,
                                      const String& filter, bool selectsDirectory, bool /*selectsFiles*/,
                                      bool isSaveDialogue, bool warnAboutOverwritingExistingFiles,
                                      bool selectMultipleFiles, FilePreviewComponent* extraInfoComponent)
{
    using namespace FileChooserHelpers;

    const String title (title_);
    HeapBlock<WCHAR> files;
    const int charsAvailableForResult = 32768;
    files.calloc (charsAvailableForResult + 1);
    int filenameOffset = 0;

    FileChooserCallbackInfo info;

    // use a modal window as the parent for this dialog box
    // to block input from other app windows
    Component parentWindow (String::empty);
    const Rectangle<int> mainMon (Desktop::getInstance().getDisplays().getMainDisplay().userArea);
    parentWindow.setBounds (mainMon.getX() + mainMon.getWidth() / 4,
                            mainMon.getY() + mainMon.getHeight() / 4,
                            0, 0);
    parentWindow.setOpaque (true);
    parentWindow.setAlwaysOnTop (areThereAnyAlwaysOnTopWindows());
    parentWindow.addToDesktop (0);

    if (extraInfoComponent == nullptr)
        parentWindow.enterModalState();

    if (currentFileOrDirectory.isDirectory())
    {
        info.initialPath = currentFileOrDirectory.getFullPathName();
    }
    else
    {
        currentFileOrDirectory.getFileName().copyToUTF16 (files, charsAvailableForResult * sizeof (WCHAR));
        info.initialPath = currentFileOrDirectory.getParentDirectory().getFullPathName();
    }

    if (selectsDirectory)
    {
        BROWSEINFO bi = { 0 };
        bi.hwndOwner = (HWND) parentWindow.getWindowHandle();
        bi.pszDisplayName = files;
        bi.lpszTitle = title.toWideCharPointer();
        bi.lParam = (LPARAM) &info;
        bi.lpfn = browseCallbackProc;
       #ifdef BIF_USENEWUI
        bi.ulFlags = BIF_USENEWUI | BIF_VALIDATE;
       #else
        bi.ulFlags = 0x50;
       #endif

        LPITEMIDLIST list = SHBrowseForFolder (&bi);

        if (! SHGetPathFromIDListW (list, files))
        {
            files[0] = 0;
            info.returnedString = String::empty;
        }

        LPMALLOC al;
        if (list != 0 && SUCCEEDED (SHGetMalloc (&al)))
            al->Free (list);

        if (info.returnedString.isNotEmpty())
        {
            results.add (File (String (files)).getSiblingFile (info.returnedString));
            return;
        }
    }
    else
    {
        DWORD flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR | OFN_HIDEREADONLY;

        if (warnAboutOverwritingExistingFiles)
            flags |= OFN_OVERWRITEPROMPT;

        if (selectMultipleFiles)
            flags |= OFN_ALLOWMULTISELECT;

        if (extraInfoComponent != nullptr)
        {
            flags |= OFN_ENABLEHOOK;

            info.customComponent = new CustomComponentHolder (extraInfoComponent);
            info.customComponent->enterModalState();
        }

        const int filterSpaceNumChars = 2048;
        HeapBlock<WCHAR> filters;
        filters.calloc (filterSpaceNumChars);
        const int bytesWritten = filter.copyToUTF16 (filters.getData(), filterSpaceNumChars * sizeof (WCHAR));
        filter.copyToUTF16 (filters + (bytesWritten / sizeof (WCHAR)),
                            (int) ((filterSpaceNumChars - 1) * sizeof (WCHAR) - bytesWritten));

        OPENFILENAMEW of = { 0 };
        String localPath (info.initialPath);

       #ifdef OPENFILENAME_SIZE_VERSION_400W
        of.lStructSize = OPENFILENAME_SIZE_VERSION_400W;
       #else
        of.lStructSize = sizeof (of);
       #endif
        of.hwndOwner = (HWND) parentWindow.getWindowHandle();
        of.lpstrFilter = filters.getData();
        of.nFilterIndex = 1;
        of.lpstrFile = files;
        of.nMaxFile = charsAvailableForResult;
        of.lpstrInitialDir = localPath.toWideCharPointer();
        of.lpstrTitle = title.toWideCharPointer();
        of.Flags = flags;
        of.lCustData = (LPARAM) &info;

        if (extraInfoComponent != nullptr)
            of.lpfnHook = &openCallback;

        if (! (isSaveDialogue ? GetSaveFileName (&of)
                              : GetOpenFileName (&of)))
            return;

        filenameOffset = of.nFileOffset;
    }

    if (selectMultipleFiles && filenameOffset > 0 && files [filenameOffset - 1] == 0)
    {
        const WCHAR* filename = files + filenameOffset;

        while (*filename != 0)
        {
            results.add (File (String (files) + "\\" + String (filename)));
            filename += wcslen (filename) + 1;
        }
    }
    else if (files[0] != 0)
    {
        results.add (File (String (files)));
    }
}