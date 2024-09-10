static void RemoveDuplicateEntries( CUtlVector< QuickJoinPanel::QuickInfo > &arr )
{
	//
	// Assumes list sorted by name "stricmp"
	//
	const char *szLastName = "";

	for ( int k = 0; k < arr.Count(); ++ k )
	{
		QuickJoinPanel::QuickInfo &fi = arr[k];
		if ( !stricmp( fi.m_szName, szLastName ) )
		{
			// Same name entry, must be removed
			arr.Remove( k -- );
		}
		else
		{
			// Next name, remember for next item
			szLastName = fi.m_szName;
		}
	}
}