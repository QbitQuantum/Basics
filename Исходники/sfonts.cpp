//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitSFDLL
//Author		Robert Slater
//Date			Fri 3 Jul 1998
//
//Description
//
//	This function loads the SF Manager DLL, and then queries all the SoundFont devices in
//	the system. Each device is given a rating (see #define statements above for details),
// 	and the device with the best rating is opened. A router command to route all MIDI data
// 	to this device is then sent.
//
// 	Pass TRUE to this function to do the above and
// 	Pass FALSE to close the SF device, and unload the SF Manager library.
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
Bool SndFonts::InitSFDLL(Bool bStartUp)
{
    UWord	count,done;
    ULong	dwMaxMem,dwAvailableMemCurrent;
    UByte	Rating[MAXNUMDEVICES] = {0};
    LRESULT dwErr;
    CSFMIDILocation midiLoc;
    CSFCapsObject sfCaps;
    char	String[60];
    ULong	dwRouterID;
    UByte	sfRouterCommand[12] = {0xf0, 0x00, 0x20, 0x21, 0x5f, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0xf7
                                };
    MIDIHDR sysExMessage;
    Bool	retval = TRUE;

    if (bStartUp == TRUE)
    {
        // Load the SoundFont Master Manager

        hSFMANDLL = LoadLibrary (SF_MASTER_MANAGER_FILENAME);
        if (hSFMANDLL == NULL )
        {
//			MessageBox(NULL, "Error loading SoundFont Manager", "Error", MB_OK) ;
            return FALSE;
        }

        // Get the address of the SoundFont manager function table
        lpSFManager = (PSFMANAGER)GetProcAddress((HINSTANCE__*)hSFMANDLL, SF_FUNCTION_TABLE_NAME);
        if  (lpSFManager == NULL)
        {
            FreeLibrary((HINSTANCE__*)hSFMANDLL);
//			MessageBox(NULL, "Error getting SFMAN function table", "Error", MB_OK) ;
            return FALSE;
        }

        // Use SF_QueryInterface to get access to the appropriate function table
        if ((dwErr = lpSFManager->SF_QueryInterface(ID_SFMANL101API,(ULong*)&lpSFL1API))!=0)
        {
            FreeLibrary((HINSTANCE__*)hSFMANDLL);
//			MessageBox(NULL,"Failed to Query Interface","Error !",MB_OK);
            return FALSE ;
        }

        // Get the number of SoundFont compatible devices in system
        lpSFL1API->SF_GetNumDevs(&numSFDevs);
        if (numSFDevs != 0)
        {
            // For each SF compatible device, query the caps, and assign a
            // rating to it.

            for (count=0; count<numSFDevs; count++)
            {
                // Get current device capabilities
                memset(&sfCaps, 0, sizeof(CSFCapsObject));
                sfCaps.m_SizeOf = sizeof(sfCaps);
                lpSFL1API->SF_GetDevCaps(count,&sfCaps);

                // Does this device have a Hardware synthesiser ?
                if ((sfCaps.m_DevCaps & SFMANCAP_SOFTWARE_SYNTH_CAP) == 0)
                {
                    // Yes, device has a hardware synthesier ...
                    // Does this device use hardware memory?
                    if ((sfCaps.m_DevCaps & SFMANCAP_DYNAMIC_MEM_CAP) == 0)
                    {
                        // Yes, device has hardware memory ...
                        // Open the device so that the amount of memory can be queried
                        lpSFL1API->SF_Open(count);

                        // Query the amount of memory available for this device
                        lpSFL1API->SF_QueryStaticSampleMemorySize(count,&dwMaxMem,
                                &dwAvailableMemCurrent);

                        Rating[count]=(BYTE)(dwAvailableMemCurrent/HWMemBlock);
                        Rating[count]+=HWSynthHWMem;

                        // If hardware RAM size is less than HWMemBlock, then do not use this
                        // device. (This caters for unexpanded SB32 cards which have no memory)
                        if (Rating[count]==HWSynthHWMem)
                            Rating[count]=0;

                        lpSFL1API->SF_Close(count);
                    }
                    else
                        Rating[count]=(BYTE)HWSynthSysMem;	// No, device uses system memory
                }
                else
                    Rating[count]=SWSynthSysMem;	//No, device has a software synthesier ...
            }

            // Choose best device and try to open it, if it fails then find next best device
            // and open that and so on ...
            done = numSFDevs;
            while (done>0)
            {
                BestsfIdx = 0;
                done--;

                // Search through the other devices, for one with a higher rating
                for (count = 1; count<numSFDevs; count++)
                {
                    if (Rating[count] > Rating[BestsfIdx])
                        BestsfIdx = count;
                }

                // Found best device - now try to open it
                if (lpSFL1API->SF_Open(BestsfIdx) != SFERR_NOERR)
                    Rating[BestsfIdx]=0;
                else
                    done=0;
            }

            if (Rating[BestsfIdx] == 0)
            {
                // Failed to open any devices
                FreeLibrary((HINSTANCE__*)hSFMANDLL);
                return FALSE;
            }

            // Query and capabilities of the best device, and set dwAvailableMemBest to the amount
            // of RAM available.
            memset(&sfCaps, 0, sizeof(CSFCapsObject));
            sfCaps.m_SizeOf = sizeof(sfCaps);
            lpSFL1API->SF_GetDevCaps(BestsfIdx,&sfCaps);
            if ((sfCaps.m_DevCaps & SFMANCAP_DYNAMIC_MEM_CAP) == 0)
                lpSFL1API->SF_QueryStaticSampleMemorySize(BestsfIdx,&dwMaxMem,&dwAvailableMemBest);
            else
                dwAvailableMemBest=0xFFFFFFFF;

            // Need to find the Router ID associated with this device
            lpSFL1API->SF_GetRouterID(BestsfIdx, &dwRouterID);

            // Call macro to obtain routing index
            SFMAN_GET_ROUTING_INDEX(dwRouterID, sfRouterCommand[7], sfRouterCommand[8],
                                    sfRouterCommand[9], sfRouterCommand[10]);

            memset(&sysExMessage, 0, sizeof(MIDIHDR));
            sysExMessage.lpData = (char*) sfRouterCommand;
            sysExMessage.dwBufferLength = 12;

            if (midiOutPrepareHeader(hMIDIOutInteractive, &sysExMessage, sizeof(MIDIHDR)) ==0 )
            {
                if (midiOutLongMsg(hMIDIOutInteractive, &sysExMessage, sizeof(MIDIHDR)) ==0 )
                    SFontSet = TRUE;
                else
                    retval = FALSE;
            }
            else
                retval = FALSE;
        }
        else
            retval = FALSE;
    }
    else
    {
        // Close down the SoundFont compatible device.
        SFontSet = FALSE;

        if ((lpSFL1API != NULL) && (numSFDevs != 0))
        {
            ClearBank();

            lpSFL1API->SF_Close(BestsfIdx);
            FreeLibrary ((HINSTANCE__*) hSFMANDLL );

            lpSFL1API = NULL;
            numSFDevs = 0;
        }
    }

    return retval;
}