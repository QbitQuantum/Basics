int main(int argc, char **argv)
{
	int i;
	HINSTANCE     hPacket;
	DWORD         dwVersion, dwMajorVersion;
	char			AdapterInfo[NIC_BUFFER_SIZE] = { '\0','\0' };
	unsigned long	AdapterLength = NIC_BUFFER_SIZE;
	LPWSTR			wstrName;
	LPSTR			strName, strDesc;
	int				nAdapterCount;
	PCHAR           dllVersion;
	PCHAR           testString;
	int		nDLLMajorVersion, nDLLMinorVersion;


	// Attemp to load the WinpCap packet library
	hPacket = LoadLibrary("PACKET.DLL");
        if(hPacket)
	{
		// Now look up the address
		PacketGetAdapterNames = (BOOLEAN (*)(PTSTR, PULONG))GetProcAddress(hPacket, "PacketGetAdapterNames");
		PacketGetVersion = (PCHAR (*)())GetProcAddress(hPacket, "PacketGetVersion");
	}
	else {
		printf("Could not load WinPCap driver!\n");
		printf ("You can download them for free from\n");
		printf ("http://www.winpcap.org/\n");
		myexit(1);
	}

	dwVersion      = GetVersion();
	dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));

        // Get DLL Version and Tokenize
        dllVersion = PacketGetVersion();
        nDLLMajorVersion = -1;
        nDLLMinorVersion = -1;
        for ( testString = strtok(dllVersion, ", ");
              testString != NULL;
              testString = strtok(NULL, ", ") )
        {
                // If Single Character, Convert
                if ( strlen( testString ) == 1 )
                {
                        // Check Major First
                        if ( nDLLMajorVersion == -1 )
                        {
                                nDLLMajorVersion = atoi(testString);
                        }
                        else if ( nDLLMinorVersion == -1 )
                        {
                                nDLLMinorVersion = atoi(testString);
                        }
                }
        }

	// Get out blob of adapter info
	PacketGetAdapterNames(AdapterInfo,&AdapterLength);

	// If this is Windows NT ... And DLL Returns UNICODE
	if(!(dwVersion >= 0x80000000 && dwMajorVersion >= 4) &&
           !(nDLLMajorVersion >= 3 && nDLLMinorVersion >= 1))
	{
		wstrName=(LPWSTR)AdapterInfo;

		// Obtain Names
		nAdapterCount = 0;
		while ((*wstrName))
		{
			// store pointer to name
			niNT[nAdapterCount].wstrName=wstrName;
			wstrName += lstrlenW(wstrName) +1;
			nAdapterCount++;
		}

		strDesc = (LPSTR)++wstrName;

		// Obtain descriptions ....
		for(i=0;i<nAdapterCount;i++)
		{
			// store pointer to description
			niNT[i].strDesc=strDesc;
			strDesc += lstrlen(strDesc) +1;

			// ... and display adapter info
			printf("\n%d: %s\n",i+1,niNT[i].strDesc);
			wprintf(L"     Device: %s",niNT[i].wstrName);
		}

		if(i)
		{
			printf("\n\nExample config for bochsrc:\n");
			wprintf(L"ne2k: ioaddr=0x300, irq=3, mac=b0:c4:20:00:00:00, ethmod=win32, ethdev=%s",niNT[0].wstrName);
			printf("\n");
		}

	}
	else
	{
		// Windows 9x
		strName=(LPSTR)AdapterInfo;

		// Obtain Names
		nAdapterCount = 0;
		while ((*strName))
		{
			// store pointer to name
			ni9X[nAdapterCount].strName=strName;
			strName += lstrlen(strName) +1;
			nAdapterCount++;
		}

		strDesc = (LPSTR)++strName;

		// Obtain descriptions ....
		for(i=0;i<nAdapterCount;i++)
		{
			// store pointer to description
			ni9X[i].strDesc=strDesc;
			strDesc += lstrlen(strDesc) +1;

			// ... and display adapter info
			printf("\n%d: %s\n",i+1,ni9X[i].strDesc);
			printf("     Device: %s",ni9X[i].strName);
		}

		if(i)
		{
			printf("\n\nExample config for bochsrc:\n");
			printf("ne2k: ioaddr=0x300, irq=3, mac=b0:c4:20:00:00:00, ethmod=win32, ethdev=%s",ni9X[0].strName);
			printf("\n");
		}

		printf("\n");
	}

	myexit (0);
	return 0; /* shut up stupid compilers */
}