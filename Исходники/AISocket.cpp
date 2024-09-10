// ai server에 처음 접속시 npc의 모든 정보를 받아온다..
void CAISocket::RecvNpcInfoAll(char* pBuf)
{
	int index = 0;
	BYTE		byCount = 0;			// 마리수
	BYTE        byType;				// 0:처음에 등장하지 않는 몬스터, 1:등장
	short		nid;				// NPC index
	short		sid;				// NPC index
	BYTE		bZone;				// Current zone number
	short		sPid;				// NPC Picture Number
	short		sSize = 100;				// NPC Size
	int			iweapon_1;
	int			iweapon_2;
	char		szName[MAX_NPC_SIZE+1];		// NPC Name
	BYTE		byGroup;		// 소속 집단
	BYTE		byLevel;		// level
	float		fPosX;			// X Position
	float		fPosZ;			// Z Position
	float		fPosY;			// Y Position
	BYTE		byDirection;	// 
	BYTE		tNpcType;		// 00	: Monster
								// 01	: NPC
	int		iSellingGroup;
  	int		nMaxHP;			// 최대 HP
	int		nHP;			// 현재 HP
	BYTE		byGateOpen;		// 성문일경우 열림과 닫힘 정보
	short		sHitRate;
	BYTE		byObjectType;	// 보통 : 0, 특수 : 1

	byCount = GetByte(pBuf, index);

	for(int i=0; i<byCount; i++)
	{
		byType = GetByte(pBuf, index);
		nid = GetShort(pBuf, index);
		sid = GetShort(pBuf, index);
		sPid = GetShort(pBuf, index);
		sSize = GetShort(pBuf, index);
		iweapon_1 = GetDWORD(pBuf, index);
		iweapon_2 = GetDWORD(pBuf, index);
		bZone = GetByte(pBuf, index);
		int nLength = GetVarString(szName, pBuf, sizeof(BYTE), index);
		byGroup = GetByte(pBuf, index);
		byLevel  = GetByte(pBuf, index);
		fPosX = Getfloat(pBuf, index);
		fPosZ = Getfloat(pBuf, index);
		fPosY = Getfloat(pBuf, index);
		byDirection = GetByte(pBuf, index);
		tNpcType = GetByte(pBuf, index);
		iSellingGroup = GetDWORD(pBuf, index);
		nMaxHP = GetDWORD(pBuf, index);
		nHP = GetDWORD(pBuf, index);
		byGateOpen = GetByte(pBuf, index);
		sHitRate = GetShort(pBuf, index);
		byObjectType = GetByte(pBuf, index);

		//TRACE("RecvNpcInfoAll  : nid=%d, szName=%s, count=%d\n", nid, szName, byCount);

		if(nLength < 0 || nLength > MAX_NPC_SIZE)	{
			TRACE("#### RecvNpcInfoAll Fail : szName=%s\n", szName);
			continue;		// 잘못된 monster 아이디 
		}

		//TRACE("Recv --> NpcUserInfo : uid = %d, x=%f, z=%f.. \n", nid, fPosX, fPosZ);

		CNpc* pNpc = NULL;
		pNpc = new CNpc;
		if(pNpc == NULL)	{ 
			TRACE("#### Recv --> NpcUserInfoAll POINT Fail: uid=%d, sid=%d, name=%s, zone=%d, x=%f, z=%f.. \n", nid, sPid, szName, bZone, fPosX, fPosZ);
			continue;
		}
		pNpc->Initialize();

		pNpc->m_sNid = nid;
		pNpc->m_sSid = sid;
		pNpc->m_sPid = sPid;
		pNpc->m_sSize = sSize;
		pNpc->m_iWeapon_1 = iweapon_1;
		pNpc->m_iWeapon_2 = iweapon_2;
		strcpy(pNpc->m_strName, szName);
		pNpc->m_byGroup = byGroup;
		pNpc->m_byLevel = byLevel;
		pNpc->m_bCurZone = bZone;
		pNpc->m_pMap = m_pMain->GetZoneByID(bZone);
		pNpc->m_fCurX = fPosX;
		pNpc->m_fCurZ = fPosZ;
		pNpc->m_fCurY = fPosY;
		pNpc->m_byDirection = byDirection;
		pNpc->m_NpcState = NPC_LIVE;
		pNpc->m_tNpcType = tNpcType;
		pNpc->m_iSellingGroup = iSellingGroup;
		pNpc->m_iMaxHP = nMaxHP;
		pNpc->m_iHP = nHP;
		pNpc->m_byGateOpen = byGateOpen;
		pNpc->m_sHitRate = sHitRate;
		pNpc->m_byObjectType = byObjectType;
		pNpc->m_NpcState = NPC_LIVE;

		int nRegX = (int)fPosX / VIEW_DISTANCE;
		int nRegZ = (int)fPosZ / VIEW_DISTANCE;

		pNpc->m_sRegion_X = nRegX;
		pNpc->m_sRegion_Z = nRegZ;

		if (pNpc->GetMap() == NULL)
		{
			delete pNpc;
			pNpc = NULL;
			continue;
		}

		_OBJECT_EVENT* pEvent = NULL;
		if (pNpc->m_byObjectType == SPECIAL_OBJECT)
		{
			pEvent = pNpc->GetMap()->GetObjectEvent(pNpc->m_sSid);
			if( pEvent )	pEvent->byLife = 1;
		}

	//	TRACE("Recv --> NpcUserInfoAll : uid=%d, sid=%d, name=%s, x=%f, z=%f. gate=%d, objecttype=%d \n", nid, sPid, szName, fPosX, fPosZ, byGateOpen, byObjectType);

		if( !m_pMain->m_arNpcArray.PutData( pNpc->m_sNid, pNpc) ) {
			TRACE("Npc PutData Fail - %d\n", pNpc->m_sNid);
			delete pNpc;
			pNpc = NULL;
			continue;
		}

		if( byType == 0 )	{
			TRACE("Recv --> NpcUserInfoAll : 등록하면 안돼여,, uid=%d, sid=%d, name=%s\n", nid, sPid, szName);
			continue;		// region에 등록하지 말기...
		}

		pNpc->GetMap()->RegionNpcAdd(pNpc->m_sRegion_X, pNpc->m_sRegion_Z, pNpc->m_sNid);
	}
}