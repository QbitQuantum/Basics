//////////////////////////// 
// FETCH    USB     DRIVER      VERSION
void windozeHelpers::FetchUsbDriverVersion( const uint16_t DeviceNum, std::string & version )
{
    HDEVINFO deviceInfo = 0;
    SP_DEVICE_INTERFACE_DATA interfaceData;

     std::string msg;

    if( !EnumerateDevice( DeviceNum, deviceInfo, interfaceData, msg ) )
    {
        apgHelper::throwRuntimeException( __FILE__, msg, __LINE__, Apg::ErrorType_Connection );
    }

    
    SP_DEVINFO_DATA deviceData;
    deviceData.cbSize = sizeof(SP_DEVINFO_DATA);
    if( !SetupDiEnumDeviceInfo( deviceInfo, DeviceNum, &deviceData ) )
    {
        //getting the windows error message b4 the next winapi calls
        //nukes it out.  then throw the error
        std::string errMsg = "SetupDiEnumDeviceInfo failed "
            + windozeHelpers::GetLastWinError();

        SetupDiDestroyDeviceInfoList(deviceInfo);

        apgHelper::throwRuntimeException( __FILE__, 
           errMsg , __LINE__,Apg::ErrorType_Connection );
    }
  
    //from BOOL DumpDeviceDriverNodes in dump.cpp in 
    //C:\WinDDK\6001.18002\src\setup\devcon
    SP_DEVINSTALL_PARAMS deviceInstallParams;
    SP_DRVINFO_DATA driverInfoData;

    ZeroMemory(&deviceInstallParams, sizeof(deviceInstallParams));
    ZeroMemory(&driverInfoData, sizeof(driverInfoData));

    driverInfoData.cbSize = sizeof(SP_DRVINFO_DATA);
    deviceInstallParams.cbSize = sizeof(SP_DEVINSTALL_PARAMS);

    if( !SetupDiGetDeviceInstallParams(deviceInfo, &deviceData, 
        &deviceInstallParams) )
    {
       std::string errMsg = "SetupDiGetDeviceInstallParams failed "
            + windozeHelpers::GetLastWinError();

        SetupDiDestroyDeviceInfoList(deviceInfo);

        apgHelper::throwRuntimeException( __FILE__, 
           errMsg , __LINE__,Apg::ErrorType_Connection );
    }

    //
    // Set the flags that tell SetupDiBuildDriverInfoList to allow excluded drivers.
    //
    deviceInstallParams.FlagsEx |= (DI_FLAGSEX_INSTALLEDDRIVER | DI_FLAGSEX_ALLOWEXCLUDEDDRVS);

    if( !SetupDiSetDeviceInstallParams(deviceInfo, &deviceData, 
        &deviceInstallParams) )
    {
         std::string errMsg = "SetupDiGetDeviceInstallParams failed "
            + windozeHelpers::GetLastWinError();

        SetupDiDestroyDeviceInfoList(deviceInfo);

        apgHelper::throwRuntimeException( __FILE__, 
           errMsg , __LINE__,Apg::ErrorType_Connection );
    }

    if( !SetupDiBuildDriverInfoList(deviceInfo, &deviceData, 
        SPDIT_COMPATDRIVER) )
    {
         std::string errMsg = "SetupDiBuildDriverInfoList failed "
            + windozeHelpers::GetLastWinError();

        SetupDiDestroyDeviceInfoList(deviceInfo);

        apgHelper::throwRuntimeException( __FILE__, 
           errMsg , __LINE__,Apg::ErrorType_Connection );
    }

  
    // believe the member index should be set to 0 for all
    // devices...not 100% sure what this parameter is referring
    // to, the number of devices, the number of driver interfaces,
    // number of device interfaces????
    // http://msdn.microsoft.com/en-us/library/windows/hardware/ff551018(v=vs.85).aspx
    if( !SetupDiEnumDriverInfo(deviceInfo, &deviceData, 
        SPDIT_COMPATDRIVER, 0, &driverInfoData) )
    {
        std::string errMsg = "SetupDiEnumDriverInfo failed "
            + windozeHelpers::GetLastWinError();

        SetupDiDestroyDriverInfoList(deviceInfo, &deviceData,
        SPDIT_COMPATDRIVER);
        SetupDiDestroyDeviceInfoList(deviceInfo);

        apgHelper::throwRuntimeException( __FILE__, 
           errMsg , __LINE__,Apg::ErrorType_Connection );
    }
 
    ULARGE_INTEGER Version;
    Version.QuadPart = driverInfoData.DriverVersion;
    
    std::stringstream ss;
    ss << HIWORD(Version.HighPart) << ".";
    ss << LOWORD(Version.HighPart) << ".";
    ss << HIWORD(Version.LowPart) << ".";
    ss << LOWORD(Version.LowPart);
                       
    version = ss.str();

    SetupDiDestroyDriverInfoList(deviceInfo, &deviceData,
        SPDIT_COMPATDRIVER);
    SetupDiDestroyDeviceInfoList(deviceInfo);

}