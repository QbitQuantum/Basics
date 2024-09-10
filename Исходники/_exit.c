void
_finish(int status, char *term)
{
	char *cp;

	if(_finishing)
		exits(exitstatus);
	_finishing = 1;
	if(status){
		cp = _ultoa(exitstatus, status & 0xFF);
		*cp = 0;
	}else if(term){
		strncpy(exitstatus, term, ERRMAX);
		exitstatus[ERRMAX-1] = '\0';
	}
	if(_sessleader)
		kill(0, SIGTERM);
	exits(exitstatus);
}