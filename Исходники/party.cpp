void cParty::removeMember( P_PLAYER player, bool update )
{
	removeCanidate( player );
	members_.remove( player );
	player->setParty( 0 );

	// Update the party
	if ( update )
	{
		cUOTxPartyRemoveMember removemember;
		removemember.setSerial( player->serial() );
		for ( P_PLAYER member = members_.first(); member; member = members_.next() )
			removemember.addMember( member->serial() );

		send( &removemember );

		if ( player->socket() )
		{
			if ( player == leader_ )
				player->socket()->clilocMessage( 1005456 );

			cUOTxPartyRemoveMember updateparty;
			updateparty.setSerial( player->serial() );
			player->socket()->send( &updateparty );
		}
	}

	// Check if the party can be disbanded
	if ( player == leader_ || ( members_.count() <= 1 && canidates_.count() == 0 ) )
	{
		if ( player != leader_ && leader_->socket() )
			leader_->socket()->clilocMessage( 1005450 );

		delete this;
	}
}