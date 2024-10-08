UINT iTunesApi::Init()
{
    int result = FALSE;

	char newlibvar[2048];
	char *libvar;

	memset(newlibvar, 0, sizeof(newlibvar));
	libvar = getenv("path");
    sprintf(newlibvar, "path=%s", libvar);
	strcat_s(newlibvar, ";C:\\Program Files\\Common Files\\Apple\\Mobile Device Support;");
	strcat_s(newlibvar, "C:\\Program Files\\Common Files\\Apple\\Apple Application Support;");
	_putenv(newlibvar);

    _iTunes_mobile_device_dll = ::LoadLibrary(L"iTunesMobileDevice.dll");
    _core_function_dll = ::LoadLibrary(L"CoreFoundation.dll");

    //am
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AMRestoreRegisterForDeviceNotifications, func_AMRestoreRegisterForDeviceNotifications, "AMRestoreRegisterForDeviceNotifications");
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AMDServiceConnectionSend, func_AMDServiceConnectionSend, "AMDServiceConnectionSend");
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AMDServiceConnectionReceive, func_AMDServiceConnectionReceive, "AMDServiceConnectionReceive");
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AMDeviceGetInterfaceType, func_AMDeviceGetInterfaceType, "AMDeviceGetInterfaceType");
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AMDServiceConnectionInvalidate, func_AMDServiceConnectionInvalidate, "AMDServiceConnectionInvalidate");
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AMDeviceRetain, func_AMDeviceRetain, "AMDeviceRetain");
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AMDeviceNotificationSubscribe, func_AMDeviceNotificationSubscribe, "AMDeviceNotificationSubscribe");
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AMDeviceConnect, func_AMDeviceConnect, "AMDeviceConnect");
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AMDeviceCopyDeviceIdentifier, func_AMDeviceCopyDeviceIdentifier, "AMDeviceCopyDeviceIdentifier");
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AMDeviceDisconnect, func_AMDeviceDisconnect, "AMDeviceDisconnect");
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AMDeviceIsPaired, func_AMDeviceIsPaired, "AMDeviceIsPaired");
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AMDeviceValidatePairing, func_AMDeviceValidatePairing, "AMDeviceValidatePairing");
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AMDeviceStartSession, func_AMDeviceStartSession, "AMDeviceStartSession");
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AMDeviceStopSession, func_AMDeviceStopSession, "AMDeviceStopSession");
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AMDeviceSetValue, func_AMDeviceSetValue, "AMDeviceSetValue");
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AMDeviceCopyValue, func_AMDeviceCopyValue, "AMDeviceCopyValue");
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AMDeviceGetInterfaceType, func_AMDeviceGetInterfaceType, "AMDeviceGetInterfaceType");

    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AMDeviceSecureStartService, func_AMDeviceSecureStartService, "AMDeviceSecureStartService");
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AMDServiceConnectionGetSocket, func_AMDServiceConnectionGetSocket, "AMDServiceConnectionGetSocket");
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AMDServiceConnectionGetSecureIOContext, func_AMDServiceConnectionGetSecureIOContext, "AMDServiceConnectionGetSecureIOContext");

    //afc
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AFCConnectionOpen, func_AFCConnectionOpen, "AFCConnectionOpen");
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AFCFileInfoOpen, func_AFCFileInfoOpen, "AFCFileInfoOpen");
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AFCKeyValueRead, func_AFCKeyValueRead, "AFCKeyValueRead");

    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AFCDirectoryOpen, func_AFCDirectoryOpen, "AFCDirectoryOpen");
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AFCFileRefOpen, func_AFCFileRefOpen, "AFCFileRefOpen");
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AFCFileRefRead, func_AFCFileRefRead, "AFCFileRefRead");
    LOAD_LIBRARY_API(_iTunes_mobile_device_dll, AFCFileRefClose, func_AFCFileRefClose, "AFCFileRefClose");

	//cfstring
    LOAD_LIBRARY_API(_core_function_dll, CFStringMakeConstantString, func_CFStringMakeConstantString, "__CFStringMakeConstantString");

	//cf
    LOAD_LIBRARY_API(_core_function_dll, CFStringGetCString, func_CFStringGetCString, "CFStringGetCString");
    LOAD_LIBRARY_API(_core_function_dll, CFGetTypeID, func_CFGetTypeID, "CFGetTypeID");
    LOAD_LIBRARY_API(_core_function_dll, CFStringGetTypeID, func_CFStringGetTypeID, "CFStringGetTypeID");
    LOAD_LIBRARY_API(_core_function_dll, CFStringGetLength, func_CFStringGetLength, "CFStringGetLength");

    result = TRUE;
Exit0:
    if(!result)
	{
		LPVOID lpMsgBuf;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0,
			NULL
			);
        MessageBox(NULL,(LPCTSTR)lpMsgBuf, L"Load iTunesMobileDevice.dll Failed!!!",MB_OK | MB_ICONINFORMATION);
		LocalFree(lpMsgBuf);
	}
    return result;
}