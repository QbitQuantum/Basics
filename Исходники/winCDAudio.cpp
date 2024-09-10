//=============================================================================
// Return the length of the given track
//=============================================================================
int CCDAudio::GetTrackLength(const int nTrack)
{
	if(IsMediaInsert())
	{
		const int nBuffSize = 64;
		TCHAR szTrack[10];
		TCHAR szReqBuff[nBuffSize];
		TCHAR szBuff[nBuffSize];
		
		ITOA( nTrack, szTrack, 10 );
		lstrcpy( szReqBuff, _T("status cdaudio length track ") );
		lstrcat( szReqBuff, szTrack );

		m_nErrorCode = mciSendString( szReqBuff, szBuff, nBuffSize, NULL );    
		if( m_nErrorCode != 0 )
		{
			return 0;
		}

		TCHAR szMin[3], szSec[3];

		STRNCPY( szMin, szBuff, 2 );
		STRNCPY( szSec, (szBuff + 3), 2 );

		return ((ATOI(szMin) * 60) + ATOI(szSec));		
	}

	return 0;
}