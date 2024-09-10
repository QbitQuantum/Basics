void PluginDatabase::getPluginPathsInDirectories(HashSet<String>& paths) const
{
    // FIXME: This should be a case insensitive set.
    HashSet<String> uniqueFilenames;

    HANDLE hFind = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATAW findFileData;

    String oldWMPPluginPath;
    String newWMPPluginPath;

    Vector<String>::const_iterator end = m_pluginDirectories.end();
    for (Vector<String>::const_iterator it = m_pluginDirectories.begin(); it != end; ++it) {
        String pattern = *it + "\\*";

        hFind = FindFirstFileW(pattern.charactersWithNullTermination(), &findFileData);

        if (hFind == INVALID_HANDLE_VALUE)
            continue;

        do {
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                continue;

            String filename = String(findFileData.cFileName, wcslen(findFileData.cFileName));
            if ((!filename.startsWith("np", false) || !filename.endsWith("dll", false)) &&
                (!equalIgnoringCase(filename, "Plugin.dll") || !it->endsWith("Shockwave 10", false)))
                continue;

            String fullPath = *it + "\\" + filename;
            if (!uniqueFilenames.add(fullPath).second)
                continue;

            paths.add(fullPath);

            if (equalIgnoringCase(filename, "npdsplay.dll"))
                oldWMPPluginPath = fullPath;
            else if (equalIgnoringCase(filename, "np-mswmp.dll"))
                newWMPPluginPath = fullPath;

        } while (FindNextFileW(hFind, &findFileData) != 0);

        FindClose(hFind);
    }

    addPluginPathsFromRegistry(HKEY_LOCAL_MACHINE, paths);
    addPluginPathsFromRegistry(HKEY_CURRENT_USER, paths);

    // If both the old and new WMP plugin are present in the plugins set, 
    // we remove the old one so we don't end up choosing the old one.
    if (!oldWMPPluginPath.isEmpty() && !newWMPPluginPath.isEmpty())
        paths.remove(oldWMPPluginPath);
}