void cSkills::Snooping( P_PLAYER player, P_ITEM container )
{
	cUOSocket* socket = player->socket();

	if ( !socket )
		return;

	P_CHAR pc_owner = container->getOutmostChar();
	P_PLAYER pp_owner = dynamic_cast<P_PLAYER>( pc_owner );

	if ( pp_owner && pp_owner->isGMorCounselor() )
	{
		pp_owner->message( tr( "%1 is trying to snoop in your pack" ).arg( player->name() ) );
		socket->sysMessage( tr( "You can't peek into that container or you'll be jailed." ) );
		return;
	}
	else if ( player->checkSkill( SNOOPING, 0, 1000 ) )
	{
		socket->sendContainer( container );
		socket->sysMessage( tr( "You successfully peek into that container." ) );
	}
	else
	{
		socket->sysMessage( tr( "You failed to peek into that container." ) );

		if ( !pp_owner ) // is NPC ?
			pc_owner->talk( tr( "Art thou attempting to disturb my privacy?" ) );
		else
			pp_owner->message( tr( "You notice %1 trying to peek into your pack!" ).arg( player->name() ) );
	}



	//	SetTimerSec(player->objectdelay(), Config::instance()->objectDelay()+Config::instance()->snoopdelay());
	player->setObjectDelay( Server::instance()->time() + ( Config::instance()->objectDelay() + Config::instance()->snoopdelay() ) * MY_CLOCKS_PER_SEC );
}