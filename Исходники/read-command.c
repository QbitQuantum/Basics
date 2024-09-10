command_stream_t
make_command_stream (int (*get_next_byte) (void *), void *get_next_byte_argument)
{
  //=========Let's just try to read the input in first.============//
  
  size_t bufferSize = 1024;
  size_t bufferIterator = 0;
  char value;
  char* buffer = (char*) checked_malloc(bufferSize);

  while ((value = get_next_byte(get_next_byte_argument)) != EOF) //store into value while it isn't EOF
  {
    buffer[bufferIterator++] = value;
    //    printf("looped once: %c \n", value);
    //    printf("bufferSize: %d \n", (int) bufferSize);
    if (bufferSize == bufferIterator){
      buffer =  (char*) checked_grow_alloc(buffer, &bufferSize);
      //printf("called checked_realloc: %d\n", (int) bufferSize);
    }
  }
  if (bufferSize == bufferIterator){
    buffer =  (char*) checked_grow_alloc(buffer, &bufferSize);
    //printf("called checked_realloc: %d\n", (int) bufferSize);
  }
  buffer[bufferIterator] = '\0';

  //printf("bufferIterator: %d \n", (int) bufferIterator);
  //puts(buffer);  //will output to stdout
  
  //=========Let's tokenize the stream============//
  //we need to do the same thing as before, except instead of taking from the filestream and putting it into the array.
  //Now take the array and put it into a token stream.
  //Could never get the outside function working due to all that referential bullshit.  Let's just do it inline.

  
  token_stream* tstream = (token_stream*) checked_malloc(sizeof(token_stream*));
  token_stream* trackend = tstream;
  int bufferIteratorT = 0;
  int comment = 0;
  int linNumber = 1;

  token_type type;
  
  //do a dual parsing here where we handle two characters at the same time. This makes the && and || and comments easy
  //Need to check if the buffer is completely empty (has '\0' as the only character).  Then we don't do anything so we  //can just return

  if (buffer[bufferIteratorT] == '\0')
  {  
    command_stream_t empty = (command_stream_t) checked_malloc(sizeof(command_stream_t));
    empty->size = 0;
    return empty;
  }
  
  char first;
  char second;
  while (buffer[bufferIteratorT+1] != '\0')
  {
    first = buffer[bufferIteratorT];
    second = buffer[bufferIteratorT+1];

    //Check for &&
    if (first == '&')
      {
        if (second == '&')
          { 
     	    type = AND_TOKEN;
	    bufferIteratorT++;//deals with the fact that && is two chars
          }
        else
          {
	    type = MISC_TOKEN;  //We can test for MISC_TOKEN later, this is an invalid input, only 1 &
          }
      }
    
    //Check for ||
    else if (first == '|')
      {
	if (second == '|')
	  {
	    type = OR_TOKEN;
	    bufferIteratorT++;
          }
	else
	  {
	    type = PIPE_TOKEN;	    
	  }
      }

    else if (first == '#')
      {
	
	if (bufferIteratorT != 0 && isWordChar(buffer[bufferIteratorT-1]))
	  {
	    //if BIT is not 0 , then check if prior is a word, definitely a comment
	    fprintf(stderr,"%i: problem at this line in script\n", linNumber);
	    exit(0);
	  }
	type = COMMENTS_TOKEN;
      	comment = 1;
      }

    else if (first == ';')
      {
	type = SEMICOLON_TOKEN;
      }

    else if (first == '(')
      {
	type = LEFT_PAREN_TOKEN;
      }

    else if (first == ')')
      {
	type = RIGHT_PAREN_TOKEN;
      }

    else if (first == '<')
      {
	type = LESS_TOKEN;
      }

    else if (first == '>')
      {
	type = GREATER_TOKEN;
      }

    else if (first == '\n')
      {
	type = NEWLINE_TOKEN;
	linNumber++;
	comment = 0;
      }

    else //unknown character 
      {
	type = MISC_TOKEN;
      }
    //idea is to figure out how long the word length is and then use token adding part to figure out how far to add the words.  Also, make sure you move ahead in the outer loop.  This will also overwrite MISC_TOKEN if word is found
    int wordlength = 1;
    int placeholder = bufferIteratorT;
    if (isWordChar(first))  
      {
	type = WORD_TOKEN;
	
	while (isWordChar(buffer[bufferIteratorT+wordlength]))
	  {
	    wordlength++;
	  }
        bufferIteratorT += wordlength-1;
	//	printf("placeholder: %d + \n" , placeholder);
	//printf("end: %d \n", bufferIteratorT);
      }

    //token insertion here.
    if (first == ' ' || first == '\t' || comment == 1)
      {
	//Don't insert
      }
    else 
      {
	token temp;
	temp.type = type;
	temp.linNum = linNumber;
	if ( type == WORD_TOKEN)
	  {
	    temp.words = (char*) checked_malloc ((sizeof(char)*wordlength)+1);
	    int i = 0;
	    for (; i != wordlength;i++)
	    {
	    	temp.words[i] = buffer[placeholder+i]; 
	    }
	    temp.words[i] = '\0';
	  }
	else
	  {
	    temp.words = NULL;	
	  }
	//now insert into token stream
	token_stream* temp_ts = (token_stream*) checked_malloc(sizeof(token_stream*));
	temp_ts->m_token = temp;  
	//might have a serious problem here because if m_token is just a copy of 
	//temp and temp gets erased because temp goes out of scope (e.g. out of this function), 
	//temp might get erased and that also deletes our character array for words, leaving a dangling pointer.
	temp_ts->next = NULL;
	temp_ts->prev = trackend;
	trackend->next = temp_ts;
	trackend = temp_ts;
      }
    bufferIteratorT++;
  }
  
  //now tstream should point to the beginning of a token stream
  //the issue is we initialize the tstream to a blank token so happens is the first token_stream in tstream is empty so we skip it.

  tstream = tstream->next;
  
  //=========Code that outputs the tokens so we can test them============//
  
  puts("WORD_TOKEN: 0 \nSEMICOLON_TOKEN: 1 \nPIPE_TOKEN: 2 \nAND_TOKEN: 3 \nOR_TOKEN: 4 \nLEFT_PAREN_TOKEN: 5 \nRIGHT_PAREN_TOKEN: 6 \nGREATER_TOKEN: 7 \nLESS_TOKEN: 8 \nCOMMENTS_TOKEN: 9 \nNEWLINE_TOKEN: 10 \nMISC_TOKEN: 11 \n");
  
  //puts(tstream->m_token.words);
  /*
  while (tstream->next != NULL)
    {
      //printf("%d \n", tstream->m_token.type);
      //the above line works to display just the tokens, the below doesn't work because there's a segfault on accessing the token words
      if (tstream->m_token.type == WORD_TOKEN)
	{
	  printf("%d:%i: ", tstream->m_token.type, tstream->m_token.linNum);
	puts(tstream->m_token.words);
	//puts("\n");
	}
      else
	printf("%d:%i \n", tstream->m_token.type, tstream->m_token.linNum);
    
      tstream = tstream->next;
    }
printf("%d \n", tstream->m_token.type);
  */

  //=========Code that checks for input errors and validates the tokens before parsing tokens into commands============//

  int leftParenCount = 0;
  int rightParenCount = 0;
  while (tstream != NULL)
  {

    //MISC_TOKENS find inputs not in our subset syntax
    if (tstream->m_token.type == MISC_TOKEN)
      {
       fprintf(stderr,"%i: problem at this line in script\n", tstream->m_token.linNum);
       exit(0);
      }

    //Do count of parentheses 
    if (tstream->m_token.type == LEFT_PAREN_TOKEN)
      leftParenCount++;
    if (tstream->m_token.type == RIGHT_PAREN_TOKEN)
      rightParenCount++;
    if (tstream->next == NULL && leftParenCount != rightParenCount)
      {
	fprintf(stderr,"%i: Unmatching Parentheses\n", tstream->m_token.linNum);  //not sure about this
	exit(0);
      }      

    //Redirec always followed by a word.
    if (tstream->m_token.type == LESS_TOKEN || tstream->m_token.type == GREATER_TOKEN)
      {
	if (tstream->next == NULL)
	  {
	    fprintf(stderr,"%i: Redirect Needs a word following it.\n", tstream->m_token.linNum);
	    exit(0);
	  }
	else if (tstream->next->m_token.type != WORD_TOKEN)
          {
	    fprintf(stderr,"%i: Need word after redirect\n", tstream->m_token.linNum);  
	    exit(0);
	  }        
      }
   
    //Newlines have some specific places they can appear in.
    if (tstream->m_token.type == NEWLINE_TOKEN)
      {
	//check the ones after it for ( ) or words
	if (tstream->next != NULL)
	  {
	    if (tstream->next->m_token.type == LEFT_PAREN_TOKEN || tstream->next->m_token.type == RIGHT_PAREN_TOKEN || tstream->next->m_token.type == WORD_TOKEN)
	      {}
	    else
	      {
		fprintf(stderr,"%i: newline is followed by (,), or words\n", tstream->m_token.linNum);  
		exit(0);
	      }        
	  }
      }

    tstream = tstream->next;
  }
  
      // idea here it to represent problems parsing the code with MISC_TOKEN and have code up in the tokenization part where if the 
      //token is a MISC token, store the line number into the char* words array and if we detect it here, then output it with the line number.

  //=========Changes the tokens into commands============//
  command_stream_t fake = (command_stream_t) checked_malloc(sizeof(command_stream_t));
  fake->size = 1;
  fake->iterator = 0;
  return fake;
}