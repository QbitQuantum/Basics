void cSectorMaps::add( cUObject* object )
{
	// Very powerful statement. It completely
	// annihilates the need to check for
	// nullpointers in our object-map
	if ( !object )
		return;

	if ( isItemSerial( object->serial() ) )
	{
		P_ITEM pItem = dynamic_cast<P_ITEM>( object );
		if ( pItem )
		{
			Coord_cl pos = pItem->pos();

			std::map<unsigned char, cSectorMap*>::const_iterator it = itemmaps.find( pos.map );

			if ( it == itemmaps.end() )
				throw QString( "Couldn't find a map with the id %1." ).arg( pos.map );

			it->second->addItem( ( cUObject * ) pItem );

			Timing::instance()->addDecayItem( pItem );
		}
	}
	else if ( isCharSerial( object->serial() ) )
	{
		// This is a safety check to make sure that
		// stabled pets don't appear on our sectormap
		P_NPC npc = dynamic_cast<P_NPC>( object );

		if ( npc && npc->stablemasterSerial() != INVALID_SERIAL )
		{
			return;
		}

		// The same check for players
		P_PLAYER player = dynamic_cast<P_PLAYER>( object );

		if ( player && !player->socket() && !player->logoutTime() )
		{
			return;
		}

		P_CHAR pChar = dynamic_cast<P_CHAR>( object );
		if ( pChar )
		{
			Coord_cl pos = pChar->pos();

			std::map<unsigned char, cSectorMap*>::const_iterator it = charmaps.find( pos.map );

			if ( it == charmaps.end() )
				throw QString( "Couldn't find a map with the id %1." ).arg( pos.map );

			it->second->addItem( ( cUObject * ) pChar );
		}
	}
}