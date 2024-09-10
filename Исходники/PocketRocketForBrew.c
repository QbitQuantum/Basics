// this function is called when your application is starting up
boolean PocketRocketForBrew_InitAppData(PocketRocketForBrew* pMe)
{
    AECHAR os[] = {'B','r','e','w','\0'};
	char resx[5];
	char resy[5];
	AECHAR wresx[5];
	AECHAR wresy[5];
	AECHAR url[512];
	char curl[512];
	AECHAR fchunk[] = {'?','O','S','=','B','r','e','w','&','H','E','I','G','H','T','=','\0'};
	AECHAR schunk[] = {'&','W','I','D','T','H','=','\0'};
	AECHAR tchunk[] = {'&','I','D','=','1','\0'};
	// Get the device information for this handset.
    // Reference all the data by looking at the pMe->DeviceInfo structure
    // Check the API reference guide for all the handy device info you can get
    pMe->DeviceInfo.wStructSize = sizeof(pMe->DeviceInfo);
	ISHELL_GetDeviceInfo(pMe->a.m_pIShell,&pMe->DeviceInfo);
//	std::string a;
	
	STRCPY(url,XID_URL);
   // str
	
	itoa((int)pMe->DeviceInfo.cyScreen,resx,10);
	itoa((int)pMe->DeviceInfo.cxScreen,resy,10);
	STRTOWSTR(wresx,resx,strlen(resx));
	STRTOWSTR(wresy,resy,strlen(resy));
	//strcp
	STRCAT(url,fchunk);
	STRCAT(url,wresy);
	STRCAT(url,schunk);
	STRCAT(url,wresx);
	STRCAT(url,tchunk);

	WSTRTOSTR(curl,url,strlen(curl));
	printf(url);
	
	//strcat(


	

    // Insert your code here for initializing or allocating resources...

	//XOsApplication *xosApplication = new XOsApplication("Testing");
	
	
	





    // if there have been no failures up to this point then return success
    return TRUE;
}