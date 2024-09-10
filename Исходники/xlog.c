PRIVATE void xlog_unlink(xlog_s *xp)
{
	xlog_s *server = xp->xl_use ;

	/*
	 * Step 1: remove from server chain
	 */
	if ( server != XLOG_NULL )
	{
		if ( server->xl_clients == xp )
			if ( NEXT( xp, xl_other_users ) == xp )
				server->xl_clients = XLOG_NULL ;
			else
				server->xl_clients = NEXT( xp, xl_other_users ) ;
		else
			UNLINK( xp, xl_other_users ) ;
	}

	/*
	 * Step 2: If we have users, clear their link to us.
	 */
	if ( xp->xl_clients != NULL )
	{
		xlog_s *xp2 = xp->xl_clients ;

		do
		{
			xp2->xl_use = XLOG_NULL ;
			xp2 = NEXT( xp2, xl_other_users ) ;
		}
		while ( xp2 != xp->xl_clients ) ;
	}
}