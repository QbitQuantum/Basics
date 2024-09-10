/*!
	Sends multis which came in range and handles collisions with them.
*/
void handleMultis( P_CHAR pChar, const Coord& oldpos )
{
	P_PLAYER player = dynamic_cast<P_PLAYER>( pChar );

	MapMultisIterator multis = MapObjects::instance()->listMultisInCircle( pChar->pos(), BUILDRANGE );
	for ( P_MULTI multi = multis.first(); multi; multi = multis.next() )
	{
		// TODO: handle multi collisions here.

		// If we are a connected player then send new multis
		if ( player && player->socket() )
		{
			UI32 oldDist = oldpos.distance( multi->pos() );
			if ( oldDist >= BUILDRANGE )
			{
				// was out of range before and now is in range
				multi->update( player->socket() );
			}
		}
	}
}