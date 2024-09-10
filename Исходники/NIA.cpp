BOOL ConnectNIA(HWND hDlg) {
	UINT ui;
	UINT ret;
	ret=GetRawInputDeviceList(NULL,&ui,0);
	UINT i;
	int sav_pause;

	write_logfile("Connecting NIA");

	sav_pause=TTY.read_pause;
    TTY.read_pause=1;

	ret=GetRegisteredRawInputDevices(NULL,&ui,sizeof(RAWINPUTDEVICE));			// get size
	if (ret<=sizeof(Rid))														// if okay, get structures
		GetRegisteredRawInputDevices(Rid, &ui, sizeof(RAWINPUTDEVICE));
	if (ui>0) {
		write_logfile("NIA already connected!");
		TTY.read_pause=sav_pause;
		return (TRUE);
	}

	m_hNIA[0]=NULL;
	m_hNIA[1]=NULL;

	ui=20;
	ret=GetRawInputDeviceList(&RawInputDeviceList[0],&ui,sizeof(RAWINPUTDEVICELIST));			
	if(ret!=(UINT)-1)
	{
		RID_DEVICE_INFO dev_info ;
		TCHAR strName[300];

		m_nCountNIA = 0;

		for(i=0;i<ret;i++)
		{
			if(i>=20) break;

			dev_info.cbSize=sizeof(RID_DEVICE_INFO);
			ui=sizeof(RID_DEVICE_INFO);
			GetRawInputDeviceInfo(RawInputDeviceList[i].hDevice,RIDI_DEVICEINFO,&dev_info,&ui);
			ui=300;
			GetRawInputDeviceInfo(RawInputDeviceList[i].hDevice,RIDI_DEVICENAME,strName,&ui);

			if(dev_info.hid.dwVendorId==0x1234 /*&& dev_info.hid.dwProductId==0*/)
			{
				if(m_nCountNIA>=2) break;		// nur an dieser Stelle vorbereitet!
				m_hNIA[m_nCountNIA]=RawInputDeviceList[i].hDevice;
				Rid[m_nCountNIA].usUsagePage = 0xFF00; 
				Rid[m_nCountNIA].usUsage = 0xFF01; 
				Rid[m_nCountNIA].dwFlags = RIDEV_INPUTSINK;	// this enables the caller to receive the input even when the caller is not in the foreground. Note that hwndTarget must be specified.
				Rid[m_nCountNIA].hwndTarget = ghWndMain ;		//  directs Data to main Thread !!

				m_nCountNIA++;					// ToDo: für 2 NIA Devices 2! Channels in Amplifier??? (not tested yet!)
			}
		}
	} else {
		TTY.read_pause=sav_pause;
		return (FALSE) ;
	}
	if(m_nCountNIA>0)
	{
		if (RegisterRawInputDevices(Rid, m_nCountNIA, sizeof(RAWINPUTDEVICE)) == FALSE) {
				write_logfile("Could not register NIA");
				report_error("Could not register NIA");
				TTY.read_pause=sav_pause;
				return FALSE; 
		} else {
			if (hDlg!=NULL) {
  			  SetDlgItemText( hDlg, IDC_PORTCOMBO, "none") ;
			  TTY.read_pause=sav_pause;
			  return TRUE;
			}
		}
	}

	TTY.read_pause=sav_pause;
	return FALSE;  
}