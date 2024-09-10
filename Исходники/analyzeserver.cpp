int main(int argc, char *argv[]) {
	int c;
	int tflag = 0;
   	int fflag = 0;
   	int rflag = 0;
   	int cflag = 0;
   	char *ffile;

   	while ((c = getopt (argc, argv, "ctrf:")) != EOF) {
	switch (c) {
		case 't':
		 	tflag++;
		 	break;
		case 'r':
			rflag++;
			break;
		case 'f':
			ffile = optarg;
			fflag++;
			break;
		case 'c':
			cflag++;
			break;
      }
   	}

   	if (tflag) {
		int i;
		struct timeval tvBegin, tvEnd, tvDiff;
		gettimeofday(&tvBegin, NULL);
		for (i = 0; i < 100; i++) {
			system("./dsh -s cccwork2.wpi.edu -p 4444 -c \"test\"");
		}
		//system("./dsh -s cccwork2.wpi.edu -c \"close\"");
		gettimeofday(&tvEnd, NULL);
		timeval_subtract(&tvDiff, &tvEnd, &tvBegin);

		FILE * pFile;
		pFile = fopen ("setupData.txt","a");
		if (pFile!=NULL)
		{
			fprintf(pFile, "%ld.%06ld\n", tvDiff.tv_sec, tvDiff.tv_usec);
			fclose (pFile);
		}
	    printf("%ld.%06ld\n", tvDiff.tv_sec, tvDiff.tv_usec);
	}
	else if (rflag) {
		int i;
		struct timeval tvBegin, tvEnd, tvDiff;
		FILE * pFile;
		pFile = fopen ("thruData.txt","a");
		for (i = 0; i < 100; i++) {
			gettimeofday(&tvBegin, NULL);
			system("./dsh -s cccwork2.wpi.edu -p 4444 -c \"cat testdata.dat\"");
			gettimeofday(&tvEnd, NULL);
			timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
			fprintf(pFile, "%ld.%06ld\n", tvDiff.tv_sec, tvDiff.tv_usec);
		}
		//system("./dsh -s cccwork2.wpi.edu -c \"close\"");
		fclose (pFile);

	   	//printf("%ld.%06ld\n", tvDiff.tv_sec, tvDiff.tv_usec);
	}
	else if (fflag) {
		char *filename, *pfilename;
		int setup = 0;
		fstream inStream;
		printf("here is %s\n", ffile);
		if (strcmp(ffile, "setup") == 0) {
			filename = "setupData.txt";
			pfilename = "fsetupData.txt";
			setup++;
		}
		else {
			filename = "thruData.txt";
			pfilename = "fthruData.txt";
		}

		inStream.open(filename, ios :: in);
		if(inStream.fail())
		{
			//return false;
			cout << "couldn't open\n";
			return 0;
		}

		double inNum;
		
		FILE *pFile;
		pFile = fopen(pfilename, "a");
		if ( pFile != NULL)
		{
			double number;
			char numtxt[80];
			printf("here");
			int i;
			for (i = 0; i < 100; i++)
			{
				inStream >> inNum;
				if (setup) inNum = inNum/100;
				else inNum = inNum*100;
				sprintf(numtxt,"%.8f",inNum);
				puts(numtxt);
				fputs ( numtxt, pFile ); /* write the line */
			}
			fclose(pFile);
		}
		inStream.close();
	}