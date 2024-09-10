bool
CClassNode::SetupNode()
{
    DWORD RequiredSize, Type, Size;
    DWORD Success;
    HKEY hKey;

    // Open the registry key for this class
    hKey = SetupDiOpenClassRegKeyExW(&m_ClassGuid,
                                     MAXIMUM_ALLOWED,
                                     DIOCR_INSTALLER,
                                     NULL,
                                     0);
    if (hKey != INVALID_HANDLE_VALUE)
    {
        Size = DISPLAY_NAME_LEN;
        Type = REG_SZ;

        // Lookup the class description (win7+)
        Success = RegQueryValueExW(hKey,
                                   L"ClassDesc",
                                   NULL,
                                   &Type,
                                   (LPBYTE)m_DisplayName,
                                   &Size);
        if (Success == ERROR_SUCCESS)
        {
            // Check if the string starts with an @
            if (m_DisplayName[0] == L'@')
            {
                // The description is located in a module resource
                Success = ConvertResourceDescriptorToString(m_DisplayName, DISPLAY_NAME_LEN);
            }
        }
        else if (Success == ERROR_FILE_NOT_FOUND)
        {
            // WinXP stores the description in the default value
            Success = RegQueryValueExW(hKey,
                                       NULL,
                                       NULL,
                                       &Type,
                                       (LPBYTE)m_DisplayName,
                                       &Size);
        }

        // Close the registry key
        RegCloseKey(hKey);
    }
    else
    {
        Success = GetLastError();
    }

    // Check if we failed to get the class description
    if (Success != ERROR_SUCCESS)
    {
        // Use the class name as the description
        RequiredSize = DISPLAY_NAME_LEN;
        (VOID)SetupDiClassNameFromGuidW(&m_ClassGuid,
                                        m_DisplayName,
                                        RequiredSize,
                                        &RequiredSize);
    }

    // Get the image index for this class
    (VOID)SetupDiGetClassImageIndex(m_ImageListData,
                                    &m_ClassGuid,
                                    &m_ClassImage);

    return true;
}