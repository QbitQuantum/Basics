void process_input (void) {
	int bufferSize = 1024;

  	short buffer[BUFLEN];
	int l, i, level;
 
	//read a block of audio samples with proper error checking
  	if ((l = read (fd_in, buffer, sizeof (buffer))) == -1) {
      		perror ("Audio read");
      		exit (-1);		/* Or return an error code */
    	}

	//we are using mono 16bit. Stereo needs to be interleaved, more difficult
  	l = l / 2;

	//checking levels stuff
	level = 0;
  	for (i = 0; i < l; i++) {
       		int v = buffer[i];

      		if (v < 0)
			v = -v;		/* abs */

      		if (v > level)
			level = v;
    	}
	
  	level = (level + 1) / 1024;
	
	//save to file
	int index;
	int charBuffIndex = 0;
	char temp[BUFLEN * 2];
	for(index = 0; index < BUFLEN * 2; index += 2){
		//fprintf(fp, "%i\n", buffer[charBuffIndex]);
		short tempshort = buffer[charBuffIndex++];
		//short tempshort = 7192;
		//add the last 8 bits
		temp[index] = tempshort & 0xFF;
		//move the first 8 bits into the last 8 bits spot
		tempshort = tempshort >> 8;
		//save the next value
		temp[index + 1] = tempshort & 0xFF;
	}


	doSend(temp);

	int iindex;
	for(iindex = 0; iindex < BUFLEN; iindex++){
		printf("%i,", buffer[iindex]);
	}
	printf("\n"); 
	//exit(0);
	//end save to file
	

	//linear scale, real world(dBD) is log
  	for (i = 0; i < level; i++)
    		printf ("*");
  	for (i = level; i < 32; i++)
    		printf (".");
  	printf ("\r");
  	fflush (stdout);
}