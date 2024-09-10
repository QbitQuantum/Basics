void InstallDriver( HANDLE DeviceInformation, SP_DEVINFO_DATA* DeviceData )
{
    SP_DEVINSTALL_PARAMS_W deviceInstallParams;
    SP_DRVINFO_DATA_V2_W driverData;
    UINT32 reboot = 0;
    HANDLE module;
    DWORD address;
    BYTE *addr;

    if (!SetupDiSetSelectedDevice(DeviceInformation, DeviceData))
    {
        Log(L"Set Selected Device fail.");
        return;
    }

    Memory_Clear(&deviceInstallParams, sizeof(SP_DEVINSTALL_PARAMS_W));

    if (sizeof(int*) == 8)
    {
        deviceInstallParams.cbSize = 584;
    }
    else
    {
        deviceInstallParams.cbSize = sizeof(SP_DEVINSTALL_PARAMS_W);
    }

    if (!SetupDiGetDeviceInstallParamsW(DeviceInformation, DeviceData, &deviceInstallParams))
    {
        Log(L"Get Device Install Params fail.");
        return;
    }

    String_Copy(deviceInstallParams.DriverPath, L"C:\\mij\\drivers\\MijXinput.inf");

    deviceInstallParams.Flags |= 65536;

    if (!SetupDiSetDeviceInstallParamsW(DeviceInformation, DeviceData, &deviceInstallParams))
    {
        Log(L"Set Device Install Params fail.");
        return;
    }

    if (!SetupDiBuildDriverInfoList(DeviceInformation, DeviceData, SPDIT_COMPATDRIVER))
    {
        Log(L"Building Driver Info List fail.");
        return;
    }

    if (!SetupDiSelectBestCompatDrv(DeviceInformation, DeviceData))
    {
        Log(L"Select Best Compatible Driver fail.");
        return;
    }

    Memory_Clear(&driverData, sizeof(SP_DRVINFO_DATA_V2_W));
    driverData.cbSize = sizeof(SP_DRVINFO_DATA_V2_W);

    if (!SetupDiGetSelectedDriverW(DeviceInformation, DeviceData, &driverData))
    {
        Log(L"Get MotioninJoy Driver fail.");
        return;
    }

    //DiInstallDevice willfully returns 0xE0000235 (ERROR_IN_WOW64) in a WOW64 environment.
    //I don't know if this was a security restraint but there is no reason why this function
    //should not work under WOW64. All we have to do is insert one, literally one jmp patch to
    //skip the WOW64 check and the function succeeds as normal.
    module = Module_GetHandle(L"newdev.dll");
    address = Module_GetProcedureAddress(module, "DiInstallDevice");
    address += 0x134;
    addr = address;

    if ((*addr) == 0x74) //je
    {
        DWORD oldPageProtection = 0;

        //We firstly have to remove page protection of course.
        VirtualProtect(addr, 1, PAGE_EXECUTE_READWRITE, &oldPageProtection);

        //patch to jne
        *addr = 0x75;

        //Lastly, make it look like we were never even there by restoring protection
        VirtualProtect(addr, 1, oldPageProtection, &oldPageProtection);
    }

    if (!DiInstallDevice(NULL, DeviceInformation, DeviceData, &driverData, 0, &reboot))
    {
        Log(L"Install MotioninJoy Driver fail.");
    }
}