void UsbSerial::usbClose( )
{
	if( deviceOpen )
	{
    // Linux Only
    #if (defined(Q_WS_LINUX))
    #endif
  	  //Mac-only
		#ifdef Q_WS_MAC
		::close( deviceHandle );
		foundMakeController = false;
		deviceHandle = -1;
		deviceOpen = false;
		#endif
		//Windows-only
	  #ifdef Q_WS_WIN
	  CloseHandle( deviceHandle );
	  deviceHandle = INVALID_HANDLE_VALUE;
	  deviceOpen = false;
	  UnregisterDeviceNotification( deviceNotificationHandle );
		#endif //Windows-only UsbSerial::close( )
		messageInterface->message( 1, "Usb> Make Controller disconnected.\n" );
	}
}