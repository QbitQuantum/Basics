void Wrapper_compact_print(String *str, File *f) {
  String *ts, *tf;		/*temp string & temp file */
  int level = 0;
  int c, i;
  int empty = 1;
  int indent = 2;

  ts = NewStringEmpty();
  tf = NewStringEmpty();
  Seek(str, 0, SEEK_SET);

  while ((c = Getc(str)) != EOF) {
    if (c == '\"') {		/* string 1 */
      empty = 0;
      Putc(c, ts);
      while ((c = Getc(str)) != EOF) {
	if (c == '\\') {
	  Putc(c, ts);
	  c = Getc(str);
	}
	Putc(c, ts);
	if (c == '\"')
	  break;
      }
    } else if (c == '\'') {	/* string 2 */
      empty = 0;
      Putc(c, ts);
      while ((c = Getc(str)) != EOF) {
	if (c == '\\') {
	  Putc(c, ts);
	  c = Getc(str);
	}
	Putc(c, ts);
	if (c == '\'')
	  break;
      }
    } else if (c == '{') {	/* start of {...} */
      empty = 0;
      Putc(c, ts);
      if (Len(tf) == 0) {
	for (i = 0; i < level; i++)
	  Putc(' ', tf);
      } else if ((Len(tf) + Len(ts)) < Max_line_size) {
	Putc(' ', tf);
      } else {
	Putc('\n', tf);
	Printf(f, "%s", tf);
	Clear(tf);
	for (i = 0; i < level; i++)
	  Putc(' ', tf);
      }
      Append(tf, ts);
      Clear(ts);
      level += indent;
      while ((c = Getc(str)) != EOF) {
	if (!isspace(c)) {
	  Ungetc(c, str);
	  break;
	}
      }
    } else if (c == '}') {	/* end of {...} */
      empty = 0;
      if (Len(tf) == 0) {
	for (i = 0; i < level; i++)
	  Putc(' ', tf);
      } else if ((Len(tf) + Len(ts)) < Max_line_size) {
	Putc(' ', tf);
      } else {
	Putc('\n', tf);
	Printf(f, "%s", tf);
	Clear(tf);
	for (i = 0; i < level; i++)
	  Putc(' ', tf);
      }
      Append(tf, ts);
      Putc(c, tf);
      Clear(ts);
      level -= indent;
    } else if (c == '\n') {	/* line end */
      while ((c = Getc(str)) != EOF) {
	if (!isspace(c))
	  break;
      }
      if (c == '#') {
	Putc('\n', ts);
      } else if (c == '}') {
	Putc(' ', ts);
      } else if ((c != EOF) || (Len(ts) != 0)) {
	if (Len(tf) == 0) {
	  for (i = 0; i < level; i++)
	    Putc(' ', tf);
	} else if ((Len(tf) + Len(ts)) < Max_line_size) {
	  Putc(' ', tf);
	} else {
	  Putc('\n', tf);
	  Printf(f, "%s", tf);
	  Clear(tf);
	  for (i = 0; i < level; i++)
	    Putc(' ', tf);
	}
	Append(tf, ts);
	Clear(ts);
      }
      Ungetc(c, str);

      empty = 1;
    } else if (c == '/') {	/* comment */
      empty = 0;
      c = Getc(str);
      if (c != EOF) {
	if (c == '/') {		/* C++ comment */
	  while ((c = Getc(str)) != EOF) {
	    if (c == '\n') {
	      Ungetc(c, str);
	      break;
	    }
	  }
	} else if (c == '*') {	/* C comment */
	  int endstar = 0;
	  while ((c = Getc(str)) != EOF) {
	    if (endstar && c == '/') {	/* end of C comment */
	      break;
	    }
	    endstar = (c == '*');
	  }
	} else {
	  Putc('/', ts);
	  Putc(c, ts);
	}
      }
    } else if (c == '#') {	/* Preprocessor line */
      Putc('#', ts);
      while ((c = Getc(str)) != EOF) {
	Putc(c, ts);
	if (c == '\\') {	/* Continued line of the same PP */
	  c = Getc(str);
	  if (c == '\n')
	    Putc(c, ts);
	  else
	    Ungetc(c, str);
	} else if (c == '\n')
	  break;
      }
      if (!empty) {
	Append(tf, "\n");
      }
      Append(tf, ts);
      Printf(f, "%s", tf);
      Clear(tf);
      Clear(ts);
      for (i = 0; i < level; i++)
	Putc(' ', tf);
      empty = 1;
    } else {
      if (!empty || !isspace(c)) {
	Putc(c, ts);
	empty = 0;
      }
    }
  }
  if (!empty) {
    Append(tf, ts);
  }
  if (Len(tf) != 0)
    Printf(f, "%s", tf);
  Delete(ts);
  Delete(tf);
  Printf(f, "\n");
}