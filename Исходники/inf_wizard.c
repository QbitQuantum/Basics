BOOL CALLBACK dialog_proc_1(HWND dialog, UINT message,
							WPARAM wParam, LPARAM lParam)
{
	static HDEVNOTIFY notification_handle_hub = NULL;
	static HDEVNOTIFY notification_handle_dev = NULL;
	DEV_BROADCAST_HDR *hdr = (DEV_BROADCAST_HDR *) lParam;
	DEV_BROADCAST_DEVICEINTERFACE dev_if;
	static device_context_t *device = NULL;
	HWND list = GetDlgItem(dialog, ID_LIST);
	LVITEM item;

	switch (message)
	{
	case WM_INITDIALOG:
		SendMessage(dialog,WM_SETICON,ICON_SMALL, (LPARAM)mIcon);
		SendMessage(dialog,WM_SETICON,ICON_BIG,   (LPARAM)mIcon);

		device = (device_context_t *)lParam;
		if (device->user_allocated_wdi)
		{
			if (device->wdi)
			{
				free(device->wdi);
				device->wdi = NULL;
			}
			device->user_allocated_wdi = FALSE;
		}
		g_hwndTrackingTT = CreateTrackingToolTip(list, TEXT(" "));

#if defined(_WIN64)
		device_list_wndproc_orig = (WNDPROC)SetWindowLongPtr(list, GWLP_WNDPROC, (UINT_PTR)device_list_wndproc);
#else
		device_list_wndproc_orig = (WNDPROC)SetWindowLongPtr(list, GWL_WNDPROC, (UINT_PTR)device_list_wndproc);
#endif

		memset(device, 0, sizeof(*device));

		SetWindowText(GetDlgItem(dialog, ID_LIST_HEADER_TEXT), list_header_text);
		device_list_init(list);
		device_list_refresh(list);

		dev_if.dbcc_size = sizeof(dev_if);
		dev_if.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;

		dev_if.dbcc_classguid = GUID_DEVINTERFACE_USB_HUB;
		notification_handle_hub = RegisterDeviceNotification(dialog, &dev_if, 0);

		dev_if.dbcc_classguid = GUID_DEVINTERFACE_USB_DEVICE;
		notification_handle_dev = RegisterDeviceNotification(dialog, &dev_if, 0);

		return TRUE;

	case WM_DEVICECHANGE:
		switch (wParam)
		{
		case DBT_DEVICEREMOVECOMPLETE:
			if (hdr->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
				device_list_refresh(list);
			break;
		case DBT_DEVICEARRIVAL:
			if (hdr->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
				device_list_refresh(list);
			break;
		default:
			;
		}
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_BUTTON_NEXT:
			if (notification_handle_hub)
				UnregisterDeviceNotification(notification_handle_hub);
			if (notification_handle_dev)
				UnregisterDeviceNotification(notification_handle_dev);

			memset(&item, 0, sizeof(item));
			item.mask = LVIF_TEXT | LVIF_PARAM;
			item.iItem = ListView_GetNextItem(list, -1, LVNI_SELECTED);

			memset(device, 0, sizeof(*device));

			if (item.iItem >= 0)
			{
				if (ListView_GetItem(list, &item))
				{
					if (item.lParam)
					{
						memcpy(device, (void *)item.lParam, sizeof(*device));
					}
				}
			}

			if (!device->wdi)
			{
				device->user_allocated_wdi = TRUE;
				device->wdi = malloc(sizeof(struct wdi_device_info));
				memset(device->wdi,0,sizeof(struct wdi_device_info));

				device->wdi->vid = 0x12AB;
				device->wdi->pid = 0x12AB;
			}

			if (!device->manufacturer[0])
				strcpy(device->manufacturer, "Insert manufacturer name");
			if (!device->description[0])
				strcpy(device->description,  "Insert device description");

			device_list_clean(list);

			EndDialog(dialog, ID_DIALOG_2);
			return TRUE;

		case ID_BUTTON_BACK:
			device_list_clean(list);
			if (notification_handle_hub)
				UnregisterDeviceNotification(notification_handle_hub);
			if (notification_handle_dev)
				UnregisterDeviceNotification(notification_handle_dev);
			EndDialog(dialog, ID_DIALOG_0);
			return TRUE ;

		case ID_BUTTON_CANCEL:
		case IDCANCEL:
			device_list_clean(list);
			if (notification_handle_hub)
				UnregisterDeviceNotification(notification_handle_hub);
			if (notification_handle_dev)
				UnregisterDeviceNotification(notification_handle_dev);
			EndDialog(dialog, 0);
			return TRUE ;
		}
	}

	return FALSE;
}