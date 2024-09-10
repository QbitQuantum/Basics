	bool D3D9Device::validateDisplayMonitor(D3D9RenderWindowCore* renderWindow)
	{
		// Ignore full screen since it doesn't really move and it is possible 
		// that it created using multi-head adapter so for a subordinate the
		// native monitor handle and this device handle will be different.
		if (renderWindow->getProperties().isFullScreen())
			return true;

		HMONITOR	hRenderWindowMonitor = NULL;

		// Find the monitor this render window belongs to.
		hRenderWindowMonitor = MonitorFromWindow(renderWindow->_getWindowHandle(), MONITOR_DEFAULTTONULL);

		// This window doesn't intersect with any of the display monitor
		if (hRenderWindowMonitor == NULL)		
			return false;		
		

		// Case this window changed monitor.
		if (hRenderWindowMonitor != mMonitor)
		{	
			// Lock access to rendering device.
			D3D9RenderAPI::getResourceManager()->lockDeviceAccess();

			mpDeviceManager->linkRenderWindow(renderWindow);

			// UnLock access to rendering device.
			D3D9RenderAPI::getResourceManager()->unlockDeviceAccess();

			return false;
		}

		return true;
	}