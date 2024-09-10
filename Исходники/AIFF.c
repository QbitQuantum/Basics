/**

Process the AIFF file.  This method will call processCOMM to handle the COMM section.  
It will mark the position of the sound file so processSSND and getSamplesAIFF can perform correctly. 

**/
File_Data processAIFF(FILE *outfile, FILE* infile){
	int foundComm = 0;
	int foundSSND = 0;
	File_Data data;
	CommonChunk comm;
	SoundDataChunk sdc;
	data.samples = -1;
	data.channels = -1;
	data.sampleRate = -1;
	data.bitDepth = -1;
	data.success = 0;

	char buff[4];


	int i, j;
	for(i = 0; i < 4; i++){
		buff[i] = fgetc(infile);
	}
	flipBytes(buff, 4);
	int y = *((int*)buff);

	for(i = 0; i < 4; i++){
		buff[i] = fgetc(infile);
	}
	if(strncmp(buff, "AIFF", 4) != 0){
		data.success = 0;
		return data;
	}else {
		strncpy(data.format, "AIFF\0", 5);
	}
	while(!foundComm || !foundSSND){
		buff[0] = fgetc(infile);
		if(EOF == buff[0]){
			data.success = 0;
			return data;
		}else if(buff[0] != 'C' && buff[0] != 'S' && buff[0] != 'A'){
			continue;
		}

		for(i = 1; i < 4; i++){
			buff[i] = fgetc(infile);
			if(buff[i] == 'C'){
				ungetc(buff[i], infile);
				continue;
			}
		}
		if(strncmp(buff, "COMM", 4) == 0){
			comm = processComm(infile);
			data.samples = comm.numSampleFrames;
			data.channels = comm.numChannels;
			data.sampleRate = comm.sampleRate;
			data.bitDepth = comm.sampleSize;
			strcpy(data.duration, findDuration(data.sampleRate, data.channels, data.samples, data.duration));
			foundComm = 1;
		}
		if(strncmp(buff, "SSND", 4) == 0){
			/*Marks the position of the SSND chunk so it can be processed later*/
			foundSoundData = fgetpos(infile, &SSNDLocation);
			foundSSND = 1;
		}
		if(strncmp(buff, "COMT", 4) == 0 || strncmp(buff, "ANNO", 4) == 0 ){
			/* Runs through comment chunks */
			int chunkSize;
			char sizeBuff[4];
			for(j = 0; j < 4; j++){
				sizeBuff[j] = fgetc(infile);
			}
			flipBytes(sizeBuff, 4);
			chunkSize = *((int *)sizeBuff);
			int count = 0;
			while(count < chunkSize){
				count++;
				fgetc(infile);
			}

		}
	}
	if(foundSSND && foundComm)
		data.success = 1;
	return data;
}