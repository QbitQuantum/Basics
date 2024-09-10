	/* public c'tors */
	compare_fails_exception(const char* msg) {	
		strncpy(mywhat,msg,MAX_ERR_LEN-1);
		strcat(mywhat,"\n");
	}