// safe to call before m_isInitialized, only writes to localHeader
bool irsdkMemServer::regSessionInfo(const char *str)
{
	if(m_isInitialized)
	{
		if(str)
		{
			// only update if changed
			char *dest = (pSharedMem + localHeader.sessionInfoOffset);
			if(0 != strncmp(str, dest, localHeader.sessionInfoLen))
			{
				strncpy(dest, str, localHeader.sessionInfoLen);
				dest[localHeader.sessionInfoLen-1] = '\0';

				// flush caches to all processors
				_WriteBarrier();

				localHeader.sessionInfoUpdate++;
				pHeader->sessionInfoUpdate = localHeader.sessionInfoUpdate;
			}
		}
	}

	return false;
}