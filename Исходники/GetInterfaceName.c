static
VOID
test_GetInterfaceName(VOID)
{
    PIP_INTERFACE_INFO pInfo = NULL;
    ULONG ulOutBufLen = 0;
    DWORD ApiReturn;
    WCHAR Name[MAX_ADAPTER_NAME];
    UNICODE_STRING GuidString;
    GUID AdapterGUID;
    HINSTANCE hIpHlpApi;

    ApiReturn = GetInterfaceInfo(pInfo, &ulOutBufLen);
    ok(ApiReturn == ERROR_INSUFFICIENT_BUFFER,
       "GetInterfaceInfo(pInfo, &ulOutBufLen) returned %ld, expected ERROR_INSUFFICIENT_BUFFER\n",
       ApiReturn);
    if (ApiReturn != ERROR_INSUFFICIENT_BUFFER)
    {
        skip("Can't determine size of IP_INTERFACE_INFO. Can't proceed\n");
        return;
    }

    pInfo = (IP_INTERFACE_INFO *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, ulOutBufLen);
    if (pInfo == NULL)
    {
        skip("pInfo is NULL. Can't proceed\n");
        return;
    }

    ApiReturn = GetInterfaceInfo(pInfo, &ulOutBufLen);
    ok(ApiReturn == NO_ERROR,
        "GetInterfaceInfo(pInfo, &ulOutBufLen) returned %ld, expected NO_ERROR\n",
        ApiReturn);
    if (ApiReturn != NO_ERROR || ulOutBufLen == 0)
    {
        skip("GetInterfaceInfo failed with error %ld. Can't proceed\n", ApiReturn);
        return;
    }

    if (pInfo->NumAdapters > 0)
        CopyMemory(&Name, &pInfo->Adapter[0].Name, sizeof(Name));

    if (pInfo->NumAdapters == 0)
    {
        HeapFree(GetProcessHeap(), 0, pInfo);
        skip("pInfo->NumAdapters = 0. Can't proceed\n");
        return;
    }
    trace("pInfo->NumAdapters: %lu\n", pInfo->NumAdapters);

    HeapFree(GetProcessHeap(), 0, pInfo);

    ApiReturn = wcsncmp(Name, L"\\DEVICE\\TCPIP_", 14);
    ok(ApiReturn == 0,
       "wcsncmp(Name, L\"\\DEVICE\\TCPIP_\", 14) returned %ld, expected 0\n",
       ApiReturn);
    if (ApiReturn != 0)
    {
        if (wcslen(Name) == 0)
        {
            skip("pInfo->Adapter[0].Name is empty. Can't proceed\n");
            return;
        }
        else
        {
            // workaround for ReactOS
            trace("pInfo->Adapter[0].Name = \"%ls\" is incorrect.\n", Name);
            RtlInitUnicodeString(&GuidString, &Name[0]);
        }
    }
    else
    {
        RtlInitUnicodeString(&GuidString, &Name[14]);
    }

    ApiReturn = RtlGUIDFromString(&GuidString, &AdapterGUID);
    if (ApiReturn != 0)
    {
        skip("RtlGUIDFromString failed. Can't proceed\n");
        return;
    }

    hIpHlpApi = GetModuleHandleW(L"iphlpapi.dll");
    if (!hIpHlpApi)
    {
        skip("Failed to load iphlpapi.dll. Can't proceed\n");
        return;
    }

    pNhGetInterfaceNameFromGuid = (void *)GetProcAddress(hIpHlpApi, "NhGetInterfaceNameFromGuid");

    if (!pNhGetInterfaceNameFromGuid)
        skip("NhGetInterfaceNameFromGuid not found. Can't proceed\n");
    else
        test_NhGetInterfaceNameFromGuid(AdapterGUID, 0, 0);

    pNhGetInterfaceNameFromDeviceGuid = (void *)GetProcAddress(hIpHlpApi, "NhGetInterfaceNameFromDeviceGuid");

    if (!pNhGetInterfaceNameFromDeviceGuid)
        skip("NhGetInterfaceNameFromDeviceGuid not found. Can't proceed\n");
    else
        test_NhGetInterfaceNameFromDeviceGuid(AdapterGUID, 1, 0);
}