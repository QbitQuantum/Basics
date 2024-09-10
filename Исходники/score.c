short makenewscore() {

   short ret = 0;

   scoreentries = 0;
#if ATARIST
	if ((sfdbn = Fcreate(SCOREFILE, 0)) < 0) ret = E_FOPENSCORE;
	else {
		Fwrite(sfdbn, 2L, &scoreentries);
		Fclose(sfdbn);
	}
#else
   while( creat( LOCKFILE) < 0);
   if( (scorefile = fopen( SCOREFILE, "w")) == NULL)
      ret = E_FOPENSCORE;
   else {
      sfdbn = fileno( scorefile);
      write( sfdbn, &scoreentries, 2);
      fclose( scorefile);
   }
   unlink( LOCKFILE);
#endif

   return( (ret == 0) ? E_ENDGAME : ret);
}