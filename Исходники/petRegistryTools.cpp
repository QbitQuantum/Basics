// if file extensions not shown in pet, then the dialog boxes from the pet will not show the
// extensions, which means that the dialog watcher will not be able to ascertaion the file
// extensions by parsing the data in the dialog
void ensureFileExtensionsShown(RegKey petUser) {
    std::wstring advancedPath = L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced";
    BYTE zeroes[] = {0,0,0,0};
    std::wstring hideFileExt = L"HideFileExt";
    RegKey advanced = petUser.open(advancedPath);
    if (advanced.isGood()) {
        advanced.setBytesValue(hideFileExt, REG_DWORD, zeroes, 4);
    } else {
        logtools.log(L"explorer/advanced key does not exist for showing file extension");
        RegKey newAdvanced = petUser.create(advancedPath);
        if (newAdvanced.isGood()) {
            newAdvanced.setBytesValue(hideFileExt, REG_DWORD, zeroes, 4);
        } else {logtools.log(L"cannot even create advanced key");}

    }
}