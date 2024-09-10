LRESULT CALLBACK DeviceStatus::WindowsMessageCallback(  HWND hwnd, 
                                                        UINT message, 
                                                        WPARAM wParam, 
                                                        LPARAM lParam)
{

	switch (message)
	{
	case WM_CREATE:
		{
			// Setup window user data with device status object pointer.
			LPCREATESTRUCT create_struct = reinterpret_cast<LPCREATESTRUCT>(lParam);
			void *lpCreateParam = create_struct->lpCreateParams;
			DeviceStatus *pDeviceStatus = reinterpret_cast<DeviceStatus*>(lpCreateParam);

			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pDeviceStatus));
		}
		return 0;	// Return 0 for successfully handled WM_CREATE.

	case WM_DEVICECHANGE:
		{
			WORD loword = LOWORD(wParam);

			if (loword != DBT_DEVICEARRIVAL &&
				loword != DBT_DEVICEREMOVECOMPLETE) 
			{
				// Ignore messages other than device arrive and remove complete 
                // (we're not handling intermediate ones).
				return TRUE;	// Grant WM_DEVICECHANGE request.
			}

			DEV_BROADCAST_DEVICEINTERFACE* hdr;
			hdr = (DEV_BROADCAST_DEVICEINTERFACE*) lParam;

			if (hdr->dbcc_devicetype != DBT_DEVTYP_DEVICEINTERFACE) 
			{
				// Ignore non interface device messages.
				return TRUE;	// Grant WM_DEVICECHANGE request.
			}

			LONG_PTR userData = GetWindowLongPtr(hwnd, GWLP_USERDATA);
			OVR_ASSERT(userData != NULL);

			// Call callback on device messages object with the device path.
			DeviceStatus* pDeviceStatus = (DeviceStatus*) userData;
			String devicePathStr(hdr->dbcc_name);
			pDeviceStatus->MessageCallback(loword, devicePathStr);
		}
		return TRUE;	// Grant WM_DEVICECHANGE request.

	case WM_CLOSE:
		{
			LONG_PTR userData = GetWindowLongPtr(hwnd, GWLP_USERDATA);
			OVR_ASSERT(userData != NULL);
			DeviceStatus* pDeviceStatus = (DeviceStatus*) userData;
			pDeviceStatus->hMessageWindow = NULL;

			DestroyWindow(hwnd);
		}
		return 0;	// We processed the WM_CLOSE message.

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;	// We processed the WM_DESTROY message.
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}