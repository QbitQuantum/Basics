int main(int argc,char *argv[]) {

	int c,rcode=0,colnum=0,srcfsize;
	long int numLines=10000, fsize=5, pref_indicator=0;
	char seperator=',';
	char *col_stmt=NULL;
	char *ifname=NULL,*ofname=NULL;
	FILE *ofile=NULL, *ifile=NULL;
	short int prefix_select=0;
	//char buff[MAX_LENGTH];
	char buff[2048];
	int quot_val = 0;

	arg_options argopts = { 0 , 0, 0, 0, 0, 0, 0, 0, 0 };

	while ((c = getopt(argc, argv, "vs:hnaf:o:il:z:c:")) != -1 ) 
		switch(c) {
			case 'v':
				argopts.ver_opt = 1;
			break;
			
			case 's':
				seperator = optarg[0];
			break;

			case 'h':
				Help(0);
			break;

			case 'n':
				argopts.num_opt = 1;
			break;

			case 'a':
				argopts.alph_opt = 1;
			break;

			case 'f':
				ifname = optarg;
				argopts.ifile_opt = 1;
			break;

			case 'o':
				argopts.ofile_opt = 1;
				ofname = optarg;

			break;
		
			case 'i':
				argopts.incl_opt = 1;
			break;

			case 'l':
				argopts.line_opt =1;
				numLines = atoi(optarg);
			break;

			case 'z':
				argopts.size_opt =1;
				fsize = atoi(optarg);
			break;
			
			case 'c':
				col_stmt = optarg;
			break;	

			default:
				Help(1);
			break;
		}

	if (argopts.ifile_opt == 0) {
		fprintf(stderr,"an input file must be specified\n");
		Help(1);
	}

	if ( (argopts.num_opt == 1) && (argopts.alph_opt == 1 ) ) {
		fprintf(stderr,"only one of the arguments should be specified ( -n  \\ -a) \n");
		Help(2);
	}
	else if ( argopts.alph_opt == 1 )
		fsize = fsize * 1024;

	if (argopts.alph_opt == 1 )
		prefix_select = 1;
	else
		prefix_select = 0;

	if (getenv("CSVS_SEPERATOR"))
		strncpy(&seperator,getenv("CSVS_SEPERATOR"),1);

	if (getenv("CSVS_OUTPUT"))
		ofname = getenv("CSVS_OUTPUT");

	if (getenv("CSVS_LINE_NUMBER"))
		numLines = atoi(getenv("CSVS_LINE_NUMBER"));

	if ( (getenv("CSVS_FILE_SIZE")) && (!getenv("CSVS_LINE_NUMBER")) ) 
		fsize = atoi(getenv("CSVS_FILE_SIZE")) * 1024;
	
	if ( getenv("CSVS_COLUMNS_NAME") )
		col_stmt = getenv("CSVS_COLUMNS_NAME");	
	
	//  openning the read file 
	
	if (ifile = fopen(ifname,"r")){
		if ( argopts.ver_opt == 1 )
			printf("the file %s is o.k.\n",ifname);

		argopts.ifile_opt = 1;
	}

	else {
		fprintf(stderr,"the file \"%s\" can not be opened\n",ifname);
		exit(1);
	}

	// 1) chicking if the read file is not empty 
	
	if (ifile) {

		fseek (ifile ,0, SEEK_END);
		srcfsize = ftell(ifile);

		if ( srcfsize == 0 ) {
			fclose(ifile);
			fprintf(stderr,"The Input file is empty !!!, exiting\n");
			exit(4);
		}
	}	
	
	// 2) setting the new file name according to user choice & \
	// creating the new file for writing (with a function)

	if ( argopts.ofile_opt == 0 ) {
	
		ofname = ifname;
		ofname =  basename(ofname);
	}


	if (argopts.alph_opt == 1 ) 
		strcat(ofname,".a");
	else
		strcat(ofname,".1");
	
 	if ( argopts.ver_opt == 1 )
		printf("the first output file name is : %s \n",ofname);

	// going over the read file and making sure each line is CSV competable
	

	fseek (ifile ,0, SEEK_SET);

	while( fgets(buff,2048,ifile) != NULL )  {


                if (strlen(buff) < (colnum+1))
                        break;
	
		if ( col_stmt == NULL ) {
		
			colnum = firstlinetst(buff,argopts.ver_opt,seperator,&quot_val);	
			col_stmt = (char *)calloc(strlen(buff),sizeof(char));
			strcpy(col_stmt,buff);
			continue;
		}

		

	}

	// 5) for each approved line inserting it to the new file while checking predefine limits
	// 6) if the write file as reached a limit start a new file
	// 7) if the read file is done , close all the files
	// 8) 
	


   return rcode;
}