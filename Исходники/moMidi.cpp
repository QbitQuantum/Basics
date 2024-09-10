MOboolean
moMidiDevice::Init( moText devicetext ) {

	SetName(devicetext);


#ifdef WIN32
/*
	BOOL		result;
	GUID		hidGUID;
	HDEVINFO	hardwareDeviceInfoSet;
	SP_DEVICE_INTERFACE_DATA	deviceInterfaceData;
	DWORD Index = 0;
	DWORD requiredSize;

	//Get the HID GUID value - used as mask to get list of devices
	HidD_GetHidGuid ( &hidGUID );

	//Get a list of devices matching the criteria (hid interface, present)
	hardwareDeviceInfoSet = SetupDiGetClassDevs (&hidGUID,
					NULL, // Define no enumerator (global)
					NULL, // Define no
					(DIGCF_PRESENT | DIGCF_ALLCLASSES |DIGCF_DEVICEINTERFACE));


	deviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

	//Go through the list and get the interface data
	for(int i = 0; i < 10; i++)
	{
		result = SetupDiEnumDeviceInterfaces (hardwareDeviceInfoSet,
					NULL, //infoData,
					&hidGUID, //interfaceClassGuid,
					Index,
					&deviceInterfaceData);
		if (result == FALSE) {
			Index++;
		}
	}

	// Failed to get a device - possibly the index is larger than the number of devices
	if (result == FALSE) {
		SetupDiDestroyDeviceInfoList (hardwareDeviceInfoSet);
		return;// INVALID_HANDLE_VALUE;
	}

	//Get the details with null values to get the required size of the buffer
	SetupDiGetDeviceInterfaceDetail (hardwareDeviceInfoSet,
				&deviceInterfaceData,
				NULL, //interfaceDetail,
				0, //interfaceDetailSize,
				&requiredSize,
				0); //infoData))
*/

	MIDIINCAPS     moc;
	unsigned long   iNumDevs, i;



	/* Get the number of MIDI Out devices in this computer */
	iNumDevs = midiInGetNumDevs();

	if (iNumDevs==0) {
	    MODebug2->Message( moText("ERROR! NO MIDI DEVICES FOUND"));
    }

	/* Go through all of those devices, displaying their names */
	for (i = 0; i < iNumDevs; i++)
	{
		/* Get info about the next device */
		if (!midiInGetDevCaps(i, &moc, sizeof(MIDIINCAPS)))
		{
			/* Display its Device ID and name */
			MODebug2->Message( moText("Device ID #") + IntToStr(i) + moText(":") + moText(moc.szPname));
			if ( !stricmp(moc.szPname, devicetext) ) {
				m_DeviceId = i;
				break;
			}
		}
	}


	/*
	unsigned long result;
	HMIDIOUT      outHandle;

	// Open the MIDI Mapper
	result = midiOutOpen(&outHandle, i, 0, 0, CALLBACK_WINDOW);
	if (!result)
	{
		// Output the C note (ie, sound the note)
		midiOutShortMsg(outHandle, 0x00403C90);

		// Output the E note
		midiOutShortMsg(outHandle, 0x00404090);

		// Output the G note
		midiOutShortMsg(outHandle, 0x00404390);

		// Here you should insert a delay so that you can hear the notes sounding
		Sleep(1000);

		// Now let's turn off those 3 notes
		midiOutShortMsg(outHandle, 0x00003C90);
		midiOutShortMsg(outHandle, 0x00004090);
		midiOutShortMsg(outHandle, 0x00004390);

		 // Close the MIDI device
		 midiOutClose(outHandle);
	} else {
		printf("There was an error opening MIDI Mapper!\r\n");
	}
	*/
	HMIDIIN			handle;
	MIDIHDR			midiHdr;
	unsigned long	err;

	if (m_DeviceId!=-1) {
		/* Open default MIDI In device */
		if (!(err = midiInOpen(&handle, m_DeviceId, (DWORD)midiCallback, (DWORD)this, CALLBACK_FUNCTION)))
		{
			// Store pointer to our input buffer for System Exclusive messages in MIDIHDR
			midiHdr.lpData = (LPSTR)&SysXBuffer[0];

			// Store its size in the MIDIHDR
			midiHdr.dwBufferLength = sizeof(SysXBuffer);

			// Flags must be set to 0
			midiHdr.dwFlags = 0;

			// Prepare the buffer and MIDIHDR
			err = midiInPrepareHeader(handle, &midiHdr, sizeof(MIDIHDR));
			if (!err)
			{
				// Queue MIDI input buffer
				err = midiInAddBuffer(handle, &midiHdr, sizeof(MIDIHDR));
				if (!err)
				{
					// Start recording Midi
					err = midiInStart(handle);
					m_bInit = true;
					return true;
					/*
					if (!err)
					{
						// Wait for user to abort recording
						printf("Press any key to stop recording...\r\n\n");
						_getch();

						// We need to set a flag to tell our callback midiCallback()
						// not to do any more midiInAddBuffer(), because when we
						// call midiInReset() below, Windows will send a final
						// MIM_LONGDATA message to that callback. If we were to
						// allow midiCallback() to midiInAddBuffer() again, we'd
						// never get the driver to finish with our midiHdr

						SysXFlag |= 0x80;
						printf("\r\nRecording stopped!\n");
					}*/

					/* Stop recording */
					//midiInReset(handle);
				}
			}
	/*
			// If there was an error above, then print a message
			if (err) PrintMidiInErrorMsg(err);

			// Close the MIDI In device
			while ((err = midiInClose(handle)) == MIDIERR_STILLPLAYING) Sleep(0);
			if (err) PrintMidiInErrorMsg(err);

			// Unprepare the buffer and MIDIHDR. Unpreparing a buffer that has not been prepared is ok
			midiInUnprepareHeader(handle, &midiHdr, sizeof(MIDIHDR));
			*/
		}
		else
		{
			printf("Error opening the default MIDI In Device!\r\n");
			PrintMidiInErrorMsg(err);
			return false;
		}
	}

#else

#endif
		return false;
}