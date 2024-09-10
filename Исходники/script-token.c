WandExport MagickBooleanType GetScriptToken(ScriptTokenInfo *token_info)
{
  int
    quote,
    c;

  int
    state;

  ssize_t
    offset;

  /* EOF - no more tokens! */
  if (token_info->status != TokenStatusOK)
    {
      token_info->token[0]='\0';
      return(MagickFalse);
    }

  state=IN_WHITE;
  quote='\0';
  offset=0;
  while(1)
  {
    /* get character */
    GetChar(c);

    /* hash comment handling */
    if ( state == IN_COMMENT ) {
      if ( c == '\n' )
        state=IN_WHITE;
      continue;
    }
    /* comment lines start with '#' anywhere, or ':' or '@' at start of line */
    if ( state == IN_WHITE )
      if ( ( c == '#' ) ||
           ( token_info->curr_column==1 && (c == ':' || c == '@' ) ) )
        state=IN_COMMENT;
    /* whitespace token seperator character */
    if (strchr(" \n\r\t",c) != (char *)NULL) {
      switch (state) {
        case IN_TOKEN:
          token_info->token[offset]='\0';
          return(MagickTrue);
        case IN_QUOTE:
          SaveChar(c);
          break;
      }
      continue;
    }
    /* quote character */
    if ( c=='\'' || c =='"' ) {
      switch (state) {
        case IN_WHITE:
          token_info->token_line=token_info->curr_line;
          token_info->token_column=token_info->curr_column;
        case IN_TOKEN:
          state=IN_QUOTE;
          quote=c;
          break;
        case IN_QUOTE:
          if (c == quote)
            {
              state=IN_TOKEN;
              quote='\0';
            }
          else
            SaveChar(c);
          break;
      }
      continue;
    }
    /* escape char (preserve in quotes - unless escaping the same quote) */
    if (c == '\\')
      {
        if ( state==IN_QUOTE && quote == '\'' ) {
            SaveChar('\\');
            continue;
          }
        GetChar(c);
        if (c == '\n')
          switch (state) {
            case IN_COMMENT:
              state=IN_WHITE;  /* end comment */
            case IN_QUOTE:
              if (quote != '"')
                break;         /* in double quotes only */
            case IN_WHITE:
            case IN_TOKEN:
              continue;        /* line continuation - remove line feed */
          }
        switch (state) {
          case IN_WHITE:
            token_info->token_line=token_info->curr_line;
            token_info->token_column=token_info->curr_column;
            state=IN_TOKEN;
            break;
          case IN_QUOTE:
            if (c != quote && c != '\\')
              SaveChar('\\');
            break;
        }
        SaveChar(c);
        continue;
      }
    /* ordinary character */
    switch (state) {
      case IN_WHITE:
        token_info->token_line=token_info->curr_line;
        token_info->token_column=token_info->curr_column;
        state=IN_TOKEN;
      case IN_TOKEN:
      case IN_QUOTE:
        SaveChar(c);
        break;
      case IN_COMMENT:
        break;
    }
  }
  /* input stream has EOF or produced a fatal error */
  token_info->token[offset]='\0';
  if ( token_info->status != TokenStatusOK )
    return(MagickFalse);  /* fatal condition - no valid token */
  token_info->status = TokenStatusEOF;
  if ( state == IN_QUOTE)
    token_info->status = TokenStatusBadQuotes;
  if ( state == IN_TOKEN)
    return(MagickTrue);   /* token with EOF at end - no problem */
  return(MagickFalse);    /* in white space or in quotes - invalid token */
}