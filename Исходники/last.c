void
writelast()
{
    sprintf(buf,"%s.%ld", lastfile, our_pid);
    if ((tmpfp = fopen(buf,"w")) != NULL) {
	if (lasttime < starttime)
	    lasttime = starttime;
	fprintf(tmpfp,"%s\n%ld\n%ld\n%ld\n%ld\n",
		ngname? ngname : nullstr,lasttime,
		lastactsiz,lastnewtime,lastextranum);
	fclose(tmpfp);
	UNLINK(lastfile);
	RENAME(buf,lastfile);
    }
    else {
	printf(cantcreate,buf) FLUSH;
	/*termdown(1);*/
    }
}