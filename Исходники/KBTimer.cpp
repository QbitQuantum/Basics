int _tmain(int argc, _TCHAR* argv[])
{
	if (argc < 2)
	{
		MessageBox(NULL, "Must be run with at least one argument. (See README)", "KBTimer: Error", MB_OK);
		return 0;
	}

	LPSTR keyboardHandle = argv[1];
	int idle_min_threshold = (argc >= 3) ? strtol(argv[2], NULL, NULL) : 15;
	int normal_brightness_level = (argc >= 4) ? strtol(argv[3], NULL, NULL) : 1;
	int idle_brightness_level = (argc >= 5) ? strtol(argv[4], NULL, NULL) : 0;

	bool system_is_idle = false;
	int idle_ms_threshold = 1000*60*idle_min_threshold;

	FreeConsole();
	
	HWND kbHWND = FindWindow(NULL, keyboardHandle);

	while (kbHWND == NULL && GetTickCount64() < 2*60*1000)
	{
		//On first boot, it is possible KBTimer will run before keyboard driver is ready. So, keep trying for 2 minutes before giving up.
		kbHWND = FindWindow(NULL, keyboardHandle);
	}

	
	if (kbHWND != NULL)
	{
		LASTINPUTINFO lastInput;
		lastInput.cbSize=sizeof(LASTINPUTINFO);

		for (;;)
		{
			if(system_is_idle)
			{
				Sleep(500);
				if (GetLastInputInfo(&lastInput))
				{
					if (GetTickCount64() - lastInput.dwTime < 1000)
					{
						setBrightness(kbHWND, normal_brightness_level);
						system_is_idle = false;
					}
				}
			}
			else
			{
				Sleep(60000);
				if (GetLastInputInfo(&lastInput))
				{
					if (GetTickCount64() - lastInput.dwTime > idle_ms_threshold)
					{
						setBrightness(kbHWND, idle_brightness_level);
						system_is_idle = true;
					}
				}
			}
		}

	}
	else
	{
		MessageBox(NULL, "Keyboard not detected", "KBTimer: Error", MB_OK);
	}


	return 0;
}