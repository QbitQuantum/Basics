void cDelayedHeal::Expire()
{
	P_CHAR pSource = FindCharBySerial( destSer );
	P_CHAR pTarget = FindCharBySerial( sourSer );

	if( !pSource || !pTarget )
		return;

	if( !pSource->inRange( pTarget, 5 ) )
	{
		if( pSource->objectType() == enPlayer )
		{
			P_PLAYER pp = dynamic_cast<P_PLAYER>(pSource);
			if( pp->socket() )
				pp->socket()->sysMessage( tr( "You are standing too far away to apply any bandages." ) );
		}
		return;
	}
}