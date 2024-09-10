char *str_token( TOKEN *tok )
{  
  /* skip leading blanks and tabs */

  while( *(tok->next_token) == ' ' || *(tok->next_token) == '\t' ) (tok->next_token)++;  
  tok->actual_token = tok->next_token;

  /* search for open c-comment */

  while( *++(tok->next_token) )
    if( *(tok->next_token) == '/' )
    {
      if( *(tok->next_token-1) == '*' )
      {
        tok->tok_type = TOK_C_COMMENT;
        tok->next_token = char_insert( tok->next_token + 1, '\0' );
        tok->tok_length = (int)(tok->next_token - tok->actual_token - 1);
        return( tok->actual_token );
      }
      if( *(tok->next_token+1) == '*' )
        break;
    }    

  tok->next_token = tok->actual_token;    
  
  /* *next_token is printable character, except space */

  if( '\x20' < *(tok->next_token) && '\x7F' > *(tok->next_token) )
    switch( *(tok->next_token) )
    {
      case '#' :                        /* token is user comment */
        tok->tok_type = TOK_USR_COMMENT;
        while( *++(tok->next_token) );
        tok->tok_length = (int)(tok->next_token - tok->actual_token);
        return( tok->actual_token );
      case '"' :                        /* token is string, delimiter '"' */
        tok->tok_type = TOK_STRING;
        while( *++(tok->next_token) )
          if( *(tok->next_token) == '"' )
          {
            *(tok->next_token)++ = '\0';
            break;
          }
        (tok->actual_token)++;
        tok->tok_length = (int)(tok->next_token - tok->actual_token);
        if( *(tok->next_token) ) (tok->tok_length)--;
        return( tok->actual_token );       
      case '\'' :                       /* token is string, delimiter '\'' */
        tok->tok_type = TOK_STRING;
        while( *++(tok->next_token) )
          if( *(tok->next_token) == '\'' )
          {
            *(tok->next_token)++ = '\0';
            break;
          }
        (tok->actual_token)++;
        tok->tok_length = (int)(tok->next_token - tok->actual_token);
        if( *(tok->next_token) ) (tok->tok_length)--;
        return( tok->actual_token );       
      case '/' :
        if( *++(tok->next_token) == '*' )      /* token is c comment */
        {
          tok->tok_type = TOK_C_COMMENT;
          while( *++(tok->next_token) )
            if( *(tok->next_token) == '*' && *(tok->next_token+1) == '/' )
            {
              tok->next_token = char_insert( tok->next_token + 2, '\0' );
              break;
            }  
          tok->tok_length = (int)(tok->next_token - tok->actual_token);
          if( *(tok->next_token) ) (tok->tok_length)--;
          return( tok->actual_token );
        }
        (tok->next_token)--;
      default :                         /* token is alphanumerical */    
        tok->tok_type = TOK_ALNUM;
        while( isgraph( *++(tok->next_token) ) );
        tok->next_token = char_insert( tok->next_token, '\0' );
        tok->tok_length = (int)(tok->next_token - tok->actual_token - 1);
        return( tok->actual_token );
      }
  else                                    /* token is not printable */
    switch( *(tok->next_token) )
    {
      case '\0' :
        tok->tok_type = TOK_EOS;          /* End Of String reached */
        return( NULL );
      default   :
        if( *(tok->next_token) <= '\x20' )
          tok->tok_type = TOK_CONTROL;   /* Control character */
        else
          tok->tok_type = TOK_INVALID;   /* Invalid token */
        (tok->next_token)++;
        tok->tok_length = 1;
        return( NULL );   
     }
}