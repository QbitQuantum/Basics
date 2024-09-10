void CSoundMng::LoadSoundConfig( char* filename )
{
	char* token;
	char soundName[128];
	int idx, is3D, dup, resType = 0, type, eventType, soundID;
	float fraction, freq;

	Initialize();

	g_script.Load( filename );
	g_script.BeginParse();

	m_maxIdx	=	0;

	while( 1 )
	{
		token = g_script.GetNextToken( true );
		if( token[0] == 0 ) break;

		if( !stricmp( token, "RESOURCE" ) ) resType = 0;
		if( !stricmp( token, "MATCHING" ) ) resType = 1;
		else if( token[0] == '{' )
		{
			while( 1 )
			{
				token = g_script.GetNextToken( true );
				if( token[0] == '}' ) break;

				
				if( !resType )
				{
					if( !stricmp( token, "NORMAL" ) ) type = 0;
					else if( !stricmp( token, "ITEM" ) ) type = 1;
					else if( !stricmp( token, "EVENT_IDLE" ) ) { type = 2; eventType = ANIM_ITEM_IDLE; }
					else if( !stricmp( token, "EVENT_DAMAGE" ) ) { type = 2; eventType = ANIM_ITEM_DEFENSE; }
					else if( !stricmp( token, "EVENT_DIE" ) ) { type = 2; eventType = ANIM_ITEM_DYING_0; }
					else if( !stricmp( token, "EVENT_WALK" ) ) { type = 2; eventType = ANIM_ITEM_WALK; }
					else if( !stricmp( token, "EVENT_RUN" ) ) { type = 2; eventType = ANIM_ITEM_RUN; }
					else if( !stricmp( token, "EVENT_ATTACK" ) ) { type = 2; eventType = ANIM_ITEM_ATTACK_0; }
					else if( !stricmp( token, "EVENT_SHOCK" ) ) { type = 2; eventType = ANIM_ITEM_ATTACKED_0; }
					else if( token[0] == '{' )
					{
						while( 1 )
						{
							token = g_script.GetNextToken( true );
							if( token[0] == '}' ) break;

							
							idx = atoi( token );
							
							token = g_script.GetNextToken( true );
							strcpy( soundName, token );
							
							token = g_script.GetNextToken( true );
							is3D = atoi( token );
							
							token = g_script.GetNextToken( true );
							dup = atoi( token );
							if( type == 0 )
							{
								m_soundResource.normalID[idx].idx = idx;
								strcpy( m_soundResource.normalID[idx].filename, soundName );
								m_soundResource.normalID[idx].is3D = is3D;
								m_soundResource.normalID[idx].numDup = dup;
								m_soundResource.numNoramlID ++;

								m_maxIdx ++;
							}
							else if( type == 1 )
							{
								m_soundResource.itemID[idx].idx = idx;
								strcpy( m_soundResource.itemID[idx].filename, soundName );
								m_soundResource.itemID[idx].is3D = is3D;
								m_soundResource.itemID[idx].numDup = dup;
								m_soundResource.numItemID ++;

								m_maxIdx ++;
							}
							else if( type == 2 )
							{
								m_soundResource.eventID[eventType][idx].idx = idx;
								strcpy( m_soundResource.eventID[eventType][idx].filename, soundName );
								m_soundResource.eventID[eventType][idx].is3D = is3D;
								m_soundResource.eventID[eventType][idx].numDup = dup;
								m_soundResource.numEventID[eventType] ++;

								m_maxIdx ++;
							}
						}
					}
				}
				else
				{
					if( !stricmp( token, "ITEM" ) ) type = 0;
					else if( !stricmp( token, "PC" ) ) type = 1;
					else if( !stricmp( token, "MONSTER" ) ) type = 2;
					else if( token[0] == '{' )
					{
						while( 1 )
						{
							token = g_script.GetNextToken( true );
							if( token[0] == '}' ) break;
							else if( type == 0 )
							{
								idx = atoi( token );
								
								token = g_script.GetNextToken( true );
								soundID = atoi( token );
								
								token = g_script.GetNextToken( true );
								fraction = atof( token );

								m_itemSound[idx].idx = idx;
								m_itemSound[idx].soundID = soundID;
								m_itemSound[idx].playTime = fraction;
							}
							else if( type == 1 )
							{
								if( !stricmp( token, "IDX" ) ) eventType = -1;
								else if( !stricmp( token, "IDLE" ) ) eventType = ANIM_ITEM_IDLE;
								else if( !stricmp( token, "WALK" ) ) eventType = ANIM_ITEM_WALK;
								else if( !stricmp( token, "RUN" ) ) eventType = ANIM_ITEM_RUN;
								else if( !stricmp( token, "DAMAGE" ) ) eventType = ANIM_ITEM_DEFENSE;
								else if( !stricmp( token, "ATTACK" ) ) eventType = ANIM_ITEM_ATTACK_0;
								else if( !stricmp( token, "SHOCK" ) ) eventType = ANIM_ITEM_ATTACKED_0;
								else if( !stricmp( token, "DIE" ) ) eventType = ANIM_ITEM_DYING_0;
								else if( eventType == -1 )
								{
									idx = atoi( token );
								}
								else
								{
									soundID = atoi( token );
								
									token = g_script.GetNextToken( true );
									fraction = atof( token );

									token = g_script.GetNextToken( true );
									freq = atoi( token );

									m_pcSound[idx].idx = idx;
									m_pcSound[idx].soundID[eventType] = soundID;
									m_pcSound[idx].playTime[eventType] = fraction;
									m_pcSound[idx].frequency[eventType] = freq;
								}
							}
							else if( type == 2 )
							{
								if( !stricmp( token, "IDX" ) ) eventType = -1;
								else if( !stricmp( token, "IDLE" ) ) eventType = ANIM_ITEM_IDLE;
								else if( !stricmp( token, "WALK" ) ) eventType = ANIM_ITEM_WALK;
								else if( !stricmp( token, "RUN" ) ) eventType = ANIM_ITEM_RUN;
								else if( !stricmp( token, "DAMAGE" ) ) eventType = ANIM_ITEM_DEFENSE;
								else if( !stricmp( token, "ATTACK" ) ) eventType = ANIM_ITEM_ATTACK_0;
								else if( !stricmp( token, "SHOCK" ) ) eventType = ANIM_ITEM_ATTACKED_0;
								else if( !stricmp( token, "DIE" ) ) eventType = ANIM_ITEM_DYING_0;
								else if( eventType == -1 )
								{
									idx = atoi( token );
								}
								else
								{
									soundID = atoi( token );
								
									token = g_script.GetNextToken( true );
									fraction = atof( token );

									token = g_script.GetNextToken( true );
									freq = atoi( token );

									m_monSound[idx].idx = idx;
									m_monSound[idx].soundID[eventType] = soundID;
									m_monSound[idx].playTime[eventType] = fraction;
									m_monSound[idx].frequency[eventType] = freq;
								}
							}
						}
					}
				}
			}
		}
	}
}