	void Init() 
	{
		SetFlags( ACH_LISTEN_MAP_EVENTS | ACH_SAVE_WITH_GAME );
		SetGameDirFilter( "episodic" );
		SetGoal( 1 );
	}