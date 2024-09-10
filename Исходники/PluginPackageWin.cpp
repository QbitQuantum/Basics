bool PluginPackage::fetchInfo()
{
    DWORD versionInfoSize, zeroHandle;
    versionInfoSize = GetFileVersionInfoSizeW(const_cast<UChar*>(m_path.charactersWithNullTermination()), &zeroHandle);
    if (versionInfoSize == 0)
        return false;

    OwnArrayPtr<char> versionInfoData = adoptArrayPtr(new char[versionInfoSize]);

    if (!GetFileVersionInfoW(const_cast<UChar*>(m_path.charactersWithNullTermination()),
            0, versionInfoSize, versionInfoData.get()))
        return false;

    m_name = getVersionInfo(versionInfoData.get(), "ProductName");
    m_description = getVersionInfo(versionInfoData.get(), "FileDescription");
    if (m_name.isNull() || m_description.isNull())
        return false;

    VS_FIXEDFILEINFO* info;
    UINT infoSize;
    if (!VerQueryValueW(versionInfoData.get(), L"\\", (LPVOID*) &info, &infoSize) || infoSize < sizeof(VS_FIXEDFILEINFO))
        return false;
    m_moduleVersion.leastSig = info->dwFileVersionLS;
    m_moduleVersion.mostSig = info->dwFileVersionMS;

    if (isPluginBlacklisted())
        return false;

    Vector<String> types;
    getVersionInfo(versionInfoData.get(), "MIMEType").split('|', types);
    Vector<String> extensionLists;
    getVersionInfo(versionInfoData.get(), "FileExtents").split('|', extensionLists);
    Vector<String> descriptions;
    getVersionInfo(versionInfoData.get(), "FileOpenName").split('|', descriptions);

    for (unsigned i = 0; i < types.size(); i++) {
        String type = types[i].lower();
        String description = i < descriptions.size() ? descriptions[i] : "";
        String extensionList = i < extensionLists.size() ? extensionLists[i] : "";

        Vector<String> extensionsVector;
        extensionList.split(',', extensionsVector);

        // Get rid of the extension list that may be at the end of the description string.
        int pos = description.find("(*");
        if (pos != -1) {
            // There might be a space that we need to get rid of.
            if (pos > 1 && description[pos - 1] == ' ')
                pos--;
            description = description.left(pos);
        }

        // Determine the quirks for the MIME types this plug-in supports
        determineQuirks(type);

        m_mimeToExtensions.add(type, extensionsVector);
        m_mimeToDescriptions.add(type, description);
    }

    return true;
}