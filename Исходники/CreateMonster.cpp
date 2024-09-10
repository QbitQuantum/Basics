BOOL CCreateMonster::LoadScript( LPCSTR lpszFileName )
{
	CScript Script;

	if( !Script.Load( lpszFileName ) )
		return FALSE;

	Script.GetToken();
	while( Script.tok != FINISHED )
	{
		DWORD dwMonsterId = atoi( Script.Token );
		Script.GetToken();	// {
		vector< __MONSTERPERSENT > VecMonsterPersent;
		Script.GetToken();
		while( *Script.token != '}' )
		{
			__MONSTERPERSENT OneMosterPersent;
			OneMosterPersent.dwMonsterId = atoi( Script.Token );
			OneMosterPersent.nPersent = Script.GetNumber();
			VecMonsterPersent.push_back( OneMosterPersent );
			Script.GetToken();
		}
		Script.GetToken();	
		pMonsterItem.insert( map< DWORD, vector<__MONSTERPERSENT > >::value_type( dwMonsterId, VecMonsterPersent ) );
	}
	return TRUE;
}