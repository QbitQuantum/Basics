int main(int argc, char **argv)
{
	char dumpTableFile[] = "table.txt" ;	  
	char inputFile[] = "../test/data/test_input" ;
	char patternFile[] = "../test/pattern/space_pattern" ;
	PFAC_handle_t handle ;
	PFAC_status_t PFAC_status ;
	int input_size ;    
	char *h_inputString = NULL ;
	int  *h_matched_result = NULL ;
	
	char *h_inputString_buf = NULL;

	// step 1: create PFAC handle 
	PFAC_status = PFAC_create( &handle ) ;
	assert( PFAC_STATUS_SUCCESS == PFAC_status );

	// step 2: read patterns and dump transition table
	PFAC_status = PFAC_readPatternFromFile( handle, patternFile) ;
	if ( PFAC_STATUS_SUCCESS != PFAC_status ){
		printf("Error: fails to read pattern from file, %s\n", PFAC_getErrorString(PFAC_status) );
		exit(1) ;
	}

	// dump transition table 
	FILE *table_fp = fopen( dumpTableFile, "w") ;
	assert( NULL != table_fp ) ;
	PFAC_status = PFAC_dumpTransitionTable( handle, table_fp );
	fclose( table_fp ) ;
	if ( PFAC_STATUS_SUCCESS != PFAC_status ){
		printf("Error: fails to dump transition table, %s\n", PFAC_getErrorString(PFAC_status) );
		exit(1) ;	
	}

	if (argc <= 1){
		printf("no input arguments, using default value\n"); 	

		//step 3: prepare input stream
		FILE* fpin = fopen( inputFile, "rb");
		assert ( NULL != fpin ) ;

		// obtain file size
		fseek (fpin , 0 , SEEK_END);
		input_size = ftell (fpin)-1;
		rewind (fpin);  

		printf("input_size is %d\n", input_size);
		// allocate memory to contain the whole file
		h_inputString = (char *) malloc (sizeof(char)*input_size);
		assert( NULL != h_inputString );

		h_matched_result = (int *) malloc (sizeof(int)*input_size);
		assert( NULL != h_matched_result );
		memset( h_matched_result, 0, sizeof(int)*input_size ) ;

		// copy the file into the buffer
		input_size = fread (h_inputString, 1, input_size, fpin);
		fclose(fpin);    
	}
	else{
		// step 3: prepare input string
		processCommandOption(argc, argv, &h_inputString);		

		input_size = strlen(h_inputString);	

		h_matched_result = (int *) malloc (sizeof(int)*input_size);	
				
		memset (h_matched_result, 0, sizeof(int)*input_size);	
	}

	// step 4: run PFAC on GPU           
	PFAC_status = PFAC_matchFromHost( handle, h_inputString, input_size, h_matched_result ) ;
	if ( PFAC_STATUS_SUCCESS != PFAC_status ){
		printf("Error: fails to PFAC_matchFromHost, %s\n", PFAC_getErrorString(PFAC_status) );
		exit(1) ;	
	}     

	// step 5: output matched result
	// parse in serial, GPU version should be considered
	std::vector<int> positionQ;
	int keylen, i;
	for (int i = 0; i < input_size; i++) {
		if (h_matched_result[i] != 0)  {
			positionQ.push_back(i+1);
		}
		else if (i == 0) {
			positionQ.push_back(i);
		}
	}
	
	for (i = 0; i < positionQ.size(); i++){
		keylen = positionQ[i+1]-positionQ[i];

		// if keylen < 0, this means this is the last element
		// in h_inputString array,
		if (keylen == 1){
			continue;
		} else if (keylen < 0){
			keylen = input_size - positionQ[i];

			if (keylen == 0)
				break;
		}

		if (i != positionQ.size()-1)
			printf("%.*s\t%d\n", keylen, &h_inputString[positionQ[i]], 1);

	}

	// parse in parallel
	

	PFAC_status = PFAC_destroy( handle ) ;
	assert( PFAC_STATUS_SUCCESS == PFAC_status );
	
	if (argc <= 1)
		free(h_inputString);	

	free(h_matched_result); 

	return 0;
}