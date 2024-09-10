int main(int nargs,char *argv[])
{
	FILE *fp;
	FILE *outPut;
	struct stat fileStat;
	struct stat fileStat1;
	if(nargs != 5)
	{
		printf("ERROR:Not enough parameters. you dun goofed bro!!!!\n");
		exit(1);
	}
	else
	{	
		if(strcmp(argv[1],argv[4]) == 0)
		{
		 printf("ERROR:Can not output to input file\n");
		 exit(1);
		}
		//num of print to console
     int numPrint;
	  //num of process to fork
		 int numProc;
		if(sscanf(argv[2],"%i",&numPrint) != 1 || sscanf(argv[2],"%i",&numPrint) != 1)
		{
				printf("ERROR: parameter 2 and 3 have to be integers!\n");
					exit(1);
		}
    numPrint = atoi(argv[2]);
    numProc = atoi(argv[3]);

    if(stat(argv[1],&fileStat) < 0)
		{
			printf("ERROR:FILE OR DIRECTORY NOT EXIST\n");    
        exit(1);
		}
		if(stat(argv[4],&fileStat1) == 0)
		{
			printf("ERROR:OUTPUT FILE EXIST AND WILL BE OVER WRITTEN\n");    
        exit(1);
		}
		else
		{
			char *ftp = argv[4];
    	outPut = fopen(ftp,"w+"); 
		}

    

    if(outPut == NULL)
    {
     printf("ERROR: couldnt open file for writing\n");
     exit(1);

    }
//if command line read in a file or read in a directory
			if (S_ISREG(fileStat.st_mode) && (fileStat.st_mode & S_IRUSR))
			{
				
				       //get file size
				
          unsigned int fileSize = fileStat.st_size;
          int fd = open(argv[1],O_RDONLY);
					char *file = NULL;
					printf("FileSize: %d\n", fileSize);
				
					int i;
          fp = fopen(argv[1], "r");
						 if(fp == NULL)
					   {
						  printf("ERROR: Couldnt open file might not exist!!!!!\n");
						  exit(1);
					   }
						//mmap the file
					 	file = splitFile(fp,fileSize,numProc,fd);
						int length = fileSize/numProc;
						int j;
						//usable stuff
						int startingIndex[numProc];
						int endingIndex[numProc];
						int tempPosition = 0;

						//moving starting and ending points
						for(i = 0; i < numProc; i++)
						{
							startingIndex[i] = i * length;
							endingIndex[i] = (i * length) + length;
						}

						for(i = 1; i < numProc; i++)
						{
								while(file[startingIndex[i]] != ' ' && file[startingIndex[i]] != '\t' && file[startingIndex[i]] != '\n')
								{
									
									startingIndex[i]++;
									endingIndex[i-1]++;
								}
						}

						for(i = 0; i < numProc; i++)
						{
							printf("block number:%d\n",i);
								//call child stuff 
							for(j = startingIndex[i]; j < endingIndex[i]; j++)
							{
								//filter
								char tempAry[500];
								tempPosition = 0; 
								//cut out the white space caused by having to move the starting and ending indexs
								//printf("file[startingIndex[i]]: %c\n",file[startingIndex[i]]);
								while(file[j] != ' ' && file[j] != '\t' && file[j] != '\n' && j < endingIndex[i])
								{
											tempAry[tempPosition] = file[j];
											tempPosition++;
											j++;
												
								}
								tempAry[tempPosition] = '\0';
								
								if(strlen(tempAry) > 0)	
								{
									if(wordfilter(tempAry) == TRUE)
									{
										printf("%s ",tempAry);
								  }	
									
								}	
										
							}
							printf("\n");			
						}
					
				   readFILE(fp);
	         sortLinkedList();   			
		       printList(numPrint,outPut);
           fclose(fp);
					 freeAll();
			}
			else if (S_ISDIR(fileStat.st_mode) && (fileStat.st_mode & S_IRUSR))
			{
			//printf("This is a directory and you can read noice\n");
           searchdir(argv[1],0);
					 sortLinkedList();
					 printList(numPrint,outPut);
					 freeAll();
   		 }
			else
			{
				printf("ERROR:your input is either not a file, not a directory,or the input could not be read please check permissions on file and re-run if you believe a error has occured"); 
			}
	}
 fclose(outPut);
    
return 0;
}