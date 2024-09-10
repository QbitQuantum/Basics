char * putCatch( char * newStr, const char * putStr ){
  char *oNewStr = newStr;

  while( *putStr )
    switch( *putStr ){
    case '#':
      if( *++putStr == '#' )
        *newStr++ = *putStr++;
      else {
        int index = aToi( putStr );
        cpyCatch( newStr, index );
        newStr += lenCatch( index );
        putStr += countCharDigits( putStr );
      } break;
    default : *newStr++ = *putStr++;
    }

  *newStr = '\0';

  return oNewStr;
}