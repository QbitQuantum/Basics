INLINE FILE_LOCAL
ReturnCode cppmain(struct Global *global)
{
  /*
   * Main process for cpp -- copies tokens from the current input
   * stream (main file, include file, or a macro) to the output
   * file.
   */

  int c;        /* Current character    */
  int counter;  /* newlines and spaces  */
  ReturnCode ret; /* return code variable type */

  long bracelevel = 0;
  long parenlevel = 0;
  long bracketlevel = 0;
  int fake = 0;

#define MAX_FUNC_LENGTH 50

  char tempfunc[MAX_FUNC_LENGTH + 1];
  char tempfunc2[MAX_FUNC_LENGTH + 1];
  char define = 0; /* probability of a function define phase in the program */
  char prev = 0; /* previous type */
  char go = 0;
  char include = 0;
  char initfunc = 0;

  /* Initialize for reading tokens */
  global->tokenbsize = 50;
  global->tokenbuf = malloc(global->tokenbsize + 1);
  if(!global->tokenbuf)
    return(FPP_OUT_OF_MEMORY);

  global->functionname = malloc(global->tokenbsize + 1);
  if(!global->functionname)
    return(FPP_OUT_OF_MEMORY);
  global->functionname[0] = '\0';

  if(global->showspace) {
    global->spacebuf = (char *)malloc(MAX_SPACE_SIZE);
    if(!global->spacebuf)
      return(FPP_OUT_OF_MEMORY);
  }

  if(global->showversion)
      Error(global, VERSION_TEXT);

  /*
   * Explicitly output a #line at the start of cpp output so
   * that lint (etc.) knows the name of the original source
   * file.  If we don't do this explicitly, we may get
   * the name of the first #include file instead.
   */
  if(global->linelines) /* if #line lines are wanted! */
    sharp(global);
  /*
   * This loop is started "from the top" at the beginning of each line
   * wrongline is set TRUE in many places if it is necessary to write
   * a #line record.  (But we don't write them when expanding macros.)
   *
   * The counter variable has two different uses:  at
   * the start of a line, it counts the number of blank lines that
   * have been skipped over. These are then either output via
   * #line records or by outputting explicit blank lines.
   * When expanding tokens within a line, the counter remembers
   * whether a blank/tab has been output.  These are dropped
   * at the end of the line, and replaced by a single blank
   * within lines.
   */

  include = global->included;

  while(include--) {
    openinclude(global, global->include[include], TRUE);
  }
  
  for (;;) {
    counter = 0;                        /* Count empty lines    */
    for (;;) {                          /* For each line, ...   */
      global->comment = FALSE;          /* No comment yet!      */
      global->chpos = 0;                /* Count whitespaces    */
      while (type[(c = get(global))] == SPA)  /* Skip leading blanks */
	if(global->showspace) {
	  if(global->chpos<MAX_SPACE_SIZE-1)
	    /* we still have buffer to store this! */
	    global->spacebuf[global->chpos++]=(char)c;
	}
      if (c == '\n') {                  /* If line's all blank, */
	if(global->comment) {
	  /* A comment was output! */
	  Putchar(global, '\n');
	}
	else
	  ++counter;                    /* Do nothing now       */
      }
      else if (c == '#') {              /* Is 1st non-space '#' */
	global->keepcomments = FALSE;   /* Don't pass comments  */
	ret = control(global, &counter); /* Yes, do a #command   */
	if(ret)
	  return(ret);
	global->keepcomments = (global->cflag && compiling);
      }
      else if (c == EOF_CHAR)           /* At end of file?      */
	break;
      else if (!compiling) {            /* #ifdef false?        */
	skipnl(global);                 /* Skip to newline      */
	counter++;                      /* Count it, too.       */
      } else {
	break;                          /* Actual token         */
      }
    }
    if (c == EOF_CHAR)                  /* Exit process at      */
      break;                            /* End of file          */
    /*
     * If the loop didn't terminate because of end of file, we
     * know there is a token to compile.  First, clean up after
     * absorbing newlines.  counter has the number we skipped.
     */
    if(global->linelines) { /* if #line lines are wanted! */
      if ((global->wrongline && global->infile->fp != NULL) || counter > 4)
        sharp(global);                    /* Output # line number */
      else {                              /* If just a few, stuff */
        while (--counter >= 0)            /* them out ourselves   */
	  Putchar(global, (int)'\n');
      }
    }
    if(global->showspace) {
      /* Show all whitespaces! */
      global->spacebuf[global->chpos] = '\0';
      Putstring(global, global->spacebuf);
    }
    
    /*
     * Process each token on this line.
     */
    unget(global);                      /* Reread the char.     */
    for (;;) {                          /* For the whole line,  */
      do {                              /* Token concat. loop   */
	for (global->chpos = counter = 0; (type[(c = get(global))] == SPA);) {
#if COMMENT_INVISIBLE
	  if (c != COM_SEP)
	    counter++;
#else
	  if(global->showspace && global->chpos < MAX_SPACE_SIZE-1) {
	    global->spacebuf[global->chpos++]=(char)c;
	  }
	  counter++;            /* Skip over blanks     */
#endif
	}
	if (c == EOF_CHAR || c == '\n')
	  break;                      /* Exit line loop       */
	else if (counter > 0) {       /* If we got any spaces */
	  if(!global->showspace)      /* We don't output all spaces */
	    Putchar(global, (int)' ');/* Output one space     */
	  else {
	    global->spacebuf[global->chpos] = '\0';
	    Putstring(global, global->spacebuf); /* Output all whitespaces */
	  }
	}
	if(ret=macroid(global, &c))   /* Grab the token       */
	  return(ret);
      } while (type[c] == LET && catenate(global, &ret) && !ret);
      if(ret)
	/* If the loop was broken because of a fatal error! */
	return(ret);
      if (c == EOF_CHAR || c == '\n') /* From macro exp error */
	break;                        /* Exit line loop       */
      go++;
      switch (type[c]) {
      case LET:
	go =0;
	/* Quite ordinary token */
	Putstring(global, global->tokenbuf);
	
	if(!define) {
	  /* Copy the name */
	  strncpy(tempfunc, global->tokenbuf, MAX_FUNC_LENGTH);
          tempfunc[MAX_FUNC_LENGTH]=0;
	}
	/* fputs(global->tokenbuf, stdout); */
	break;
      case DIG:                 /* Output a number      */
      case DOT:                 /* Dot may begin floats */
	go = 0;
	ret=scannumber(global, c, (ReturnCode(*)(struct Global *, int))output);
	if(ret)
	  return(ret);
	break;
      case QUO:                 /* char or string const */
	go = 0;
	/* Copy it to output */
        if(!global->webmode) {
          ret=scanstring(global, c,
                         (ReturnCode(*)(struct Global *, int))output);
          if(ret)
            return(ret);
          break;
        }
        /* FALLTHROUGH */
      default:                  /* Some other character */
	
	define++;
	switch(c) {
	case '{':
	  if(! bracelevel++ && define > 2) {
	    /*
	     * This is a starting brace. If there is a probability of a
	     * function defining, we copy the `tempfunc' function name to
	     * `global->functionname'.
	     */
	    strcpy(global->functionname, tempfunc2);
	    global->funcline = global->line;

		if(global->outputfunctions) {
			/*
			 * Output the discovered function name to stderr!
			 */
			Error(global, "#> Function defined at line %d: %s <#\n",
				  global->line,
				  global->functionname);
		}

	    if(global->initialfunc) {
		int a;
		for(a=0; a<global->excluded; a++) {
		    /* check for excluded functions */
		    if(!strcmp(global->functionname,
			       global->excludedinit[a]))
			break;
		}
		if(a==global->excluded) {
		    expstuff(global, "__brace__", "{");
		    expstuff(global, "__init_func__", global->initialfunc);
		    initfunc = TRUE;
		}
	    }

	  }
	  break;
	case '}':
	  go = 0;
	  if( (--bracelevel == initfunc) &&
	     strcmp(global->infile->filename, "__init_func__") ) {
	    /* we just stepped out of the function! */
	    global->functionname[0] = '\0';
	    global->funcline = 0;
	    define = 1;

	    if(initfunc) {
	      Putchar(global, '}');
	      bracelevel--;
	      initfunc=0;
	    }
	  }
	  fake = 0;
	  break;
	  
	case ';':
	case ',':
	  if(go == 2) {
	    define = 1;
	    fake = 0;
	    go--;
	    break;
	  }
	  break;
	case '(':
	  if(! parenlevel++ && !bracelevel) {
	    if(go == 2) {
	      /* foobar(text) -> "(" is found. This can't be a
		 function */
	      go--;
	      define = 1;
	      break;
	    }
	    if( define < 2 && prev == LET) {
	      /* This is the first parenthesis on the ground brace
		 level, and we did previously not have a probable
		 function name */
	      strncpy(tempfunc2, global->tokenbuf, MAX_FUNC_LENGTH);
              tempfunc2[MAX_FUNC_LENGTH]=0;
	      define++;
	    }
	    else {
	      /* we have a fake start */
	      fake++;
	    }
	  }
	  break;
	case ')':
	  if(! --parenlevel && !bracelevel && define>1 && !fake) {
	    /*
	     * The starting parentheses level and
	     * the starting brace level.
	     * This might be the start of a function defining coming
	     * up!
	     */
	    define++; /* increase probability */
	    fake = 0;
	    go = 1;
	  }
	  break;
	case '[':
	  bracketlevel++;
	  break;
	case ']':
	  bracketlevel--;
	  break;
	}
	define--; /* decrease function probability */
	
	Putchar(global, c);     /* Just output it       */
	break;
      }                         /* Switch ends          */
      prev = type[c];
    }                           /* Line for loop        */
    
    if (c == '\n') {  /* Compiling at EOL?    */
      Putchar(global, '\n');              /* Output newline, if   */
      if (global->infile->fp == NULL)     /* Expanding a macro,   */
	global->wrongline = TRUE; /* Output # line later        */
    }
  }                             /* Continue until EOF   */

  if(global->showbalance) {
    if(bracketlevel) {
      cwarn(global, WARN_BRACKET_DEPTH, bracketlevel);
    }
    if(parenlevel) {
      cwarn(global, WARN_PAREN_DEPTH, parenlevel);
    }
    if(bracelevel) {
      cwarn(global, WARN_BRACE_DEPTH, bracelevel);
    }
  }
  if (global->wflag) {
    global->out = TRUE;         /* enable output */
    outdefines(global);         /* Write out #defines   */
  }
  return(FPP_OK);
}