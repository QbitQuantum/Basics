BOOL kuhl_m_pac_marshall_sid(PISID pSid, PVOID * current, DWORD * size)
{
	BOOL status = FALSE;
	PVOID newbuffer;
	DWORD sidSize, actualsize;
	sidSize = GetLengthSid(pSid);
	actualsize = sizeof(ULONG32) + sidSize;
	if(newbuffer = LocalAlloc(LPTR, *size + actualsize))
	{
		RtlCopyMemory(newbuffer, *current, *size);
		(*(PULONG32) ((PBYTE) newbuffer + *size)) = pSid->SubAuthorityCount;
		RtlCopyMemory((PBYTE) newbuffer + *size + sizeof(ULONG32), pSid, sidSize);

		LocalFree(*current);
		*current = newbuffer;
		*size += actualsize;

		status = TRUE;
	}
	return status;
}