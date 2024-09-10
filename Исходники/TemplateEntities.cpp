void Templates_RemoveByHammerID( int nHammerID )
{
	for ( int i=g_Templates.Count()-1; i >= 0; i-- )
	{
		if ( g_Templates[i]->m_nHammerID == nHammerID )
		{
			Templates_FreeTemplate( g_Templates[i] );
			g_Templates.Remove( i );
		}
	}
}