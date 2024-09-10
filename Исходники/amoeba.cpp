LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{	
	switch(msg)
	{
	case WM_DEVICECHANGE:
	{
		PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR) lParam;
		switch(wParam)
		{
		case DBT_DEVICEARRIVAL:
			if (lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
			{
				PDEV_BROADCAST_VOLUME lpdv = (PDEV_BROADCAST_VOLUME) lpdb;
				TCHAR z = FirstDriveFromMask(lpdv->dbcv_unitmask);
				if (DriveType(z) == DT_REMOVABLE)
					PendriveArrive(z);
			}
		}
	}
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}