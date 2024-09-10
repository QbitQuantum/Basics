int main(int argc, char* argv[]){
	// Declare variables-------------------------------------------------------------
	HashTable Index;				// Inverted index
	InitialiseHashTable(&Index);
	char text[MAXLEN];
	int test = 0;
	
	// 1. Check input parameters--------------------------------------------------------
	if (argc != 3 ){ 				// check number of arguments
		fprintf(stderr,"Error: Incorrect number of input argument\n");
		return -1;
	}else if(!IsFile(argv[1])){		// check if file is valid
		fprintf(stderr,"Error: File %s is invalid\n", argv[1]);
		return -1;
	}else if(!IsDir(argv[2])){		// check if directory is valid
		fprintf(stderr,"Error: Directory %s cannot be found\n", argv[2]);
		return -1;
	}
	
	// 2. Reconstruct Inverted Index-----------------------------------------------------
	printf("Please wait while the query engine is loading. It might take a few minutes... \n");
	if(!ReadFile(&Index, argv[1])){
		CleanUpHash(&Index);
		return -1;
	}
	
	
	// 3. Command Line interface and query -----------------------------------------------
	
	for(int j=0; j<9; j++){
		
		// Create text array for automated testing
		
		switch (j){
			case 0:
				printf("\n3.%d Test invalid input syntax\n",j+1);
				printf("QUERY :> AND dog\n");
				strcpy(text,"AND dog\n");
				break;
			case 1:
				printf("\n3.%d Test invalid input syntax\n", j+1);
				printf("QUERY :> cat OR AND dog\n");
				strcpy(text,"cat OR AND dog\n");
				break;
			case 2:
				printf("\n3.%d Test no result\n", j+1);
				printf("QUERY :> thisisrandom\n");
				strcpy(text,"thisisrandom\n");
				break;
			case 3:
				printf("\n3.%d Test single entry\n", j+1);
				printf("QUERY :> incredible\n");
				strcpy(text,"incredible\n");
				break;
			case 4:
				printf("\n3.%d Test uppercase\n", j+1);
				printf("QUERY :> Incredible\n");
				strcpy(text,"Incredible\n");
				break;
			case 5:
				printf("\n3.%d Test AND\n", j+1);
				printf("QUERY :> Dartmouth AND College AND Computer AND Science\n");
				strcpy(text,"Dartmouth AND College AND Computer AND Science\n");
				break;
			case 6:
				printf("\n3.%d Test space as AND\n", j+1);
				printf("QUERY :> Dartmouth College Computer Science\n");
				strcpy(text,"Dartmouth College Computer Science\n");
				break;
			case 7:
				printf("\n3.%d Test OR\n", j+1);
				printf("QUERY :> Dartmouth OR Computer\n");
				strcpy(text,"Dartmouth OR Computer\n");
				break;
			case 8:
				printf("\n3.%d Test combined\n", j+1);
				printf("QUERY :> Dartmouth College AND Hanlon OR Mathematics AND Computer Science AND Philosophy OR incredibles Pixar\n");
				strcpy(text,"Dartmouth College AND Hanlon OR Mathematics AND Computer Science AND Philosophy OR incredibles Pixar\n");
				break;
		
		}
		// a) declare variables
		int unionflag, flag, size_temp, size_intersect, size_final, count;
		char wordarray[MAXLEN][MAXLEN];
		int temparray[MAXSIZE][2], intersect[MAXSIZE][2], final[MAXSIZE][2];
		
		// b) instantiate variables
		size_temp = size_intersect = size_final = unionflag = flag = 0;
		count = StringToWord(wordarray,text);
		
		// c) query
		for(int i=0; i<count; i++){
			if(i==0 && strcmp(wordarray[i],"AND") && strcmp(wordarray[i],"OR")){ 	// if it's the first word and is not invalid
				NormalizeWord(wordarray[i]);
				size_intersect = FindHash(wordarray[i], intersect, Index);
				continue;
			}else if(i==0){ 	// if it is first word and invalid
				flag = 1; break;
			}else if(unionflag){
				if(strcmp(wordarray[i],"AND") && strcmp(wordarray[i],"OR")){
					NormalizeWord(wordarray[i]);
					size_intersect = FindHash(wordarray[i], intersect, Index);
					unionflag = 0;
					continue;
				}else{
					flag = 1; break;
				}
			}
			
			if (!strcmp(wordarray[i],"AND")){	// if it's AND
				if(CheckOperator(wordarray,i,count)){
					NormalizeWord(wordarray[i+1]);
					size_temp = FindHash(wordarray[i+1], temparray, Index);
					size_intersect = FindIntersection(intersect, size_intersect, temparray, size_temp);
					i++;
					continue;
				}else{
					flag = 1; break;
				}
			}else if(!strcmp(wordarray[i],"OR")){ // if it's OR
				if(CheckOperator(wordarray,i,count)){
					size_final = FindUnion(final, size_final, intersect, size_intersect);
					size_intersect = 0;
					unionflag = 1;
					continue;
				}else{
					flag = 1; break;
				}
			}else{
				NormalizeWord(wordarray[i]);
				size_temp = FindHash(wordarray[i], temparray, Index);
				size_intersect = FindIntersection(intersect, size_intersect, temparray, size_temp);
				continue;
			}
		}