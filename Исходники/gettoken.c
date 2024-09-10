static int yylex2(void) {
  int ch;
  int chkcomment = FALSE;

yuk_a_goto:
	eatwhite();
	if ((ch = GETC(fname)) == EOF) {
	  if (firstsemi == 1) {
	    firstsemi = 0;
	    fclose(fname);
	    fname = fnamesave;
	    goto yuk_a_goto;
	  }
	  else {
	    return(TENDOFFILE);
	  }
	}
	do {
		if (ch == '/')
			if ((ch = GETC(fname)) == '*') {
				eatcomment();
				eatwhite();
				chkcomment = TRUE;
				if ((ch = GETC(fname)) == EOF)
					return(TENDOFFILE);
			} else {
				UNGETC(ch, fname);
				ch = '/';
				chkcomment = FALSE;
			}
		else if (ch == '-')	/* -- is a comment in our language */
		{
			if ((ch = GETC(fname)) == '-')
			{
				eatline();	 /* ignore rest of line */
				if (firstsemi != 1) yylineno++;
				eatwhite();
				chkcomment = TRUE;
				if ((ch = GETC(fname)) == EOF)
					return(TENDOFFILE);
			}
			else
			{
				UNGETC(ch, fname);
				ch = '-';
				chkcomment = FALSE;
			}
		}
		else
			chkcomment = FALSE;
	} while (chkcomment);
	if (isalpha(ch) || ch == '_')
		return(eatident(ch));
	if (isdigit(ch))
		return(eatnumber(ch));
	if (ch == '"')
		return(eatstring());
	if (ch == '\'') {
	  char ch2;
	  char ch3;
	  char chat;
	  int ate;
	  
	  ch2 = GETC(fname);
	  ch3 = GETC(fname);
	  UNGETC(ch3,fname);
	  UNGETC(ch2,fname);
	  if (ch2 != ' ' || ch3 != '\'') {
	    /* can't eat whitespace if char contains whitespace */
	    ate = eatwhite();
	    chat = GETC(fname);
	    UNGETC(chat,fname);
	    if (chat == '@') {
	      if (ate || (ch2 != '@' && ch3 != '\'')) {
		return TPRIME;
	      }
	    }
	  }
	  return eatcharacter();
	}
	if (ch == '.') {
		if (isdigit(ch = GETC(fname))) {
			UNGETC(ch, fname);
			ch = '.';
			return(eatnumber(ch));
		} else {
			UNGETC(ch, fname);
			ch = '.';
		}
	}
	if (ch == '#') {
	  char ch2;
		eatwhite();
		/* remove "line" if it exists - some vers of cpp have this */
		if ((ch2 = GETC(fname)) == '[') {
		  UNGETC(ch2, fname);
		  return eatleftovers(ch);
		}
		else {
		  UNGETC(ch2, fname);
		}
		if (!isdigit(ch = GETC(fname))) {
			UNGETC(ch, fname);
			yylex2();
			if (!strcmp(buffer,"pragma")) {
			  for (ch = GETC(fname); ch != '\n'; ch = GETC(fname)) ;
			  goto yuk_a_goto;
			}
			if (strcmp(buffer,"line")) {
			  USR_FATALX(yylineno, in_file,
				     "syntax error (appears to be a cpp directive: try -cpp)");
			}
			eatwhite();
		} else {
			UNGETC(ch, fname);
		}

		if (!isdigit(ch = GETC(fname))) {
			UNGETC(ch, fname);
			USR_FATALX(yylineno, in_file,
				   "syntax error (appears to be a cpp directive: use -cpp)");
		} else
			UNGETC(ch, fname);
		yylex2();
		yylineno = atoi(buffer);

		for (ch = GETC(fname); ch != '"' && ch != '\n'; ch = GETC(fname))
			;
		if (ch != '"') {
			goto yuk_a_goto;
		} else
			UNGETC(ch, fname);
		yylex2();

		
		in_file = (char *)PMALLOC((strlen(buffer) + 1)*sizeof(char));
		strcpy(in_file, buffer);
		base_in_file = strrchr(in_file,'/');
		if (base_in_file == NULL) {
		  base_in_file = in_file;
		} else {
		  base_in_file++;
		}
		for (ch = GETC(fname); ch != '\n'; ch = GETC(fname))
			;

		goto yuk_a_goto;
	}
	if (ispunct(ch))
		return(eatleftovers(ch));

	
	buffer[0] = ch; buffer[1] = '\0';

	  if (firstsemi == 1) {
	    firstsemi = 0;
	    fclose(fname);
	    fname = fnamesave;
	    goto yuk_a_goto;
	  }

	return(-1);
}