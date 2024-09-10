////////////////////////////////////////////////////////////////
/// This is a general function that returns the value according to \c exp
///
/// \c exp mimics the xPath expression.
/// Its format is //el1/../eln[@attr]
/// which will return the \c attr value of \c eln, 
/// where \c eln is the n-th child of \c el1
///
/// Example: //variable/EnergyPlus[@name] will return the name attributes of EnergyPlus
/// which is equivalent to //EnergyPlus[@name]
///
///\param fileName the xml file name.  
///\param exp the xPath expression.
///\param myVals string to store the found values, semicolon separated.
///\param mynumVals number of values found.
///\param myStrLen length of the string that is passed.
////////////////////////////////////////////////////////////////
int 
getxmlvalues(char* const fileName, 
             char* const exp, 
             char* const myVals, 
             int*  const myNumVals,
             int   const myStrLen){

  char* temp;
  int i,j;
  FILE * fd;
  XML_Parser p;
  vals = myVals;
  numVals = myNumVals;
  *numVals = 0;
  strLen = &myStrLen;
  att = NULL;
  expStk.head = NULL;
  expStk.top = -1;
  expStk.cur = -1;
  fd = fopen(fileName, "r");
  if(!fd) {
    fprintf(stderr, "Error: Could not open file '%s'.\n", fileName);
    return -1;
  }
  p = XML_ParserCreate(NULL);
  if (!p) {
    fprintf(stderr, "Error: Could not allocate memory for parser in function 'getxmlvalue'.\n");
    return -1;
  }
  i=2; j=0;
  if(!exp || '\0' == exp[0]) 
    return -1;
  if( exp[0] != '/' || exp[1] != '/')
    return -1;

  temp = NULL;
  while(exp[i] != '\0'){
    if( exp[i] == '/' || exp[i] == '[' || exp[i] == ']') {
      if(0==j && 0==expStk.top) {
        fprintf(stderr, "Error when parsing expression in 'utilXml.c'.\n");
        return -1;
      }
      i++;
      if(strchr(temp, '@'))
        break;
      stackPushBCVTB(temp);
      free(temp);
      temp = NULL;
      j=0;
    }
    else {
      j++;  
      temp = (char*) realloc(temp, sizeof(char)*(j+1));
      if(temp == NULL) {
        fprintf(stderr, "Error: Memory allocation failed in 'utilXml.c'.\n");
        return -1;
      }
      temp[j-1]=exp[i];
      temp[j]='\0';
      i++;
    }
  }
  if(temp[0] == '@'){
    att = (char*) malloc(sizeof(char) * (strlen(temp) ) );
    if(att == NULL) {
      fprintf(stderr, "Error: Memory allocation failed in 'utilXml.c'.\n");
	  free(temp);
      return -1;
    }
    for(i=1; i<strlen(temp); i++) 
      att[i-1] = temp[i];
    att[i-1]='\0';
    free(temp);
  }
  else {
    fprintf(stderr, "Error when parsing expression in 'utilXml.c'.\n");
	free(temp);
	free(att);
	while(i!= -1) stackPopBCVTB();
    return -1;
  }
  expStk.cur = 0;
  if(1 == PARSEVALUE)
    vals[0]='\0';
  *numVals = 0;
  XML_SetElementHandler(p, start, end);

  for (;;) {
    int done;
    int len;

    len = (int)fread(Buff, 1, BUFFSIZE, fd);
    if (ferror(fd)) {
      fprintf(stderr, "Error when reading xml variables in '%s'.\n", fileName);
      return -1;
    }
    done = feof(fd);

    if (XML_Parse(p, Buff, len, done) == XML_STATUS_ERROR) {
      fprintf(stderr, "Error: Parse error in file '%s':\n%s\n",
	      fileName,
              XML_ErrorString(XML_GetErrorCode(p)));
      return -1;
    }

    if (done)
      break;
  }
  if( 0 == *numVals ){
	  fprintf(stderr, "Error: Did not find xml value\n       for expression '%s'.\n       in file '%s'\n", 
		  exp, fileName);
  }
  while( i != -1 ) 
    i = stackPopBCVTB();  
  att = NULL;
  XML_ParserFree(p);
  fclose(fd);
  return 0;

}