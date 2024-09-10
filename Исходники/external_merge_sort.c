copyfiles() {
	writefile(TMPFILE);
	int page_number1 = -1;
	int page_number2 = -1;

	int *buf1, *buf2;

	int fd_inpfile, fd_finalfile;

	if ((fd_inpfile=PF_OpenFile(TMPFILE))<0){
		PF_PrintError("Error in opening file");
		exit(1);
	}

	if ((fd_finalfile=PF_OpenFile(FILE))<0){
		PF_PrintError("Error in opening file");
		exit(1);
	}

	//transferring contents of finalfile to tmpfile
	int i, error;
	for(i = 0 ; i < B_R ; i++) {
		// get the page page_number of each file
		if((error=PF_GetNextPage(fd_finalfile,&page_number1,&buf1))!= PFE_OK) {
			PF_PrintError("Error");
			exit(1);
		}
		if((error=PF_GetNextPage(fd_inpfile,&page_number2,&buf2))!= PFE_OK) {
			PF_PrintError("Error");
			exit(1);
		}

		*((int *)buf2) = *((int *)buf1);
		//printf("%d ", *((int *)buf2));

		if ((error=PF_UnfixPage(fd_finalfile,page_number1,TRUE))!= PFE_OK){
			PF_PrintError("unfix buffer\n");
			exit(1);
		}

		if ((error=PF_UnfixPage(fd_inpfile,page_number2,TRUE))!= PFE_OK){
			PF_PrintError("unfix buffer\n");
			exit(1);
		}
	}
	if ((error=PF_CloseFile(fd_inpfile))!= PFE_OK){
		PF_PrintError("Error in closing input file\n");
		exit(1);
	}

	if ((error=PF_CloseFile(fd_finalfile))!= PFE_OK){
		PF_PrintError("Error in closing temporary file\n");
		exit(1);
	}
}