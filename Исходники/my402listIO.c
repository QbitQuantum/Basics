void parseInputToList(FILE* fp,My402List *list)
{
    char buffer[1026];
   // FILE *fpNew = fopen("f1", "r");
    while(fgets(buffer, sizeof(buffer)/sizeof(char), fp) != NULL) {
        
        if (strlen(buffer) > 1024) {
            fprintf(stderr, "Line longer than 1024 characters \n");
            exit(1);
        }
        
        transaction *newObject = createTransaction();
        if (newObject) {
            // parsing code
            const char s[2] = "\t";
            char *token;
            
            // type of transaction
            token = strtok(buffer, s);
	    if((strcmp(token,"+") != 0) && (strcmp(token,"-") != 0))
	    {
		fprintf(stderr, "Malformed file \n");
                exit(1);
	    }	
            strcpy(newObject->type,token);
            
            // timestamp
            token = strtok(NULL, s);
            if (strlen(token) >= 11 || atol(token) > time(0)) {
                fprintf(stderr, "Bad timestamp \n");
                exit(1);
            }
            
            time_t raw_time = atol(token);
            newObject->timeStamp = (unsigned int)atol(token);
            struct tm*  timeinfo = localtime (&raw_time);
            strftime (newObject->timeStampDesc,16,"%a %b %e %Y",timeinfo);
            
            // amount
            token = strtok(NULL, s);
	    long length = atol(token);

            if (length <1 || length >= 10000000) {
                fprintf(stderr, "Length of amount greater than desired range or less than 1 \n");
                exit(1);
            }
	    
	    char *dec = strchr(token,'.');
	    int decPosition = (int)(dec -token);
	    if ((strlen(token) - decPosition) > 3) {
                fprintf(stderr, "Decimal places more than 2 \n");
                exit(1);
            }

            strcpy(newObject->amount,token);
	   
            
            // transaction description
            token = strtok(NULL, s);
	    char *exceedField = strtok(NULL, s);
	    if (exceedField && strlen(exceedField) > 0)
	    {
		fprintf(stderr, "Too many fields \n");
                exit(1);
 	    }

	    token = strtok(token,"\n");
            if (strlen(token) < 1) {
                fprintf(stderr, "Description not empty \n");
                exit(1);
            }
            if (strlen(token) > 24) {
                strncpy(newObject->desc,token,24);
            }else {
                strncpy(newObject->desc,token,strlen(token));
            }
            newObject->desc[strlen(token)] = '\0';


            My402ListAppend(list, newObject);
            
	
        }
    }
}