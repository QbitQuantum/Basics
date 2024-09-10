static void printFile(char *fileNam)
{
	int fi, fo;
#define NBUFF 256
	char buff[NBUFF];
	long len;
	
	fileNam[0] = 'd';			/* force data file */

	if ( (fi=Fopen(fileNam, FO_READ)) >= 0 ) {
		if ( (fo=Fcreate(prDevice, 0)) < 0)
			fo=Fopen(prDevice, FO_WRITE);
		/* Fopen may return < 0 for devices like PRN: ! */
		if ( fo > -31) {
	
			while ( (len=Fread(fi, NBUFF, buff)) > 0)
				Fwrite(fo, len, buff);
	
			Fclose(fo);
		} else {
	        uiPrintf(uiH, uiPrERR, "cannot open device|>%s<", prDevice);
		}
		Fclose(fi);
	} else {
        uiPrintf(uiH, uiPrERR, "cannot open dFile");
	}

	Fdelete(fileNam);
	fileNam[0] = 'c';			/* force control file */
	Fdelete(fileNam);
}	