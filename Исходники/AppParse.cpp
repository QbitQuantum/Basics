bool testUnicode(char *filename) {
	char a,b;
	FILE *test=NULL;

	try {
		test= _wfsopen(T2W(filename),T2W("rb"), _SH_DENYNO);
		if(test==NULL ){
			logger(Error,"Failed to open input file %s to inspect unicode status. Error code %d. Assuming non unicode. Problem with log file access?",filename, errno);
			return false;
		}

		a=getc(test);  //NOT getwc!
		b=getc(test);

		// Empty file produces -1 and -1 (EOF twice)
		if ((a==-1)&(b==-2)) {  //actually 0xFF 0xFE
			//is unicode
			fclose(test);
			test=0;
			DEBUGAPPLPARSE(Informational,"Log file %s is in unicode format.",filename);
			return true;
		} else {
			fclose(test);
			test=0;
			DEBUGAPPLPARSE(Informational,"Log file %s is not unicode format.",filename);
			return false;
		}
	}
	catch(SE_Exception e) {
		logger(Error,"SEH Exception in testUnicode for log file %s. Assuming non unicode log file. Error code %u.",filename,e.getSeNumber());
	}
	catch(...) {
		CreateMiniDump(NULL);
		logger(Error, "Exception when detecting unicode status on log file %s. Dump file written.",filename);
		if (test!=NULL)
		fclose(test);
	}
	return false;

}