int cds_openDataStore(char *database)
{

	if(cdsInfo.state != CDS_CLOSED) 
	{
		LOG_ERROR("CDS already open. \n");
		return CDS_ALREADYOPEN;
	}

	//adding .sch extension
	char *temp=(char *)malloc(sizeof(char)*(strlen(database)+5));
	strcpy(temp,database);
	strcat(temp,".sch");
	
	cdsInfo.database=(char*)malloc(sizeof(char)*(strlen(database)+1));
	strcpy(cdsInfo.database,database);
	FILE *scf;//schema file

	scf=fopen(temp,"rb");

	if(scf==NULL)
	   return OPENCDS_FAIL;

	cdsInfo.freelist=(struct stack *)malloc(sizeof(struct stack));

	//reading .sch file line by line and storing it in buffer
	char *line = (char *)malloc(sizeof(char)*80);
	int i=0;

	FILE *pndx,*sndx,*fp;//pointers to hold .ndx files


	//this loop parses .sch file and opens all ndx and dat files and also populates cdsInfo structure
	while( fgets(line,80,scf) != NULL )
    {
		char *temp=strTok(line,":"); //Colname
		char *size=strTok(NULL,":"); //size of the field
		char *datatype=strTok(NULL,":"); //string
		char *last=strTok(NULL,":");

		if(temp!=NULL && size!=NULL && datatype!=NULL && last==NULL)
		{
			cdsInfo.fileregister[i].colname=(char*)malloc(sizeof(char)*strlen(temp));
			strcpy(cdsInfo.fileregister[i].colname,temp);
			strcat(cdsInfo.fileregister[i].colname,"\0");
			cdsInfo.fileregister[i].type = TYPE_STRING;
			cdsInfo.fileregister[i].length=atoi(size);

			char *fieldname = convert_to_filename(database,temp,".dat");
			
			fp=fopen(fieldname,"rb+");
			if(fp==NULL) 
			{
				LOG_ERROR(".dat file not getting created \n");
				return OPENCDS_FAIL;
				
			}
			cdsInfo.fileregister[i].fptr=fp;

			if(i==0)
			{ 
                  char *indexfilename=convert_to_filename(database,temp,".ndx");    	
			      pndx=fopen(indexfilename,"rb");
			      if(pndx==NULL)
				  {
					LOG_ERROR("Cannot open primary .ndx file.\n");
					return OPENCDS_FAIL;
				  }
			}
			if(i==1)
			{
			     char *indexfilename=convert_to_filename(database,temp,".ndx");    			
			     sndx=fopen(indexfilename,"rb");
			     if(sndx==NULL)
				 {
					LOG_ERROR("Cannot open secondary .ndx file.\n");
					return OPENCDS_FAIL;
				 }
			}
		}
		i++;
	}
	cdsInfo.numCols=i;
	//Populating freelist variable of cdsInfo and loading it 
	cdsInfo.freelist=(struct stack *)malloc(sizeof(struct stack));
	stackInit(cdsInfo.freelist);
	LOG_INFO("Initialized free list\n");


	if(stackLoadFromFile(pndx, cdsInfo.freelist)==STACK_FAIL)
		{
		LOG_ERROR("Didn't load stack from primary .ndx file\n");
		return OPENCDS_FAIL;
		}
	LOG_INFO("Loaded stack with freelist from primary .ndx file \n");


	cdsInfo.primaryNdx = bstLoadFromFile(pndx);
	LOG_INFO("\nLoaded BST from primary .ndx file\n");

	cdsInfo.secondaryNdx=(struct hashTable*)malloc(sizeof(struct hashTable));
	

	hashInit(cdsInfo.secondaryNdx,0);//Initializing hashtable
	if(hashLoadFromFile(sndx,cdsInfo.secondaryNdx)==HASH_FAIL)
	{
		LOG_ERROR("Didn't load hash table from secondary .ndx file\n");
		return OPENCDS_FAIL;//hashLoad Failed
	}
	LOG_INFO("\nLoaded Hash Table from secondary .ndx file\n");	

	//closing ndx files     
	fclose(pndx);
	fclose(sndx);   

	//closing schema file
	fclose(scf);      
	LOG_INFO("CDS open!");
	cdsInfo.state = CDS_OPEN_RW; // else set state to open
	for(i=0;i<cdsInfo.numCols;i++)
		printf("%s\n",cdsInfo.fileregister[i].colname);
	free(temp);
	return OPENCDS_SUCCESS;
}