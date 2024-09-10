bool MWinAccessControlList::AddAccessDeny(const char *accountname,DWORD permission)
	{
	BYTE sidbuffer[100];
	PSID psid=(SID *)&sidbuffer;
	DWORD sidsize=sizeof(sidbuffer);
	char domainbuffer[100];
	DWORD domainbuffersize=sizeof(domainbuffer);
	SID_NAME_USE snu;

	if(LookupAccountNameA(NULL,accountname,psid,&sidsize
			,(LPSTR)&domainbuffer,&domainbuffersize,&snu)==FALSE)
		{
		return false;
		}

	if(AddAccessDeniedAce(mpACL,ACL_REVISION,permission,psid)==false)
		{
		return false;
		}

	return true;
	}