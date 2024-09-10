/* IO_pp_init
 *
 * Read the ppdev entries from wine.conf, open the device and check
 * for nescessary IOCTRL
 * Report verbose about possible errors
 */
char IO_pp_init(void)
{
    char name[80];
    char buffer[1024];
    HKEY hkey;
    char temp[256];
    int i,idx=0,fd,res,userbase,nports=0;
    char * timeout;
    char ret=1;
    int lasterror;

    TRACE("\n");
    if (RegOpenKeyA( HKEY_LOCAL_MACHINE, "Software\\Wine\\Wine\\Config\\ppdev", &hkey ) != ERROR_SUCCESS)
      return 1;

    for (;;)
    {
        DWORD type, count = sizeof(buffer), name_len = sizeof(name);

        if (RegEnumValueA( hkey, idx, name, &name_len, NULL, &type,
                           (LPBYTE)buffer, &count )!= ERROR_SUCCESS)
	  break;

	idx++;
	if(nports >4)
	  {
	    FIXME("Make the PPDeviceList larger then 5 elements\n");
	    break;
	  }
	TRACE("Device '%s' at virtual userbase '%s'\n", buffer,name);
	timeout = strchr(buffer,',');
	if (timeout)
	  *timeout++=0;
	fd=open(buffer,O_RDWR);
	lasterror=errno;
	if (fd == -1)
	  {
	    WARN("Configuration: No access to %s Cause: %s\n",buffer,strerror(lasterror));
	    WARN("Rejecting configuration item\n");
	    if (lasterror == ENODEV)
	      FIXME("Is the ppdev module loaded?\n");
	    continue;
	  }
	userbase = strtol(name,(char **)NULL, 16);
	if ( errno == ERANGE)
	  {
	    WARN("Configuration: Invalid base %s for %s\n",name,buffer);
	    WARN("Rejecting configuration item\n");
	    continue;
	  }
	if (ioctl (fd,PPCLAIM,0))
	  {
	    ERR("PPCLAIM rejected %s\n",buffer);
	    ERR("Perhaps the device is already in use or non-existant\n");
	    continue;
	  }
	if (nports > 0)
	  {
	    for (i=0; i<= nports; i++)
	      {
		if (PPDeviceList[i].userbase == userbase)
		  {
		    WARN("Configuration: %s uses the same virtual ports as %s\n",
			 buffer,PPDeviceList[0].devicename);
		    WARN("Configuration: Rejecting configuration item");
		    userbase = 0;
		    break;
		  }
	      }
	    if (!userbase) continue;
	  }
	/* Check for the minimum required IOCTLS */
	if ((ioctl(fd,PPRDATA,&res))||
	    (ioctl(fd,PPRCONTROL,&res))||
	    (ioctl(fd,PPRCONTROL,&res)))
	  {
	    ERR("PPUSER IOCTL not available for parport device %s\n",temp);
	    continue;
	  }
	if (ioctl (fd,PPRELEASE,0))
	  {
	    ERR("PPRELEASE rejected %s\n",buffer);
	    ERR("Perhaps the device is already in use or non-existant\n");
	    continue;
	  }
	PPDeviceList[nports].devicename = malloc(sizeof(buffer)+1);
	if (!PPDeviceList[nports].devicename)
	  {
	    ERR("No (more)space for devicename\n");
	    break;
	  }
	strcpy(PPDeviceList[nports].devicename,buffer);
	PPDeviceList[nports].fd = fd;
	PPDeviceList[nports].userbase = userbase;
	PPDeviceList[nports].lastaccess=NtGetTickCount();
	if (timeout)
	  {
	    PPDeviceList[nports].timeout = strtol(timeout,(char **)NULL, 10);
	    if (errno == ERANGE)
	      {
		WARN("Configuration:Invalid timeout %s in configuration for %s, Setting to 0\n",
		     timeout,buffer);
		PPDeviceList[nports].timeout = 0;
	      }
	  }
	else
	  PPDeviceList[nports].timeout = 0;
	nports++;
    }
    TRACE("found %d ports\n",nports);
    RegCloseKey( hkey );

    PPDeviceNum= nports;
    if (nports > 1)
      /* sort in accending order for userbase for faster access*/
      qsort (PPDeviceList,PPDeviceNum,sizeof(PPDeviceStruct),IO_pp_sort);

    if (nports)
      ret=0;
    for (idx= 0;idx<PPDeviceNum; idx++)
      TRACE("found device %s userbase %x fd %x timeout %d\n",
	    PPDeviceList[idx].devicename, PPDeviceList[idx].userbase,
	    PPDeviceList[idx].fd,PPDeviceList[idx].timeout);
    /* FIXME:
       register a timer callback perhaps every 30 second to release unused ports
       Set lastaccess = 0 as indicator when port was released
    */
    return ret;
}