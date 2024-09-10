BOOL  ffplayer::SetPlayedTime(DWORD nTime)
{	
	DWORD FileTime = GetFileTime();
	if (FileTime == 0)
	{
		m_seekTime = 0;
		return false;
	}

	float fPos = (float) nTime / (float)FileTime;
	SetPlayPos(fPos);
	m_seekTime = nTime;
	return true;
}