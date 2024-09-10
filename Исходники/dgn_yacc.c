void
init_dungeon()
{
	if(++n_dgns > MAXDUNGEON) {
	    (void) fprintf(stderr, "FATAL - Too many dungeons (limit: %d).\n",
		    MAXDUNGEON);
	    (void) fprintf(stderr, "To increase the limit edit MAXDUNGEON in global.h\n");
	    exit(EXIT_FAILURE);
	}

	in_dungeon = 1;
	tmpdungeon[n_dgns].lev.base = 0;
	tmpdungeon[n_dgns].lev.rand = 0;
	tmpdungeon[n_dgns].chance = 100;
	Strcpy(tmpdungeon[n_dgns].name, "");
	Strcpy(tmpdungeon[n_dgns].protoname, "");
	tmpdungeon[n_dgns].flags = 0;
	tmpdungeon[n_dgns].levels = 0;
	tmpdungeon[n_dgns].branches = 0;
}