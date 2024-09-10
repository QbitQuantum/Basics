void servlog(PCStr(fmt),...){
	FILE *lfp;
	VARGS(8,fmt);

	lfp = fopen("c:/tmp/svlog","a");
	if( lfp == NULL ){
		return;
	}
	fprintf(stderr,"[%d] ",getpid());
	fprintf(stderr,fmt,VA8);
	fprintf(lfp,"[%d][%d] ",getpid(),getthreadid());
	fprintf(lfp,fmt,VA8);
	fflush(lfp);
	fclose(lfp);
}