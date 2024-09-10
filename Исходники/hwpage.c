static VOID
BuildDevicesList(IN PHARDWARE_PAGE_DATA hpd)
{
    PHWCLASSDEVINFO ClassDevInfo, LastClassDevInfo;
    SP_DEVINFO_DATA DevInfoData;

    DevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    ClassDevInfo = hpd->ClassDevInfo;
    LastClassDevInfo = ClassDevInfo + hpd->NumberOfGuids;

    while (ClassDevInfo != LastClassDevInfo)
    {
        ClassDevInfo->ImageIndex = -1;

        /* open a class device handle for the GUID we're processing */
        ClassDevInfo->hDevInfo = SetupDiGetClassDevs(&ClassDevInfo->Guid,
                                                     NULL,
                                                     hpd->hWnd,
                                                     DIGCF_PRESENT | DIGCF_PROFILE);
        if (ClassDevInfo->hDevInfo != INVALID_HANDLE_VALUE)
        {
            DWORD MemberIndex = 0;

            SetupDiGetClassImageIndex(&hpd->ClassImageListData,
                                      &ClassDevInfo->Guid,
                                      &ClassDevInfo->ImageIndex);

            /* enumerate all devices in the class */
            while (SetupDiEnumDeviceInfo(ClassDevInfo->hDevInfo,
                                         MemberIndex++,
                                         &DevInfoData))
            {
                BOOL HideDevice = FALSE;

                if (ClassDevInfo->HwDevInfo != NULL)
                {
                    PHWDEVINFO HwNewDevInfo = HeapReAlloc(GetProcessHeap(),
                                                          0,
                                                          ClassDevInfo->HwDevInfo,
                                                          (ClassDevInfo->ItemCount + 1) *
                                                              sizeof(HWDEVINFO));
                    if (HwNewDevInfo != NULL)
                    {
                        ClassDevInfo->HwDevInfo = HwNewDevInfo;
                    }
                    else
                    {
                        ERR("Unable to allocate memory for %d SP_DEVINFO_DATA structures!\n",
                            ClassDevInfo->ItemCount + 1);
                        break;
                    }
                }
                else
                {
                    ClassDevInfo->HwDevInfo = HeapAlloc(GetProcessHeap(),
                                                        0,
                                                        sizeof(HWDEVINFO));
                    if (ClassDevInfo->HwDevInfo == NULL)
                    {
                        ERR("Unable to allocate memory for a SP_DEVINFO_DATA structures!\n");
                        break;
                    }
                }

                /* Find out if the device should be hidden by default */
                IsDeviceHidden(DevInfoData.DevInst,
                               NULL,
                               &HideDevice);

                /* save all information for the current device */
                ClassDevInfo->HwDevInfo[ClassDevInfo->ItemCount].ClassDevInfo = ClassDevInfo;
                ClassDevInfo->HwDevInfo[ClassDevInfo->ItemCount].DevInfoData = DevInfoData;
                ClassDevInfo->HwDevInfo[ClassDevInfo->ItemCount++].HideDevice = HideDevice;
            }
        }

        ClassDevInfo++;
    }
}