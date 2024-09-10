//------------------------------------------------------------------------------
int restore_sam_tree_access(HKEY start, char *pth)
{
	char path[MAX_PATH];
	char *p;
	HKEY key;
	DWORD err;
	SECURITY_DESCRIPTOR sd;
	DWORD admin_mask;

  strncpy(path,pth,MAX_PATH);
	admin_mask = WRITE_DAC | READ_CONTROL;

  char group_name[256];
  if (AdministratorGroupName(group_name, 255))
  {
      if(create_sd_from_list( &sd, 2, "SYSTEM", GENERIC_ALL,group_name, admin_mask) == FALSE)       //get local admin group
        if(create_sd_from_list( &sd, 2, "SYSTEM", GENERIC_ALL,"Administrators", admin_mask) == FALSE)       //english
          if(create_sd_from_list( &sd, 2, "SYSTEM", GENERIC_ALL,"Administrateurs", admin_mask) == FALSE)    //french
            if(create_sd_from_list( &sd, 2, "SYSTEM", GENERIC_ALL,"Administradores", admin_mask) == FALSE)  //spanish
              if(create_sd_from_list( &sd, 2, "SYSTEM", GENERIC_ALL,"Administratoren", admin_mask) == FALSE)//dutch
            return -1;
  }else if(create_sd_from_list( &sd, 2, "SYSTEM", GENERIC_ALL,"Administrators", admin_mask) == FALSE)       //english
          if(create_sd_from_list( &sd, 2, "SYSTEM", GENERIC_ALL,"Administrateurs", admin_mask) == FALSE)    //french
            if(create_sd_from_list( &sd, 2, "SYSTEM", GENERIC_ALL,"Administradores", admin_mask) == FALSE)  //spanish
              if(create_sd_from_list( &sd, 2, "SYSTEM", GENERIC_ALL,"Administratoren", admin_mask) == FALSE)//dutch
            return -1;

	// Remove the security on the user keys first.
	if(set_userkeys_security( start, path, &sd, 0) != 0)return -1;

	// now go up the path, restoring security
	do {
		if((err = RegOpenKeyEx( start, path, 0, WRITE_DAC, &key)) !=ERROR_SUCCESS)return -1;
		if((err = RegSetKeySecurity( key, DACL_SECURITY_INFORMATION,&sd)) != ERROR_SUCCESS)
    {
			RegCloseKey(key);
			return  -1;
		}
		RegCloseKey(key);
		p = strrchr(path, '\\');
		if( p != 0)
			*p = 0;
	} while( p != 0 );

	return 0;
}