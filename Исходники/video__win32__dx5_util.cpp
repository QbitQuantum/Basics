BOOL WINAPI dd_create_callback(LPGUID lpGuid,   LPSTR lpDeviceDescription,
							   LPSTR lpDriverName, LPVOID lpUserArg, HMONITOR hm)
{
	char * desired_driver = (char *)lpUserArg;

	//PG: Changed this as I'm not shure wheter driver name is guaranteed to
	//be unique even when using multiple displays.
	//Using lpGuid instead, which certainly IS unique.
	/*if (!stricmp(desired_driver,lpDriverName))
	   {
	   HRESULT res = DirectDrawCreate(lpGuid, &dx5_ddraw, 0);
	   return DDENUMRET_CANCEL;
	   }*/
	if (!lpGuid) //is the primary display driver
	{
		for(int i=0; i<=sizeof(GUID); i++)
		{
			if (((w8 *)&i4_win32_startup_options.guid_screen)[i]!=0)
			{
				//is the saved guid a null-guid?
				return DDENUMRET_OK;
			}
		}
		i4_dx5_check(DirectDrawCreate(lpGuid,&dx5_ddraw,0));
		return DDENUMRET_CANCEL;
	}
	if (memcmp(lpGuid,&i4_win32_startup_options.guid_screen,sizeof(GUID))==0)
	{
		HRESULT res=DirectDrawCreate(lpGuid,&dx5_ddraw,0);
		if (!i4_dx5_check(res))
		{
			MessageBox(NULL,"The currently choosen display device failed to initialize.\n"
							"Reverting to default (primary display driver)","DirectX initialisation failed",MB_OK);
			ZeroMemory(&i4_win32_startup_options.guid_screen,sizeof(GUID));
			i4_dx5_check(DirectDrawCreate(NULL,&dx5_ddraw,0));
		}
		return DDENUMRET_CANCEL;
	}
	return DDENUMRET_OK;
}