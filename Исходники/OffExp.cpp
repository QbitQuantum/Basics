//=====================================
//	Fairy Elf Offline Experience
//=====================================
void cOffExp::FairyElfOff(LPOBJ lpObj)
{
	int SearchSkill = 0;
	int dis;
	int tObjNum;
	BYTE attr;

	CMagicInf * lpMagic;

	//Buff
	SYSTEMTIME time;
	GetLocalTime(&time);
	if( time.wSecond == 0  || time.wSecond == 10 || 
	    time.wSecond == 20 || time.wSecond == 30 ||
	    time.wSecond == 40 || time.wSecond == 50 )
	{
		int partynum = -1;
		int partycount;
		int number;

		LPOBJ lpPartyObj;

		partynum = lpObj->PartyNumber;

		if(partynum != -1)
		{
			partycount = gParty.m_PartyS[partynum].Count;

			for(int j = 0; j < MAX_USER_IN_PARTY; j++)
			{
				number = gParty.m_PartyS[partynum].Number[j];

				if(number >= 0)
				{
					lpPartyObj = &gObj[number];

					if(lpObj->MapNumber == lpPartyObj->MapNumber)
					{
						dis = gObjCalDistance(lpObj,&gObj[number]);

						if(dis < 6)
						{
							//Defence Baf
							if(gObjGetMagicSearch( lpObj, 27) != NULL) SearchSkill = 27;
							else if(gObjGetMagicSearch( lpObj, 480) != NULL) SearchSkill = 480;
							else if(gObjGetMagicSearch( lpObj, 481) != NULL) SearchSkill = 481;
							else if(gObjGetMagicSearch( lpObj, 482) != NULL) SearchSkill = 482;
							else if(gObjGetMagicSearch( lpObj, 483) != NULL) SearchSkill = 483;
							else if(gObjGetMagicSearch( lpObj, 484) != NULL) SearchSkill = 484;
							else SearchSkill = 0;
							if(SearchSkill != 0)
							{
								lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
								if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpObj->m_Index, lpMagic);
							}
							//Damage Baf
							if(gObjGetMagicSearch( lpObj, 28) != NULL) SearchSkill = 28;
							else if(gObjGetMagicSearch( lpObj, 485) != NULL) SearchSkill = 485;
							else if(gObjGetMagicSearch( lpObj, 486) != NULL) SearchSkill = 486;
							else if(gObjGetMagicSearch( lpObj, 487) != NULL) SearchSkill = 487;
							else if(gObjGetMagicSearch( lpObj, 488) != NULL) SearchSkill = 488;
							else if(gObjGetMagicSearch( lpObj, 489) != NULL) SearchSkill = 489;
							else SearchSkill = 0;
							if(SearchSkill != 0)
							{
								lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
								if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpObj->m_Index, lpMagic);
							}
							//Heal Baf
							if(gObjGetMagicSearch( lpObj, 26) != NULL) SearchSkill = 26;
							else if(gObjGetMagicSearch( lpObj, 475) != NULL) SearchSkill = 475;
							else if(gObjGetMagicSearch( lpObj, 476) != NULL) SearchSkill = 476;
							else if(gObjGetMagicSearch( lpObj, 477) != NULL) SearchSkill = 477;
							else if(gObjGetMagicSearch( lpObj, 478) != NULL) SearchSkill = 478;
							else if(gObjGetMagicSearch( lpObj, 479) != NULL) SearchSkill = 479;
							else SearchSkill = 0;
							if(SearchSkill != 0)
							{
								lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
								if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpObj->m_Index, lpMagic);
							}
						}
					}
				}
			}
		}
		else
		{
			//Defence Baf
			if(gObjGetMagicSearch( lpObj, 27) != NULL) SearchSkill = 27;
			else if(gObjGetMagicSearch( lpObj, 480) != NULL) SearchSkill = 480;
			else if(gObjGetMagicSearch( lpObj, 481) != NULL) SearchSkill = 481;
			else if(gObjGetMagicSearch( lpObj, 482) != NULL) SearchSkill = 482;
			else if(gObjGetMagicSearch( lpObj, 483) != NULL) SearchSkill = 483;
			else if(gObjGetMagicSearch( lpObj, 484) != NULL) SearchSkill = 484;
			else SearchSkill = 0;
			if(SearchSkill != 0)
			{
				lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
				if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpObj->m_Index, lpMagic);
			}
			//Damage Baf
			if(gObjGetMagicSearch( lpObj, 28) != NULL) SearchSkill = 28;
			else if(gObjGetMagicSearch( lpObj, 485) != NULL) SearchSkill = 485;
			else if(gObjGetMagicSearch( lpObj, 486) != NULL) SearchSkill = 486;
			else if(gObjGetMagicSearch( lpObj, 487) != NULL) SearchSkill = 487;
			else if(gObjGetMagicSearch( lpObj, 488) != NULL) SearchSkill = 488;
			else if(gObjGetMagicSearch( lpObj, 489) != NULL) SearchSkill = 489;
			else SearchSkill = 0;
			if(SearchSkill != 0)
			{
				lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
				if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpObj->m_Index, lpMagic);
			}
			//Heal Baf
			if(gObjGetMagicSearch( lpObj, 26) != NULL) SearchSkill = 26;
			else if(gObjGetMagicSearch( lpObj, 475) != NULL) SearchSkill = 475;
			else if(gObjGetMagicSearch( lpObj, 476) != NULL) SearchSkill = 476;
			else if(gObjGetMagicSearch( lpObj, 477) != NULL) SearchSkill = 477;
			else if(gObjGetMagicSearch( lpObj, 478) != NULL) SearchSkill = 478;
			else if(gObjGetMagicSearch( lpObj, 479) != NULL) SearchSkill = 479;
			else SearchSkill = 0;
			if(SearchSkill != 0)
			{
				lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
				if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpObj->m_Index, lpMagic);
			}
		}
	}

	lpMagic = gObjGetMagicSearch( lpObj, 235);	//Multi-Shot 235
	if(lpMagic==NULL) return;

	int NumDir[6] = {0, 50, 100, 150, 200, 250 };
	int StartDir = NumDir[rand()%6];
	gObjUseSkill.UseSkill(lpObj->m_Index, lpMagic,lpObj->X, lpObj->Y,StartDir,0,-1);

	for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;
		if(lpObj->VpPlayer2[n].state == 0) continue;
		if ( tObjNum >= 0 )
		{
			if ( gObj[tObjNum].Type == OBJ_MONSTER )
			{
				attr = MapC[gObj[tObjNum].MapNumber].GetAttr(gObj[tObjNum].X, gObj[tObjNum].Y);
				if ( (attr&1) != 1 )
				{
					dis = gObjCalDistance(lpObj, &gObj[tObjNum]);
					if(5 >= dis)
					{
						gObjAttack(lpObj, &gObj[tObjNum], lpMagic, FALSE, 1, 0, FALSE, 0 , 0);
					}
				}
			}
		}
	}

	this->UseMana(lpObj->m_Index);
}