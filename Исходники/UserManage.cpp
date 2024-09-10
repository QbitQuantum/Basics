void CUserManage::SendAllUser( char* Buffer, int len )
{
	EnterCriticalSection( &g_CheckCritical ); //Lock
	USER_MAP::Iterator Iter1 = m_UserMap.m_UserTypeMap.begin();
	USER_MAP::Iterator Iter2 = m_UserMap.m_UserTypeMap.end();
	CUser* pUser;
	for( ;Iter1!=Iter2;Iter1++ )
	{
		pUser = (*Iter1).second;
		if( pUser )
		{
			pUser->Send( Buffer, len );
		}
	}
	LeaveCriticalSection( &g_CheckCritical ); //UnLock
}