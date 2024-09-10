int uninstallCMUDriver()
{
    GUID guid = t1394CmdrGetGUID();
    HDEVINFO hDI = SetupDiGetClassDevs(&guid,NULL,NULL,DIGCF_DEVICEINTERFACE);
    if(hDI != INVALID_HANDLE_VALUE)
    {
        SP_DEVINFO_DATA devInfoData;
        int index = 0;
        devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
        while(SetupDiEnumDeviceInfo(hDI,index,&devInfoData))
        {
            printf(" - Device %d:\n",index);
            if(index == 0)
            {
                // look for OEM inf files
                if(SetupDiBuildDriverInfoList(hDI,&devInfoData,SPDIT_COMPATDRIVER))
                {
                    SP_DRVINFO_DATA drvInfoData;
                    drvInfoData.cbSize = sizeof(SP_DRVINFO_DATA);
                    int driverIndex = 0;
                    while(SetupDiEnumDriverInfo(hDI,&devInfoData,SPDIT_COMPATDRIVER,driverIndex++,&drvInfoData))
                    {
                        SP_DRVINFO_DETAIL_DATA drvInfoDetail;
                        drvInfoDetail.cbSize = sizeof(SP_DRVINFO_DETAIL_DATA);
                        BOOL ret = SetupDiGetDriverInfoDetail(hDI,&devInfoData,&drvInfoData,&drvInfoDetail,drvInfoDetail.cbSize,NULL);
                        if(ret || GetLastError() == ERROR_INSUFFICIENT_BUFFER)
                        {
                            printf("    - has OEM inf file '%s'\n",drvInfoDetail.InfFileName);
                            if(!DeleteFile(drvInfoDetail.InfFileName))
                            {
                                printf("      - could not delete '%s' : %d",drvInfoDetail.InfFileName,GetLastError());
                            }
                            drvInfoDetail.InfFileName[lstrlen(drvInfoDetail.InfFileName) - 3] = 'p';
                            if(!DeleteFile(drvInfoDetail.InfFileName))
                            {
                                printf("      - could not delete '%s' : %d",drvInfoDetail.InfFileName,GetLastError());
                            }
                        } else {
                            printf("    - SetupDiGetDriverInfoDetail: %d\n",GetLastError());
                        }
                    }
                
                    if(GetLastError() != ERROR_NO_MORE_ITEMS)
                    {
                        printf("    - SetupDiEnumDriverInfo: %d\n",GetLastError());
                    }

                    SetupDiDestroyDriverInfoList(hDI,&devInfoData,SPDIT_COMPATDRIVER);
                } else {
                    printf("    - SetupDiEnumDriverInfo: %d\n",GetLastError());
                }
            } // else already nuked oem inf files

            if(SetupDiCallClassInstaller(DIF_REMOVE,hDI,&devInfoData))
            {
                printf("    - has been removed!\n");
            } else {
                printf("    - could not be removed: %d\n",GetLastError());
            }

            index++;
        }

		if(index == 0)
		{
			printf("No Devices Found!\n");
		}

        SetupDiDestroyDeviceInfoList(hDI);
    } else {
        printf("Failed to get class devs!\n");
    }
	return 0;
}