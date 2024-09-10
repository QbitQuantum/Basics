DWORD
InstallInfOnDevice(
    IN HWND hWnd,
    HDEVINFO DeviceInfoSet,
    PSP_DEVINFO_DATA DeviceInfoData,
    PTSTR Inf,
    BOOL DelayInstall
    )
{
    DWORD Err = NO_ERROR;
    SP_DEVINSTALL_PARAMS DeviceInstallParams;
    BOOL Reboot = FALSE;

    if (!SetupDiSetSelectedDevice(DeviceInfoSet, DeviceInfoData)) {
        Err = GetLastError();
        goto exit;
    }

    DeviceInstallParams.cbSize = sizeof(DeviceInstallParams);
    if (!SetupDiGetDeviceInstallParams(DeviceInfoSet,
                                       DeviceInfoData,
                                       &DeviceInstallParams)) {
        Err = GetLastError();
        goto exit;
    }

    //
    // Set DriverPath to the path of the INF that we want to install from.
    // Set the DI_ENUMSINGLEINFO so setupapi builds up a driver list just from
    //   this specific INF.
    // Set DI_DONOTCALLCONFIGMG so that we won't call kernel PnP when installing
    //   the driver.  This will do all the install actions except stop/start the 
    //   device so it won't start using the new driver until a reboot.
    //
    StringCchCopy(DeviceInstallParams.DriverPath, 
                  SIZECHARS(DeviceInstallParams.DriverPath),
                  Inf);
    DeviceInstallParams.hwndParent = hWnd;
    DeviceInstallParams.Flags |= (DI_ENUMSINGLEINF | DI_QUIETINSTALL);
    if (DelayInstall) {
        DeviceInstallParams.Flags |= DI_DONOTCALLCONFIGMG;
    }
    DeviceInstallParams.FlagsEx |= DI_FLAGSEX_ALLOWEXCLUDEDDRVS;
    if (!SetupDiSetDeviceInstallParams(DeviceInfoSet,
                                       DeviceInfoData,
                                       &DeviceInstallParams)) {
        Err = GetLastError();
        goto exit;
    }

    //
    // Build up a list of drivers from the specified INFs
    //
    if (!SetupDiBuildDriverInfoList(DeviceInfoSet, DeviceInfoData, SPDIT_COMPATDRIVER)) {
        Err = GetLastError();
        goto exit;
    }

    //
    // Tell setupapi and the class installers to select the best driver from the 
    // list built from the specified INF.
    //
    if (!SetupDiCallClassInstaller(DIF_SELECTBESTCOMPATDRV,
                                   DeviceInfoSet,
                                   DeviceInfoData)) {
        Err = GetLastError();
        goto exit;
    }

    //
    // Install the selected driver on the selected device without calling kernel mode
    //
    if (!InstallSelectedDriver(hWnd,
                               DeviceInfoSet,
                               NULL,
                               FALSE,
                               &Reboot)) {
        Err = GetLastError();
        goto exit;
    }

exit:
    return Err;
}