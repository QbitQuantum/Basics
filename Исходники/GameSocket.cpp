void CGameSocket::RecvUserInfo(char* pBuf)
{
//	TRACE("RecvUserInfo()\n");
	int index = 0;
	short uid=-1, sHp, sMp, sLength = 0;
	BYTE bNation, bLevel, bZone, bAuthority=1;
	short sDamage, sAC;
	float fHitAgi, fAvoidAgi;
	char strName[MAX_ID_SIZE+1];
	memset(strName, 0x00, MAX_ID_SIZE+1);
//
	short  sItemAC;
	BYTE   bTypeLeft;
	BYTE   bTypeRight;
	short  sAmountLeft;
	short  sAmountRight;
//
	uid = GetShort( pBuf, index );
	sLength = GetShort( pBuf, index );
	if( sLength > MAX_ID_SIZE || sLength <= 0 ) {
		char countstr[256];
		memset( countstr, NULL, 256 );
		CTime cur = CTime::GetCurrentTime();
		sprintf( countstr, "RecvUserInfo() Fail : %d월 %d일 %d시 %d분 - uid=%d, name=%s\r\n", cur.GetMonth(), cur.GetDay(), cur.GetHour(), cur.GetMinute(), uid, strName);
		LogFileWrite( countstr );
		TRACE("###  RecvUserInfo() Fail ---> uid = %d, name=%s  ### \n", uid, strName);
		return;
	}
	GetString(strName, pBuf, sLength, index);
	bZone = GetByte( pBuf, index );
	bNation = GetByte( pBuf, index );
	bLevel = GetByte( pBuf, index );
	sHp = GetShort( pBuf, index );
	sMp = GetShort( pBuf, index );
	sDamage = GetShort( pBuf, index );
	sAC = GetShort( pBuf, index );
	fHitAgi = Getfloat( pBuf, index );
	fAvoidAgi = Getfloat( pBuf, index );
//
	sItemAC = GetShort(pBuf, index);
	bTypeLeft = GetByte(pBuf, index);
	bTypeRight = GetByte(pBuf, index);
	sAmountLeft = GetShort(pBuf, index);
	sAmountRight = GetShort(pBuf, index);
	bAuthority = GetByte(pBuf, index);
//

	//CUser* pUser = m_pMain->GetActiveUserPtr(uid);
	//if( pUser == NULL )		return;
	CUser* pUser = new CUser;
	pUser->Initialize();

	pUser->m_iUserId = uid;
	strcpy(pUser->m_strUserID, strName);
	pUser->m_curZone = bZone;
	pUser->m_pMap = m_pMain->GetZoneByID(bZone);
	pUser->m_bNation = bNation;
	pUser->m_sLevel = bLevel;
	pUser->m_sHP = sHp;
	pUser->m_sMP = sMp;
	//pUser->m_sSP = sSp;
	pUser->m_sHitDamage = sDamage;
	pUser->m_fHitrate = fHitAgi;
	pUser->m_fAvoidrate = fAvoidAgi;
	pUser->m_sAC = sAC;
	pUser->m_bLive = USER_LIVE;
//
	pUser->m_sItemAC = sItemAC;
	pUser->m_bMagicTypeLeftHand = bTypeLeft;
	pUser->m_bMagicTypeRightHand = bTypeRight;
	pUser->m_sMagicAmountLeftHand = sAmountLeft;
	pUser->m_sMagicAmountRightHand = sAmountRight;
	pUser->m_byIsOP = bAuthority;
//

	TRACE("****  RecvUserInfo()---> uid = %d, name=%s, leng=%d  ******\n", uid, strName, sLength);

	if(uid >= USER_BAND && uid < MAX_USER)	{
		m_pMain->m_pUser[uid] = pUser;
	}

	_USERLOG* pUserLog = NULL;
	pUserLog = new _USERLOG;
	pUserLog->t = CTime::GetCurrentTime();
	pUserLog->byFlag = USER_LOGIN;
	pUserLog->byLevel = pUser->m_sLevel;
	strcpy( pUserLog->strUserID, pUser->m_strUserID );
	pUser->m_UserLogList.push_back( pUserLog );
}