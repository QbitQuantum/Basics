VOID
AddResourceItems(
    IN PDEVADVPROP_INFO dap,
    IN HWND hWndDevList)
{
    HKEY hKey;
    WCHAR szBuffer[100];
    WCHAR szDetail[100];
    BYTE szData[512];
    DWORD dwSize;
    PCM_RESOURCE_LIST ResourceList;
    LONG Result;
    ULONG ItemCount = 0, Index;

    wsprintf(szBuffer, L"SYSTEM\\CurrentControlSet\\Enum\\%s\\LogConf", dap->szDeviceID);
    Result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, szBuffer, 0, KEY_READ, &hKey);
    if (Result != ERROR_SUCCESS)
    {
        /* failed to open device instance log conf dir */
        return;
    }

    dwSize = sizeof(szData);
    Result = RegQueryValueExW(hKey, L"BootConfig", NULL, NULL, szData, &dwSize);

    RegCloseKey(hKey);
    if (Result != ERROR_SUCCESS)
    {
        /* failed to query resources */
        return;
    }

    ResourceList = (PCM_RESOURCE_LIST)szData;

    for (Index = 0; Index < ResourceList->List[0].PartialResourceList.Count; Index++)
    {
         PCM_PARTIAL_RESOURCE_DESCRIPTOR Descriptor = &ResourceList->List[0].PartialResourceList.PartialDescriptors[Index];
         if (Descriptor->Type == CmResourceTypeInterrupt)
         {
             if (LoadString(hDllInstance, IDS_RESOURCE_INTERRUPT, szBuffer, sizeof(szBuffer) / sizeof(szBuffer[0])))
             {
                 wsprintf(szDetail, L"0x%08x (%d)", Descriptor->u.Interrupt.Level, Descriptor->u.Interrupt.Vector);
                 InsertListItem(hWndDevList, ItemCount, szBuffer, szDetail);
                 ItemCount++;
             }
         }
         else if (Descriptor->Type == CmResourceTypePort)
         {
             if (LoadString(hDllInstance, IDS_RESOURCE_PORT, szBuffer, sizeof(szBuffer) / sizeof(szBuffer[0])))
             {
                 wsprintf(szDetail, L"%08lx - %08lx", Descriptor->u.Port.Start.LowPart, Descriptor->u.Port.Start.LowPart + Descriptor->u.Port.Length - 1);
                 InsertListItem(hWndDevList, ItemCount, szBuffer, szDetail);
                 ItemCount++;
             }
         }
         else if (Descriptor->Type == CmResourceTypeMemory)
         {
             if (LoadString(hDllInstance, IDS_RESOURCE_MEMORY_RANGE, szBuffer, sizeof(szBuffer) / sizeof(szBuffer[0])))
             {
                 wsprintf(szDetail, L"%08I64x - %08I64x", Descriptor->u.Memory.Start.QuadPart, Descriptor->u.Memory.Start.QuadPart + Descriptor->u.Memory.Length - 1);
                 InsertListItem(hWndDevList, ItemCount, szBuffer, szDetail);
                 ItemCount++;
             }
         }
         else if (Descriptor->Type == CmResourceTypeDma)
         {
             if (LoadString(hDllInstance, IDS_RESOURCE_DMA, szBuffer, sizeof(szBuffer) / sizeof(szBuffer[0])))
             {
                 wsprintf(szDetail, L"%08ld", Descriptor->u.Dma.Channel);
                 InsertListItem(hWndDevList, ItemCount, szBuffer, szDetail);
                 ItemCount++;
             }
         }
    }
}