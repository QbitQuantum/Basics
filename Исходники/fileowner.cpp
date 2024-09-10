bool GetFileOwner(const wchar_t *Computer,const wchar_t *Name, string &strOwner)
{
	bool Result=false;
	/*
	if(!Owner)
	{
		SIDCacheFlush();
		return TRUE;
	}
	*/
	strOwner.Clear();
	SECURITY_INFORMATION si=OWNER_SECURITY_INFORMATION|GROUP_SECURITY_INFORMATION;;
	DWORD LengthNeeded=0;
	NTPath strName(Name);
	PSECURITY_DESCRIPTOR sd=reinterpret_cast<PSECURITY_DESCRIPTOR>(sddata);

	if (GetFileSecurity(strName,si,sd,sizeof(sddata),&LengthNeeded) && LengthNeeded<=sizeof(sddata))
	{
		PSID pOwner;
		BOOL OwnerDefaulted;
		if (GetSecurityDescriptorOwner(sd,&pOwner,&OwnerDefaulted))
		{
			if (IsValidSid(pOwner))
			{
				const wchar_t *Owner=GetNameFromSIDCache(pOwner);
				if (!Owner)
				{
					Owner=AddSIDToCache(Computer,pOwner);
				}
				if (Owner)
				{
					strOwner=Owner;
					Result=true;
				}
			}
		}
	}
	return Result;
}