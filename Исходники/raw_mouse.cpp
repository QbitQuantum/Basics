BOOL init_raw_mouse(BOOL in_include_sys_mouse, BOOL in_include_rdp_mouse, BOOL in_include_individual_mice, HWND hwnd)
{
	// "0" to exclude, "1" to include

	int nInputDevices, i, j;
	PRAWINPUTDEVICELIST pRawInputDeviceList;

	int currentmouse = 0;
	int nSize;
	char *psName;

	char buffer[80];



	excluded_sysmouse_devices_count = 0;
	nraw_mouse_count = 0;


	include_sys_mouse = in_include_sys_mouse;
	include_rdp_mouse = in_include_rdp_mouse;
	include_individual_mice = in_include_individual_mice;

	// 1st call to GetRawInputDeviceList: Pass NULL to get the number of devices.
	if (GetRawInputDeviceList(NULL,  (PUINT) &nInputDevices, sizeof(RAWINPUTDEVICELIST)) != 0) {
		fprintf(stderr, "ERROR: Unable to count raw input devices.\n");
		return 0;
	}

	// Allocate the array to hold the DeviceList
	if ((pRawInputDeviceList = (PRAWINPUTDEVICELIST)  malloc(sizeof(RAWINPUTDEVICELIST) * nInputDevices)) == NULL) {
		fprintf(stderr, "ERROR: Unable to allocate memory for raw input device list.\n");
		return 0;
	}

	// 2nd call to GetRawInputDeviceList: Pass the pointer to our DeviceList and GetRawInputDeviceList() will fill the array
	if ( GetRawInputDeviceList(pRawInputDeviceList, (PUINT)&nInputDevices, sizeof(RAWINPUTDEVICELIST)) == -1)  {
		fprintf(stderr, "ERROR: Unable to get raw input device list.\n");
		return 0;
	}

	// Loop through all devices and count the mice
	for (i = 0; i < nInputDevices; i++) {
		if (pRawInputDeviceList[i].dwType == RIM_TYPEMOUSE ||pRawInputDeviceList[i].dwType == RIM_TYPEHID)  {
			/* Get the device name and use it to determine if it's the RDP Terminal Services virtual device. */

			// 1st call to GetRawInputDeviceInfo: Pass NULL to get the size of the device name 
			if (GetRawInputDeviceInfo (pRawInputDeviceList[i].hDevice, RIDI_DEVICENAME, NULL, (PUINT) &nSize) != 0) {
				fprintf(stderr, "ERROR: Unable to get size of raw input device name.\n");
				return 0;
			}

			// Allocate the array to hold the name
			if ((psName = (char *)malloc(sizeof(TCHAR) * nSize)) == NULL)  {
				fprintf(stderr, "ERROR: Unable to allocate memory for device name.\n");
				return 0;
			}

			// 2nd call to GetRawInputDeviceInfo: Pass our pointer to get the device name
			if ((int)GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICENAME, psName,(PUINT) &nSize) < 0)  {
				fprintf(stderr, "ERROR: Unable to get raw input device name.\n");
				return 0;
			} 

			// Count this mouse for allocation if it's not an RDP mouse or if we want to include the rdp mouse
			if (is_rm_rdp_mouse(psName)) {
				if (include_rdp_mouse) nraw_mouse_count++;
			}
			else { // It's an ordinary mouse
				nraw_mouse_count++;
				if (!include_individual_mice) excluded_sysmouse_devices_count++;     // Don't count this in the final nraw_mouse_count value
			}
		}
	}

	if (include_sys_mouse)
		nraw_mouse_count++;

	// Allocate the array for the raw mice
	if ((raw_mice = (PRAW_MOUSE)malloc(sizeof(RAW_MOUSE) * nraw_mouse_count)) == NULL)  {
		fprintf(stderr, "ERROR: Unable to allocate memory for raw input mice.\n");
		return 0;
	}

	// Define the sys mouse
	if (include_sys_mouse) {
		raw_mice[RAW_SYS_MOUSE].device_handle = 0;
		raw_mice[RAW_SYS_MOUSE].x = 0;
		raw_mice[RAW_SYS_MOUSE].y = 0;
		raw_mice[RAW_SYS_MOUSE].z = 0;
		raw_mice[RAW_SYS_MOUSE].is_absolute = 1;
		raw_mice[RAW_SYS_MOUSE].is_virtual_desktop = 0;
		//raw_mice[RAW_SYS_MOUSE].ID
		currentmouse++;
	}

	// Loop through all devices and set the device handles and initialize the mouse values
	for (i = 0; i < nInputDevices; i++) {
		if (pRawInputDeviceList[i].dwType == RIM_TYPEMOUSE ||pRawInputDeviceList[i].dwType == RIM_TYPEHID) {
			// 1st call to GetRawInputDeviceInfo: Pass NULL to get the size of the device name 
			if (GetRawInputDeviceInfo (pRawInputDeviceList[i].hDevice, RIDI_DEVICENAME, NULL,(PUINT) &raw_mice[currentmouse].nSize) != 0)  {
				fprintf(stderr, "ERROR: Unable to get size of raw input device name (2).\n");
				return 0;
			}

			// Allocate the array to hold the name
			if ((raw_mice[currentmouse].psname = (char *)malloc(sizeof(TCHAR) * raw_mice[currentmouse].nSize)) == NULL) {
				fprintf(stderr, "ERROR: Unable to allocate memory for raw input device name (2).\n");
				return 0;
			}

			// 2nd call to GetRawInputDeviceInfo: Pass our pointer to get the device name
			if ((int) GetRawInputDeviceInfo (pRawInputDeviceList[i].hDevice, RIDI_DEVICENAME, raw_mice[currentmouse].psname,(PUINT) &raw_mice[currentmouse].nSize) < 0) {
				fprintf(stderr, "ERROR: Unable to get raw input device name (2).\n");
				return 0;
			} 

			// Add this mouse to the array if it's not an RDPMouse or if we wish to include the RDP mouse
			if ((!is_rm_rdp_mouse(psName)) || include_rdp_mouse ) {
				raw_mice[currentmouse].device_handle = pRawInputDeviceList[i].hDevice;
				raw_mice[currentmouse].x = 0;
				raw_mice[currentmouse].y = 0;
				raw_mice[currentmouse].z = 0;
				raw_mice[currentmouse].is_absolute = 1;
				raw_mice[currentmouse].is_virtual_desktop = 0;
				

				currentmouse++;
			}
		}
	}

	// free the RAWINPUTDEVICELIST
	free(pRawInputDeviceList);

	for (i = 0; i < nraw_mouse_count; i++) {
		for (j = 0; j < MAX_RAW_MOUSE_BUTTONS; j++) {
			raw_mice[i].buttonpressed[j] = 0;

			// Create the name for this button
			sprintf(buffer, "Button %i", j);
			raw_mice[i].button_name[j] = (char *)malloc(strlen(buffer) + 1);
			sprintf(raw_mice[i].button_name[j], "%s", buffer);
		}
	}

	nraw_mouse_count -= excluded_sysmouse_devices_count;
	// finally, register to recieve raw input WM_INPUT messages
	if (!register_raw_mouse(hwnd)) {
		fprintf(stderr, "ERROR: Unable to register raw input (2).\n");
		return 0;
	}


	return 1;  
}