//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CObjectTunnelTrigger::TunnelThink()
{
	// Make sure it's not already in the list
	int c = m_Tunneling.Count();
	for ( int i = c - 1; i >= 0; i-- )
	{
		TunnelPlayer *tp = &m_Tunneling[ i ];

		if ( !KeepTunneling( tp ) )
		{
			m_Tunneling.Remove( i );
		}
	}

	SetNextThink( gpGlobals->curtime + TUNNEL_THINK_INTERVAL );
}