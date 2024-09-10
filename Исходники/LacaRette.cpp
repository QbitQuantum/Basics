bool CLacarette::Load()
{
	RemoveAll();

	CDBCmd dbQuest;
	CDBCmd dbQuest1;
	dbQuest.Init(&gserver->m_dbdata);
	dbQuest1.Init(&gserver->m_dbdata);
	dbQuest.SetQuery("SELECT * FROM t_lacarette WHERE a_enable=1 ORDER BY a_index");

	if ( !dbQuest.Open() )
		return false;

	if( !dbQuest.MoveFirst() )
		return true;

	if( dbQuest.m_nrecords <= 0)
		return false;

	m_count = dbQuest.m_nrecords;

	CourseInfo * ld = new CourseInfo[m_count];

	int i=0,j=0;
	CLCString temp1(64);
	char buf[64];

	do
	{
		dbQuest.GetRec("a_index",			ld[i].index);
		dbQuest.GetRec("a_useCoinCount",	ld[i].coinUseCnt);

		ld[i].coinIndex  = new int[ld[i].coinUseCnt];
		ld[i].coinDefCnt = new int[ld[i].coinUseCnt];
		ld[i].coinAddCnt = new int[ld[i].coinUseCnt];

		dbQuest.GetRec("a_coinIndex", temp1);
		for(j=0; j<ld[i].coinUseCnt; j++ )
		{
			buf[0] = '\0';
			temp1 = AnyOneArg(temp1, buf);
			if( strlen(buf) < 1 )
				break;
			ld[i].coinIndex[j] = atoi(buf);
		}

		dbQuest.GetRec("a_coinDefCount", temp1);
		for(j=0; j<ld[i].coinUseCnt; j++ )
		{
			buf[0] = '\0';
			temp1 = AnyOneArg(temp1, buf);
			if( strlen(buf) < 1 ) break;
			ld[i].coinDefCnt[j] = atoi(buf);
		}

		dbQuest.GetRec("a_coinAddCount", temp1);
		for(j = 0; j < ld[i].coinUseCnt; j++ )
		{
			buf[0] = '\0';
			temp1 = AnyOneArg(temp1, buf);
			if( strlen(buf) < 1 ) break;
			ld[i].coinAddCnt[j] = atoi(buf);
		}

		// give item info
		ld[i].giveItem = new GiveItemInfo[10];
		for(j = 0; j < LACARETTE_GIVE_ITEM_MAX; j++)
		{
			dbQuest.GetRec( a_giveItem_str[j].c_str(), temp1);

			buf[0] = '\0';
			temp1 = AnyOneArg(temp1, buf);
			if( strlen(buf) < 1 ) break;
			ld[i].giveItem[j].index = atoi(buf);

			buf[0] = '\0';
			temp1 = AnyOneArg(temp1, buf);
			if( strlen(buf) < 1 ) break;
			ld[i].giveItem[j].count = ((LONGLONG)ATOLL(buf));

			buf[0] = '\0';
			temp1 = AnyOneArg(temp1, buf);
			if( strlen(buf) < 1 ) break;
			ld[i].giveItem[j].flag = atoi(buf);

			buf[0] = '\0';
			temp1 = AnyOneArg(temp1, buf);
			if( strlen(buf) < 1 ) break;
			ld[i].giveItem[j].prob = atoi(buf);
		}
		i++;
	}
	while( dbQuest.MoveNext() );

	m_data = ld;
	return true;
}