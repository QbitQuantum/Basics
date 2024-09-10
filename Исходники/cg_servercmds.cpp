/*
================
CG_ParseServerinfo

This is called explicitly when the gamestate is first received,
and whenever the server updates any serverinfo flagged cvars
================
*/
void CG_ParseServerinfo( void ) {
	const char	*info;
	char	*mapname;

	info = CG_ConfigString( CS_SERVERINFO );
	cgs.dmflags = atoi( Info_ValueForKey( info, "dmflags" ) );
	cgs.teamflags = atoi( Info_ValueForKey( info, "teamflags" ) );
	cgs.timelimit = atoi( Info_ValueForKey( info, "timelimit" ) );
	cgs.maxclients = 1;
	mapname = Info_ValueForKey( info, "mapname" );
	Com_sprintf( cgs.mapname, sizeof( cgs.mapname ), "maps/%s.bsp", mapname );
	char *p = strrchr(mapname,'/');
	strcpy( cgs.stripLevelName[0], p?p+1:mapname );
	strupr( cgs.stripLevelName[0] );
	for (int i=1; i<STRIPED_LEVELNAME_VARIATIONS; i++)	// clear retry-array
	{
		cgs.stripLevelName[i][0]='\0';
	}
	// be careful with the []-numbers here. Currently I use 0,1,2 for replacements or substitution, and [3] for "INGAME"
	//	I know, if I'd known there was going to be this much messing about I'd have subroutinised it all and done it
	//	neater, but it kinda evolved...   Feel free to bug me if you want to add to it... ?  -Ste.
	//

//FIXME: a better way to handle sound-matched strings from other levels (currently uses levelname+sound as key)

	// additional String files needed for some levels...
	//
	// JKA...
	if (!stricmp(cgs.stripLevelName[0],"YAVIN1B"))
	{
		strcpy( cgs.stripLevelName[1], "YAVIN1");
	}

/*	// JK2...
	if (!stricmp(cgs.stripLevelName[0],"KEJIM_BASE") ||
		!stricmp(cgs.stripLevelName[0],"KEJIM_POST")
		)
	{
		strcpy( cgs.stripLevelName[1], "ARTUS_MINE" );
	}
	if (!stricmp(cgs.stripLevelName[0],"DOOM_DETENTION") ||
		!stricmp(cgs.stripLevelName[0],"DOOM_SHIELDS")
		)
	{
		strcpy( cgs.stripLevelName[1], "DOOM_COMM" );
	}
	if (!stricmp(cgs.stripLevelName[0],"DOOM_COMM"))
	{
		strcpy( cgs.stripLevelName[1], "CAIRN_BAY" );
	}
	if (!stricmp(cgs.stripLevelName[0],"NS_STARPAD"))
	{
		strcpy( cgs.stripLevelName[1], "ARTUS_TOPSIDE" );	// for dream sequence...

		strcpy( cgs.stripLevelName[2], "BESPIN_UNDERCITY" );	// for dream sequence...
	}
	if (!stricmp(cgs.stripLevelName[0],"BESPIN_PLATFORM"))
	{
		strcpy( cgs.stripLevelName[1], "BESPIN_UNDERCITY" );
	}
*/
}