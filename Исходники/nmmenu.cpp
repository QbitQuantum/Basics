HMENU 
CNdasDeviceMenu::CreateDeviceSubMenu(
	__in ndas::DevicePtr pDevice,
	__out NDSI_DATA* psiData)
{
	CMenuHandle menu;
	CString strText;

	CMenuItemInfo sep;
	sep.fMask = MIIM_TYPE;
	sep.fType = MFT_SEPARATOR;

	CMenuItemInfo mii;
	mii.fMask = MIIM_ID | MIIM_STRING | MIIM_DATA;
	mii.dwItemData = (WORD)pDevice->GetSlotNo();

	ATLVERIFY(menu.CreateMenu());

	NDAS_DEVICE_STATUS status = pDevice->GetStatus();
	// Enable or Disable

	BOOL fShowUnregister = FALSE;

	if (NDAS_DEVICE_STATUS_DISABLED == status) 
	{
		psiData->Status = NDSI_DISABLED;

		pSetDeviceStatusMenuItem(menu,IDS_DEVMST_DEACTIVATED);

		ATLVERIFY(strText.LoadString(IDS_ACTIVATE_DEVICE));

		mii.wID = IDR_ENABLE_DEVICE;
		mii.dwTypeData = (LPTSTR)(LPCTSTR)strText;

		ATLVERIFY(menu.InsertMenuItem(0xFFFF, TRUE, &mii));

		fShowUnregister = TRUE;

	} 
	else if (NDAS_DEVICE_STATUS_DISCONNECTED == status) 
	{
		//
		// although there is no ERROR status in NDAS device,
		// if the last error is set, we will show the indicator
		// as error
		//
		psiData->Status = 
			(ERROR_SUCCESS == pDevice->GetLastError()) ? 
			NDSI_DISCONNECTED : 
			NDSI_ERROR;

		ATLVERIFY(pSetDeviceStatusMenuItem(menu, IDS_DEVMST_DISCONNECTED));
		fShowUnregister = TRUE;
	}
	else if (NDAS_DEVICE_STATUS_UNKNOWN == status) 
	{
		psiData->Status = NDSI_UNKNOWN;
		ATLVERIFY(pSetDeviceStatusMenuItem(menu, IDS_DEVMST_UNKNOWN));
		fShowUnregister = TRUE;
	} 
	else if (NDAS_DEVICE_STATUS_CONNECTING == status)
	{
		psiData->Status = NDSI_CONNECTING;
		ATLVERIFY(pSetDeviceStatusMenuItem(menu, IDS_DEVMST_CONNECTING));
		fShowUnregister = TRUE;
	}
	else if (NDAS_DEVICE_STATUS_CONNECTED == status) 
	{
		psiData->Status = NDSI_CONNECTED;

		BOOL fMounted = FALSE;

		ndas::UnitDeviceVector unitDevices = pDevice->GetUnitDevices();
		int i = 0;
		for (ndas::UnitDeviceConstIterator itr = unitDevices.begin();
			itr != unitDevices.end(); ++itr, ++i)
		{
			ndas::UnitDevicePtr pUnitDevice = *itr;

			pUnitDevice->UpdateStatus();

			BYTE bReserved;
			psiData->nParts = min(i + 1, 2);
			AppendUnitDeviceMenuItem(
				pUnitDevice, 
				menu.m_hMenu, 
				(i < 2) ? &psiData->StatusPart[i] : &bReserved);

			// If there is a mounted unit device, DISABLE menu will be disabled.
			if (NDAS_UNITDEVICE_STATUS_MOUNTED == pUnitDevice->GetStatus()) 
			{
				fMounted = TRUE;
			}
		}

		if (!fMounted) 
		{
			fShowUnregister = TRUE;
		}
	}

	//
	// Unregister Device Menu
	//
	if (fShowUnregister) 
	{
		ATLVERIFY(strText.LoadString(IDS_UNREGISTER_DEVICE));
		mii.wID = IDR_UNREGISTER_DEVICE;
		mii.dwTypeData = (LPTSTR)(LPCTSTR)strText;
		ATLVERIFY(menu.InsertMenuItem(0xFFFF, TRUE, &mii));
		ATLVERIFY(menu.InsertMenuItem(0xFFFF, TRUE, &sep));
	}

	ATLVERIFY(strText.LoadString(IDS_SHOW_DEVICE_PROPERTIES));
	mii.wID = IDR_SHOW_DEVICE_PROPERTIES;
	mii.dwTypeData = (LPTSTR)(LPCTSTR)strText;
	ATLVERIFY(menu.InsertMenuItem(0xFFFF, TRUE, &mii));

	return menu.m_hMenu;
}