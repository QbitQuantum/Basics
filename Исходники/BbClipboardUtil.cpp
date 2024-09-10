bool ClipboardUtil::getAvailableClipboardFormats(std::vector<std::string> *formatsArray)
{
    //KITDIAG_ASSERT(formatsArray);
    ClipboardGuard clipboardGuard(GetClipboardOwner());
    if (!clipboardGuard.isOpen()) {
        return false;
    }

    formatsArray->clear();
    char formatName[100];
    std::string formatNameString;
    UINT uFormat = EnumClipboardFormats(0);
    while (uFormat) {
        if (getStandardClipboardFormatName(&formatNameString, uFormat)) {
            formatsArray->push_back(formatNameString);
        }
        else if (GetClipboardFormatNameA(uFormat, formatName, sizeof(formatName))) {
            formatNameString = formatName;
            formatsArray->push_back(formatNameString);
        }
        uFormat = EnumClipboardFormats(uFormat);
    }
    return true;
}