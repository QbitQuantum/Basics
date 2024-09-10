//-----------------------------------------------------------------------------
// Purpose: Run through all the Bots in the game and let them think.
//-----------------------------------------------------------------------------
void Bot_RunAll( void )
{
	if ( !botmanager )
		return;

	for ( int i = 0; i < s_Bots.Count(); i++ )
	{
		CPluginBot & bot = s_Bots[i];
		if ( bot.m_BotEdict->IsFree() || !bot.m_BotEdict->GetUnknown()|| !bot.m_PlayerInfo->IsConnected() )
		{
			s_Bots.Remove(i);
			--i;
		}
		else
		{
			Bot_Think( &bot );
		}
	}
}