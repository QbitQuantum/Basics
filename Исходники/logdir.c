static FILE *
open_logfile(const char *fn){
	FILE *ret;

	if( (ret = fopen(fn,"wb")) ){
		int fd;

		setlinebuf(ret);
		if((fd = Fileno(ret)) < 0){
			fclose(ret);
			ret = NULL;
		}else if(set_fd_close_on_exec(fd)){
			fclose(ret);
			ret = NULL;
		}
		// We don't necessarily want the performance hit from
		// unbuffered logging...maybe make it an option somehow? FIXME
		/*else if(set_fd_nonblocking(fd)){
			fclose(ret);
			ret = NULL;
		}*/
	}
	return ret;
}