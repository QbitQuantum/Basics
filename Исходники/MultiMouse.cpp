		ArrayBlock<RawMouse> getRawMouseArray()
		{
			UINT nDevices;
			PRAWINPUTDEVICELIST pRawInputDeviceList;
			list<RawMouse> rawMiceList;

			if (GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST)) != 0)
			{
				showErrorMessageAndExit(L"GetRawInputDeviceList() count");
			}

			pRawInputDeviceList = safeMallocExitOnFailure<RAWINPUTDEVICELIST>(nDevices);

			if (((INT) GetRawInputDeviceList(pRawInputDeviceList, &nDevices, sizeof(RAWINPUTDEVICELIST))) < 0)
			{
				showErrorMessageAndExit(L"GetRawInputDeviceList() get");
			}

			for (UINT currentDeviceIndex = 0; currentDeviceIndex < nDevices; currentDeviceIndex++)
			{
				DWORD currentDeviceType = pRawInputDeviceList[currentDeviceIndex].dwType;
				HANDLE hDevice = pRawInputDeviceList[currentDeviceIndex].hDevice;

				if (currentDeviceType == RIM_TYPEMOUSE)
				{
					UINT cbSize;
					TCHAR* psName;

					if (GetRawInputDeviceInfo(hDevice, RIDI_DEVICENAME, NULL, &cbSize) != 0)
					{
						showErrorMessageAndExit(L"GetRawInputDeviceInfo() count");
					}

					psName = safeMallocExitOnFailure<TCHAR>(cbSize);

					if (((INT) GetRawInputDeviceInfo(hDevice, RIDI_DEVICENAME, psName, &cbSize)) < 0)
					{
						safe_free(&psName);
						showErrorMessageAndExit(L"GetRawInputDeviceInfo() get");
					}

					assert(_tcsnlen(psName, cbSize) == cbSize - 1);

					// We want to ignore RDP mice
					{
						TCHAR rdpMouseName[] = _T("\\\\?\\Root#RDP_MOU#0000#");
						size_t rdpMouseNameStrlen = _tcslen(rdpMouseName);

						if (_tcslen(psName) >= rdpMouseNameStrlen && 
							_tcsncmp(rdpMouseName, psName, rdpMouseNameStrlen) == 0)
						{
							safe_free(&psName);
							continue;
						}
					}

					safe_free(&psName);

					if (GetRawInputDeviceInfo(hDevice, RIDI_DEVICEINFO, NULL, &cbSize) != 0)
					{
						showErrorMessageAndExit(L"GetRawInputDeviceInfo() count");
					}

					PRID_DEVICE_INFO pDeviceInfo = safeMallocBytesExitOnFailure<RID_DEVICE_INFO>(cbSize);

					pDeviceInfo->cbSize = cbSize;

					if (((INT) GetRawInputDeviceInfo(hDevice, RIDI_DEVICEINFO, pDeviceInfo, &cbSize)) < 0)
					{
						showErrorMessageAndExit(L"GetRawInputDeviceInfo() get");
					}

					assert(pDeviceInfo->dwType == RIM_TYPEMOUSE);

					RawMouse currentMouse;
					currentMouse.deviceHandle = pRawInputDeviceList[currentDeviceIndex].hDevice;
					currentMouse.x = 0;
					currentMouse.y = 0;
					currentMouse.z = 0;
					currentMouse.buttonsPressed = ArrayBlock<bool>();
					currentMouse.buttonsPressed.allocate(pDeviceInfo->mouse.dwNumberOfButtons);

					memset(currentMouse.buttonsPressed.data(), 0, 
						sizeof(bool)*currentMouse.buttonsPressed.count());

					rawMiceList.push_back(currentMouse);
				}
			}

			safe_free(&pRawInputDeviceList);

			ArrayBlock<RawMouse> out_rawMiceArray;
			out_rawMiceArray.allocate(rawMiceList.size());

			size_t currentPos = 0;

			for (list<RawMouse>::iterator rawMouseIt = rawMiceList.begin(); 
				rawMouseIt != rawMiceList.end(); rawMouseIt++)
			{
				out_rawMiceArray.data()[currentPos] = *rawMouseIt;
				currentPos++;
			}

			return out_rawMiceArray;
		}