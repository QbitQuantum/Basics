int write_ini_value(char *section,char *key,int val)
{
	char str[20]={0};
	_snprintf(str,sizeof(str),"%i",val);
	if(ini_file[0]!=0){
		if(WritePrivateProfileStringA(section,key,str,ini_file)!=0)
			return TRUE;
		else
			return FALSE;
	}
	else{
		if(write_private_profile_string(section,key,str,&ram_ini)!=0)
			return TRUE;
		else
			return FALSE;
	}
}