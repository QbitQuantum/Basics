PPH_STRING PhGetServiceNameFromTag(
    _In_ HANDLE ProcessId,
    _In_ PVOID ServiceTag
    )
{
    static PQUERY_TAG_INFORMATION I_QueryTagInformation = NULL;
    PPH_STRING serviceName = NULL;
    TAG_INFO_NAME_FROM_TAG nameFromTag;

    if (!I_QueryTagInformation)
    {
        I_QueryTagInformation = PhGetModuleProcAddress(L"advapi32.dll", "I_QueryTagInformation");

        if (!I_QueryTagInformation)
            return NULL;
    }

    memset(&nameFromTag, 0, sizeof(TAG_INFO_NAME_FROM_TAG));
    nameFromTag.InParams.dwPid = HandleToUlong(ProcessId);
    nameFromTag.InParams.dwTag = PtrToUlong(ServiceTag);

    I_QueryTagInformation(NULL, eTagInfoLevelNameFromTag, &nameFromTag);

    if (nameFromTag.OutParams.pszName)
    {
        serviceName = PhCreateString(nameFromTag.OutParams.pszName);
        LocalFree(nameFromTag.OutParams.pszName);
    }

    return serviceName;
}