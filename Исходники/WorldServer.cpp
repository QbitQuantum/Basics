BOOL Script( LPCSTR lpszFileName )
{
	g_eLocal.SetState( EVE_RESPAWN, 1 );

	CScanner s;
	if( s.Load( lpszFileName ) == FALSE)
	{
		Error("Fail to open file - %s", lpszFileName );
		return FALSE;
	}

	s.GetToken();
	while( s.tok != FINISHED )
	{
		if( s.Token == "ResourceFolder" )
		{
			s.GetToken();
			if( !SetCurrentDirectory( s.Token ) )
			{
				Error( "Folder not found, %s", s.Token );
				return FALSE;
			}
		}
		else if( s.Token == "Key" )
		{
			g_uKey		 = (DWORD)s.GetNumber();
#ifdef __S8_SERVER_PORT
			g_uIdofMulti = g_uKey % 100;
#else // __S8_SERVER_PORT
			g_uIdofMulti = g_uKey / 100;
#endif // __S8_SERVER_PORT
		}
		else if( s.Token == "Core" )
		{
			s.GetToken();
			strcpy( g_szCoreAddr, s.Token );
		}
		else if( s.Token == "DB" )
		{
			s.GetToken();
			strcpy( g_szDBAddr, s.Token );
		}
		else if( s.Token == "Account" )
		{
			s.GetToken();
			/*
		#ifdef __GIFTBOX0213
			lstrcpy( s_szAccountAddr, s.Token );
		#endif	// __GIFTBOX0213
		*/
		}
		else if( s.Token == "Heartbeat" )
		{
			s.GetToken();
			strcpy( g_sHeartbeat, s.Token );
		}
		else if( s.Token == "18" )
		{
			g_eLocal.SetState( EVE_18, 1 );		// 18세 서버 
		}
		else if( s.Token == "PK" )
		{
			g_eLocal.SetState( EVE_PK, 1 );
		}
		else if( s.Token == "PKCOST" )
		{
			g_eLocal.SetState( EVE_PKCOST, 1 );
		}
		else if( s.Token == "STEAL" )
		{
			g_eLocal.SetState( EVE_STEAL, 1 );				
		}
		else if (s.Token == "GUILDBANK")
		{
			g_eLocal.SetState( ENABLE_GUILD_INVENTORY, 1 );
		}
		else if( s.Token == "GUILDWAR" )
		{
			g_eLocal.SetState( EVE_GUILDWAR, 1 );
		}
		else if( s.Token == "DROPITEM_REMOVE" )
		{
			g_eLocal.SetState( EVE_DROPITEMREMOVE, 1 );
		}			
		else if( s.Token == "SCHOOL" )
		{
			//g_eLocal.SetState( EVE_SCHOOL, 1 );
		}
		else if( s.Token == "GUILDCOMBAT")
		{
			g_eLocal.SetState( EVE_GUILDCOMBAT, 1 );
		}
		else if( s.Token == "WORMON" )
		{
			g_eLocal.SetState( EVE_WORMON, 1 );
		}
		else if( s.Token == "respawn" )
		{
			g_eLocal.SetState( EVE_RESPAWN, (BYTE)s.GetNumber() );
		}
#ifdef __S_RECOMMEND_EVE
		else if( s.Token == "RECOMMEND" )
		{
			g_eLocal.SetState( EVE_RECOMMEND, 1 );
		}
#endif // __S_RECOMMEND_EVE

#if __VER >= 11 // __GUILD_COMBAT_1TO1
		else if( s.Token == "GUILDCOMBAT1TO1" )
		{
			g_eLocal.SetState( EVE_GUILDCOMBAT1TO1, 1 );
		}
#endif // __GUILD_COMBAT_1TO1

#ifdef __JEFF_11_4
		else if( s.Token == "ARENA" )
		{
			g_eLocal.SetState( EVE_ARENA, 1 );
		}
#endif // __JEFF_11_4

#if __VER >= 12 // __SECRET_ROOM
		else if( s.Token == "SECRETROOM" )
		{
			g_eLocal.SetState( EVE_SECRETROOM, 1 );
		}
#endif // __SECRET_ROOM
#if __VER >= 13 // __RAINBOW_RACE
		else if( s.Token == "RAINBOWRACE" )
		{
			g_eLocal.SetState( EVE_RAINBOWRACE, 1 );
		}
#endif // __RAINBOW_RACE

		s.GetToken();
	}
	return TRUE;
}