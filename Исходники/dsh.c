int parse_input( int * argc , char* input, char*** argv )
{
  dref(argc) = 0; //Count of arguments
  int count = 0; //Counter to store arguments
  int done = 0;
  int before = 0;
  int found = 0;
  int quotes = 0;
  int status = 0;
  
  char** args = NULL;
  char* argin = input;
  char* iptin = input;

  //Tokenize and count number of arguments in input
  while( !done )
  {
    before = found;
    switch( dref(iptin) )
    {
      case 0:
        done = 1;
        break;
        
      case '\"':
        quotes++;
        found = 0;
        break;
        
      case ' ':
        if( is_even(quotes) )
        {
          found = 0;
          break;
        }
        
      case '\t':
      default:
        found = 1;
        if( !before  )
          dref(argc)++;
    }
    if( !done && !found )
      dref(iptin) = 0;
    iptin++;
  }

  //Check if there are an odd number of ""
  if( is_odd(quotes) )
  {
    printf( "Parse error: Unable to match \"\" delimiters.\n" );
    return -1;
  }

  //Allocate Exactly Enough Memory
  if( dref(argc) > 0 )
    args = (char**) malloc( (dref(argc)+1)*sizeof(char*) );
  else
    return 0;

  //Store Arguments
  found = 0;
  argin = input;
  while( argin < iptin )
  {
    if( dref(argin) != 0 )
    {
      if( !found )
      {
        //printf( "Argument %d: %s\n" , count , argin );
        args[count++] = argin;
      }
      found = 1;
    }
    else
      found = 0;
    argin++;
  }
  args[dref(argc)] = NULL;

  //For testing purposes
  if( dref(argc) > 0 && argv != NULL )
  {
    dref(argv) = args;
  }
  else
    free(args);
  return 0;
}