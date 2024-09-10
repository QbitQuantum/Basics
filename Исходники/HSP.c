unsigned int HSPParseFASTAToPacked(const char* FASTAFileName, const char* annotationFileName, const char* packedDNAFileName, const char* ambiguityFileName, const unsigned int FASTARandomSeed, const int maskLowerCase) {

	FILE *FASTAFile, *annotationFile, *packedDNAFile, *ambiguityFile;

	NewAnnotation *chrAnnotation;
	int chrAnnAllocated = 256;
	int blockAllocated = 256;

	char c;
	int chrNum, blockNum;
	unsigned int i, l;
	int nCount;
	unsigned int chrLen, usefulCharNum, numCharInBuffer, totalNumChar;
	unsigned char charMap[255];
	char *chrSeq, *p;
	unsigned int chrAllocated = 65536;
	unsigned char buffer[PACKED_BUFFER_SIZE];
	unsigned char packedBuffer[PACKED_BUFFER_SIZE / 4];
	chrLen = usefulCharNum = numCharInBuffer = totalNumChar = chrNum = blockNum = i = l = nCount = 0;
	FASTAFile = (FILE*)fopen64(FASTAFileName, "r");
	if (FASTAFile == NULL) {
		fprintf(stderr, "ParseFASTToPacked() : Cannot open FASTAFileName!\n");
		exit(1);
	}

	annotationFile = (FILE*)fopen64(annotationFileName, "w");
	if (annotationFile == NULL) {
		fprintf(stderr, "ParseFASTToPacked() : Cannot open annotationFileName!\n");
		exit(1);
	}

	packedDNAFile = (FILE*)fopen64(packedDNAFileName, "wb");
	if (packedDNAFile == NULL) {
		fprintf(stderr, "ParseFASTToPacked() : Cannot open packedDNAFileName!\n");
		exit(1);
	}

	ambiguityFile = (FILE*)fopen64(ambiguityFileName, "w");
	if (ambiguityFile == NULL) {
		fprintf(stderr, "ParseFASTToPacked() : Cannot open ambiguityFileName!\n");
		exit(1);
	}

	HSPFillCharMap(charMap);

	c = (char)getc(FASTAFile);
	if (c != '>') {
		fprintf(stderr, "ParseFASTToPacked() : FASTA file does not begin with '>'!\n");
		exit(1);
	}
	chrAnnotation = (NewAnnotation *)malloc(sizeof(NewAnnotation)*chrAnnAllocated);
	chrSeq = (char*)malloc(sizeof(char)*chrAllocated);
	chrNum = blockNum = usefulCharNum = numCharInBuffer = 0;
	while(!feof(FASTAFile)){
		if (feof(FASTAFile)) break;
		if (chrNum == chrAnnAllocated){
			chrAnnAllocated <<= 1;
			chrAnnotation = (NewAnnotation *)realloc(chrAnnotation, sizeof(NewAnnotation)*chrAnnAllocated);
//			printf("%d\n", chrNum);
		}

		l=0;
		c = (char)getc(FASTAFile);
		while(!feof(FASTAFile) && c!='\t' && c!=' ' && c!='\n' && l<MAX_SEQ_NAME_LENGTH){
			chrAnnotation[chrNum].chrName[l]=c;
			l++;
			c=(char)getc(FASTAFile);
		}
		chrAnnotation[chrNum].chrName[l]='\0';
		while(c!='\n'){
			c=(char)getc(FASTAFile);
		}
		chrLen = 0;
		while(c!='>' && !feof(FASTAFile)){
			if (c!='\n'){
				if (c>='a' && c<='z'){
					c+='A'-'a';
				}
				if (chrLen >= chrAllocated){
					chrAllocated <<= 1;
					chrSeq = (char*)realloc(chrSeq, sizeof(char)*chrAllocated);
				}
				*(chrSeq+chrLen) = c;
				chrLen += 1;
			}
			c=(char)getc(FASTAFile);
		}
		if (chrLen < 75) continue;
		//*
		i=0;
		p=chrSeq;
		while (ambiguityCount[charMap[(int)*p]] == 1 && i++ != chrLen) p++;
		if (i == chrLen) {
			blockNum = 1;
			chrAnnotation[chrNum].blockInChr = (ChrBlock *)malloc(sizeof(ChrBlock)*blockNum);
			chrAnnotation[chrNum].chrStart = usefulCharNum;
			chrAnnotation[chrNum].blockNum = blockNum;
			chrAnnotation[chrNum].blockInChr[0].blockStart = usefulCharNum;
			chrAnnotation[chrNum].blockInChr[0].ori = 0;
			usefulCharNum += chrLen;
			chrAnnotation[chrNum].chrEnd = usefulCharNum-1;
			chrAnnotation[chrNum].blockInChr[0].blockEnd = usefulCharNum-1;
			i=0;
			while(i<chrLen){
				if (numCharInBuffer >= PACKED_BUFFER_SIZE) {
					ConvertTextToBytePacked(buffer, packedBuffer, charMap, 4, PACKED_BUFFER_SIZE);
					fwrite(packedBuffer, 1, PACKED_BUFFER_SIZE / 4, packedDNAFile);
					numCharInBuffer = 0;
				}
				buffer[numCharInBuffer++] = chrSeq[i++];
			}
		} else {
			i=0;
			p = chrSeq;
			while (ambiguityCount[charMap[(int)*p]]!=1 && ++i!=chrLen) p++;
			if (i<10) { i = 0; p = chrSeq;}
			blockNum = 1;
			chrAnnotation[chrNum].blockInChr = (ChrBlock *)malloc(sizeof(ChrBlock)*blockAllocated);
			chrAnnotation[chrNum].chrStart = usefulCharNum;
			chrAnnotation[chrNum].blockInChr[blockNum-1].ori = i;
			chrAnnotation[chrNum].blockInChr[blockNum-1].blockStart = usefulCharNum;
			int len=0;
			while (i<chrLen) {
				if(ambiguityCount[charMap[(int)*p]] == 1){
					if (numCharInBuffer >= PACKED_BUFFER_SIZE) {
						ConvertTextToBytePacked(buffer, packedBuffer, charMap, 4, PACKED_BUFFER_SIZE);
						fwrite(packedBuffer, 1, PACKED_BUFFER_SIZE / 4, packedDNAFile);
						numCharInBuffer = 0;
					}
					buffer[numCharInBuffer++] = *p++;
					i++;
					usefulCharNum++;
					len++;
				}else{
					nCount = 0;
					while((ambiguityCount[charMap[(int)*p]]!=1) && i<chrLen){
						nCount++;
						i++;
						p++;
					}
					if (nCount<10) {
						do {
							if (numCharInBuffer >= PACKED_BUFFER_SIZE) {
								ConvertTextToBytePacked(buffer, packedBuffer, charMap, 4, PACKED_BUFFER_SIZE);
								fwrite(packedBuffer, 1, PACKED_BUFFER_SIZE / 4, packedDNAFile);
								numCharInBuffer = 0;
							}
							buffer[numCharInBuffer++] = 'G';
							usefulCharNum++;
							len++;
						} while(--nCount>0);
					} else {
						if (i<chrLen) {
							chrAnnotation[chrNum].blockInChr[blockNum-1].blockEnd = usefulCharNum -1;
							chrAnnotation[chrNum].blockInChr[blockNum-1].ori = i-nCount-len;
							if (blockNum == blockAllocated){
								blockAllocated <<= 1;
								chrAnnotation[chrNum].blockInChr = (ChrBlock *)realloc(chrAnnotation[chrNum].blockInChr, sizeof(ChrBlock)*blockAllocated);
							}
							blockNum++;
							len=0;
							chrAnnotation[chrNum].blockInChr[blockNum-1].blockStart = usefulCharNum;
						} else {
							i-=nCount;
							break;
						}
					}
				}
			}
			chrAnnotation[chrNum].blockInChr[blockNum-1].blockEnd = usefulCharNum-1;
			chrAnnotation[chrNum].blockInChr[blockNum-1].ori = i-len;
			chrAnnotation[chrNum].blockNum = blockNum;
			chrAnnotation[chrNum].chrEnd = usefulCharNum-1;
		}
//*/
		chrNum++;
		totalNumChar += chrLen;
	}
	if (numCharInBuffer > 0) {
		ConvertTextToBytePacked(buffer, packedBuffer, charMap, 4, numCharInBuffer);
		fwrite(packedBuffer, 1, (numCharInBuffer + 3) / 4, packedDNAFile);
		numCharInBuffer = 0;
	}
	if (totalNumChar % 4 == 0) {
		c = 0;
		fwrite(&c, 1, 1, packedDNAFile);
	}
	c = (char)(totalNumChar % 4);
	fwrite(&c, 1, 1, packedDNAFile);
	fclose(packedDNAFile);
	fprintf(annotationFile, "%u\t%d\t%d\n", totalNumChar, chrNum, FASTARandomSeed);
	int j=0;
	int total = 0;
	for (i=0;i<chrNum;i++) {
		fprintf(annotationFile, "%d\t%s\n", (int)strlen(chrAnnotation[i].chrName), chrAnnotation[i].chrName);
		total += chrAnnotation[i].blockNum;
	}
	fprintf(annotationFile, "%d\n", total);
//	fprintf(stderr, "total block, %d, %d, %d\n",i,chrNum, total);
	for(i=0;i<chrNum;i++){
		for(j=0;j<chrAnnotation[i].blockNum;j++){
			fprintf(annotationFile,"%d\t%u\t%u\t%u\n",i, chrAnnotation[i].blockInChr[j].blockStart, chrAnnotation[i].blockInChr[j].blockEnd, chrAnnotation[i].blockInChr[j].ori);
		}
		free(chrAnnotation[i].blockInChr);
	}
	free(chrAnnotation);
	fclose(annotationFile);
	return chrNum;
}