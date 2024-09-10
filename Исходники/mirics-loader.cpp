	miricsLoader::miricsLoader	(bool *success) {
	libraryLoaded	= false;
	*success	= false;
#ifdef	__MINGW32__
HKEY APIkey;
wchar_t APIkeyValue [256];
ULONG APIkeyValue_length = 255;
	if (RegOpenKey (HKEY_LOCAL_MACHINE,
	                TEXT("Software\\MiricsSDR\\API"),
	                &APIkey) != ERROR_SUCCESS) {
          fprintf (stderr,
	           "failed to locate API registry entry, error = %d\n",
	           (int)GetLastError());
	   return;
	}
	RegQueryValueEx (APIkey,
	                 (wchar_t *)L"Install_Dir",
	                 NULL,
	                 NULL,
	                 (LPBYTE)&APIkeyValue,
	                 (LPDWORD)&APIkeyValue_length);
//	Ok, make explicit it is in the 64 bits section
	wchar_t *x = wcscat (APIkeyValue, (wchar_t *)L"\\x64\\mir_sdr_api.dll");
//	fprintf (stderr, "Length of APIkeyValue = %d\n", APIkeyValue_length);
//	wprintf (L"API registry entry: %s\n", APIkeyValue);
	RegCloseKey(APIkey);

	Handle	= LoadLibrary (x);
	if (Handle == NULL) {
	  fprintf (stderr, "Failed to open mir_sdr_api.dll\n");
	  return;
	}
#else
//	Ǹote that under Ubuntu, the Mirics shared object does not seem to be
//	able to find the libusb. That is why we explicity load it here
	Handle		= dlopen ("libusb-1.0.so", RTLD_NOW | RTLD_GLOBAL);
	Handle		= dlopen ("libmir_sdr_api.so", RTLD_NOW);
//	Handle		= dlopen ("/usr/local/lib/libmir_sdr_api.so", RTLD_NOW);
	if (Handle == NULL) {
	   fprintf (stderr, "error report %s\n", dlerror ());
	   return;
	}
#endif
	libraryLoaded	= true;
//	Load the functions one by one
	my_mir_sdr_Init	= (pfn_mir_sdr_Init)
	                    GETPROCADDRESS (Handle, "mir_sdr_Init");
	if (my_mir_sdr_Init == NULL) {
	   fprintf (stderr, "Could not find mir_sdr_Init\n");
	   return;
	}
	my_mir_sdr_ReadPacket = (pfn_mir_sdr_ReadPacket)
	                    GETPROCADDRESS (Handle, "mir_sdr_ReadPacket");
	if (my_mir_sdr_ReadPacket == NULL) {
	   fprintf (stderr, "Could not find mir_sdr_ReadPacket\n");
	   return;
	}
	my_mir_sdr_SetRf	= (pfn_mir_sdr_SetRf)
	                    GETPROCADDRESS (Handle, "mir_sdr_SetRf");
	if (my_mir_sdr_SetRf == NULL) {
	   fprintf (stderr, "Could not find mir_sdr_SetRf\n");
	   return;
	}
	my_mir_sdr_SetFs	= (pfn_mir_sdr_SetFs)
	                    GETPROCADDRESS (Handle, "mir_sdr_SetFs");
	if (my_mir_sdr_SetFs == NULL) {
	   fprintf (stderr, "Could not find mir_sdr_SetFs\n");
	   return;
	}
	my_mir_sdr_SetGr	= (pfn_mir_sdr_SetGr)
	                    GETPROCADDRESS (Handle, "mir_sdr_SetGr");
	if (my_mir_sdr_SetGr == NULL) {
	   fprintf (stderr, "Could not find mir_sdr_SetGr\n");
	   return;
	}
	my_mir_sdr_SetGrParams	= (pfn_mir_sdr_SetGrParams)
	                    GETPROCADDRESS (Handle, "mir_sdr_SetGrParams");
	if (my_mir_sdr_SetGrParams == NULL) {
	   fprintf (stderr, "Could not find mir_sdr_SetGrParams\n");
	   return;
	}
	my_mir_sdr_SetDcMode	= (pfn_mir_sdr_SetDcMode)
	                    GETPROCADDRESS (Handle, "mir_sdr_SetDcMode");
	if (my_mir_sdr_SetDcMode == NULL) {
	   fprintf (stderr, "Could not find mir_sdr_SetDcMode\n");
	   return;
	}
	my_mir_sdr_SetDcTrackTime	= (pfn_mir_sdr_SetDcTrackTime)
	                    GETPROCADDRESS (Handle, "mir_sdr_SetDcTrackTime");
	if (my_mir_sdr_SetDcTrackTime == NULL) {
	   fprintf (stderr, "Could not find mir_sdr_SetDcTrackTime\n");
	   return;
	}
	my_mir_sdr_SetSyncUpdateSampleNum = (pfn_mir_sdr_SetSyncUpdateSampleNum)
	               GETPROCADDRESS (Handle, "mir_sdr_SetSyncUpdateSampleNum");
	if (my_mir_sdr_SetSyncUpdateSampleNum == NULL) {
	   fprintf (stderr, "Could not find mir_sdr_SetSyncUpdateSampleNum\n");
	   return;
	}
	my_mir_sdr_SetSyncUpdatePeriod	= (pfn_mir_sdr_SetSyncUpdatePeriod)
	                GETPROCADDRESS (Handle, "mir_sdr_SetSyncUpdatePeriod");
	if (my_mir_sdr_SetSyncUpdatePeriod == NULL) {
	   fprintf (stderr, "Could not find mir_sdr_SetSyncUpdatePeriod\n");
	   return;
	}
	my_mir_sdr_ApiVersion	= (pfn_mir_sdr_ApiVersion)
	                GETPROCADDRESS (Handle, "mir_sdr_ApiVersion");
	if (my_mir_sdr_ApiVersion == NULL) {
	   fprintf (stderr, "Could not find mir_sdr_ApiVersion\n");
	   return;
	}
	my_mir_sdr_Uninit	= (pfn_mir_sdr_Uninit)
	                    GETPROCADDRESS (Handle, "mir_sdr_Uninit");
	if (my_mir_sdr_Uninit == NULL) {
	   fprintf (stderr, "Could not find mir_sdr_Uninit\n");
	   return;
	}
//	my_mir_sdr_ResetUpdateFlags	= (pfn_mir_sdr_ResetUpdateFlags)
//	                GETPROCADDRESS (Handle, "mir_sdr_ResetUpdateFlags");
//	if (my_mir_sdr_ResetUpdateFlags == NULL) {
//	   fprintf (stderr, "Could not find mir_sdr_ResetUpdateFlags\n");
//	   return;
//	}

	fprintf (stderr, "Functions seem to be loaded\n");
	*success	= true;
//
//	If one wishes to link to the ".a", this is the way
//	my_mir_sdr_Init	= (pfn_mir_sdr_Init)&mir_sdr_Init;
//	my_mir_sdr_Uninit	= (pfn_mir_sdr_Uninit) &mir_sdr_Uninit;
//	my_mir_sdr_ReadPacket = (pfn_mir_sdr_ReadPacket) &mir_sdr_ReadPacket;
//	my_mir_sdr_SetRf	= (pfn_mir_sdr_SetRf) &mir_sdr_SetRf;
//	my_mir_sdr_SetFs	= (pfn_mir_sdr_SetFs) &mir_sdr_SetFs;
//	my_mir_sdr_SetGr	= (pfn_mir_sdr_SetGr) &mir_sdr_SetGr;
//	my_mir_sdr_SetGrParams	= (pfn_mir_sdr_SetGrParams) &mir_sdr_SetGrParams;
//	my_mir_sdr_SetDcMode	= (pfn_mir_sdr_SetDcMode) &mir_sdr_SetDcMode;
//	my_mir_sdr_SetDcTrackTime	= (pfn_mir_sdr_SetDcTrackTime)
//	                                      &mir_sdr_SetDcTrackTime;
//	my_mir_sdr_SetSyncUpdateSampleNum = (pfn_mir_sdr_SetSyncUpdateSampleNum)
//	                &mir_sdr_SetSyncUpdateSampleNum;
//	my_mir_sdr_SetSyncUpdatePeriod	= (pfn_mir_sdr_SetSyncUpdatePeriod)
//	                            &mir_sdr_SetSyncUpdatePeriod;
//	my_mir_sdr_ApiVersion	= (pfn_mir_sdr_ApiVersion) &mir_sdr_ApiVersion;
////	my_mir_sdr_ResetUpdateFlags	= (pfn_mir_sdr_ResetUpdateFlags)
////	                                     &mir_sdr_ResetUpdateFlags;
}