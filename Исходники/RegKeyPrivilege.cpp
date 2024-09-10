bool RegKeyPrivilegeAquireRestore::Restore()
{
    XL_INFO_FUNCTION();

    if (!m_bBackedup)
    {
        return false;
    }

    HKEY hKey = nullptr;

    LSTATUS lRes = RegOpenKeyEx(m_hRootKey,
                   m_strSubKey,
                   0,
                   m_samDesired,
                   &hKey);

    if (lRes != ERROR_SUCCESS || hKey == nullptr)
    {
        XL_ERROR(_T("Failed to open Key: %s."), (LPCTSTR)m_strSubKey);
        return false;
    }

    XL_ON_BLOCK_EXIT(RegCloseKey, hKey);

    PSECURITY_DESCRIPTOR pSd = (PSECURITY_DESCRIPTOR)m_pOldSd.RawPointer();
    lRes = RegSetKeySecurity(hKey, m_SecurityInformation, pSd);

    if (lRes != ERROR_SUCCESS)
    {
        XL_ERROR(_T("Failed to restore security information to Key: %s."), (LPCTSTR)m_strSubKey);
        return false;
    }

    m_bBackedup = false;

    return true;
}