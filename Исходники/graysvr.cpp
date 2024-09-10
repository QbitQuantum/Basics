bool CMapList::Load(int map, char *args)
{
	if (( map < 0 ) || ( map > 255 ))
	{
		g_Log.EventError("Invalid map #%d couldn't be initialized.\n", map);
		return false;
	}
	else if ( !m_mapsinitalized[map] )	// disable double intialization
	{
		TCHAR * ppCmd[5];	// maxx,maxy,sectorsize,mapnum[like 0 for map0/statics0/staidx0],mapid
		size_t iCount = Str_ParseCmds(args, ppCmd, COUNTOF(ppCmd), ",");

		if ( iCount <= 0 )	// simple MAPX= same as disabling the map
		{
			m_maps[map] = false;
		}
		else
		{
			int	maxx = 0, maxy = 0, sectorsize = 0, realmapnum = 0, mapid = -1;
			if ( ppCmd[0] ) maxx = ATOI(ppCmd[0]);
			if ( ppCmd[1] ) maxy = ATOI(ppCmd[1]);
			if ( ppCmd[2] ) sectorsize = ATOI(ppCmd[2]);
			if ( ppCmd[3] ) realmapnum = ATOI(ppCmd[3]);
			if ( ppCmd[4] ) mapid = ATOI(ppCmd[4]);

										// zero settings of anything except the real map num means
			if ( maxx )					// skipping the argument
			{
				if (( maxx < 8 ) || ( maxx % 8 ))
				{
					g_Log.EventError("MAP%d: X coord must be multiple of 8 (%d is invalid, %d is still effective).\n", map, maxx, m_sizex[map]);
				}
				else m_sizex[map] = maxx;
			}
			if ( maxy )
			{
				if (( maxy < 8 ) || ( maxy % 8 ))
				{
					g_Log.EventError("MAP%d: Y coord must be multiple of 8 (%d is invalid, %d is still effective).\n", map, maxy, m_sizey[map]);
				}
				else m_sizey[map] = maxy;
			}
			if ( sectorsize > 0 )
			{
				if (( sectorsize < 8 ) || ( sectorsize % 8 ))
				{
					g_Log.EventError("MAP%d: Sector size must be multiple of 8 (%d is invalid, %d is still effective).\n", map, sectorsize, m_sectorsize[map]);
				}
				else if (( m_sizex[map]%sectorsize ) || ( m_sizey[map]%sectorsize ))
				{
					g_Log.EventError("MAP%d: Map dimensions [%d,%d] must be multiple of sector size (%d is invalid, %d is still effective).\n", map, m_sizex[map], m_sizey[map], sectorsize, m_sectorsize[map]);
				}
				else m_sectorsize[map] = sectorsize;
			}
			if ( realmapnum >= 0 )
				m_mapnum[map] = realmapnum;
			if ( mapid >= 0 )
				m_mapid[map] = mapid;
			else
				m_mapid[map] = map;
		}
		m_mapsinitalized[map] = true;
	}
	return true;
}