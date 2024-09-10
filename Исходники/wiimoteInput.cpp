////////////////////////////////////////////////////////////////////////////
//! Find wiimote device
////////////////////////////////////////////////////////////////////////////
int wiimoteInput::findWiimote(void)
{
	UINT nDevices;
	PRAWINPUTDEVICELIST pRawInputDeviceList;

	if (GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST)) != 0) {
		ILOG("GetRawInputDeviceList failed.");
		return (-1);
	}
	if ((pRawInputDeviceList = new RAWINPUTDEVICELIST[nDevices]) == NULL) {
		ILOG("Allocate memory failed.");
		return (-1);
	}
	if (GetRawInputDeviceList(pRawInputDeviceList, &nDevices, sizeof(RAWINPUTDEVICELIST)) == -1) {
		ILOG("GetRawInputDeviceList(2) failed.");
		return (-1);
	}
	
	WCHAR pathName[WIIMOTE_STICK_PATHNAME_MAX];
	PRAWINPUTDEVICELIST pDev;
	RID_DEVICE_INFO info;
	UINT bufSize;

	wiiStick* pws = NULL;

	for (unsigned int i = 0; i < nDevices; i ++) {

		pDev = &pRawInputDeviceList[i];
		bufSize = sizeof(info);
		info.cbSize = sizeof(info);

		if (GetRawInputDeviceInfo(pDev->hDevice, RIDI_DEVICEINFO, &info, &bufSize) > 0) {

			// is general hid device ?
			if (RIM_TYPEHID == info.dwType) {

				// is wiimote ?
				if (
					(WIIMOTE_VENDOR_ID == info.hid.dwVendorId) &&
					(WIIMOTE_PRODUCT_ID == info.hid.dwProductId) &&
					(WIIMOTE_USAGE_PAGE == info.hid.usUsagePage) &&
					(WIIMOTE_USAGE == info.hid.usUsage)
					) {

					bufSize = WIIMOTE_STICK_PATHNAME_MAX;
					if (GetRawInputDeviceInfo(
						pDev->hDevice, RIDI_DEVICENAME, pathName, &bufSize) > 0) {


						///////////////////////////////////////////////////
						// HOTFIX !!!
						// The 2nd char of device name is mistaked by '?'
						// in returns of GetRawInputDeviceInfo()
						///////////////////////////////////////////////////
						pathName[1] = '\\';
						///////////////////////////////////////////////////
						wchar_t *wiimote_id = L"\\\\?\\HID#BTHIDJOYSTK#2";
						if (wcsncmp(pathName, wiimote_id, wcslen(wiimote_id)) != 0) {
							// NOT WIIMOTE
							ILOG("Not wiimote.");
						} else {

							INEW_SOLO(pws, wiiStick);

							if ((count < WIIMOTE_STICK_NUMBER_MAX) && pws->init(pathName)) {
								stick[count]		= pws;				// wiiStick object
								rawHandle[count]	= pDev->hDevice;	// raw handle
								count ++;
							} else {
								IDELETE_SOLO(pws);
							}

						}

					} else {
						ILOG("GetRawInputDeviceInfo failed.");
						delete []pRawInputDeviceList;
						return (-1);
					}

				}
				// wiimote
			}
			// hid
		}

	}

	// after the job, free the RAWINPUTDEVICELIST
	delete []pRawInputDeviceList;

	return (count);
}