        current->next = new;
        current = new;
      }
      current->indent = indent;
      d = current->s;
      if( *s == '\t' || cont == 1 ) current->label = 0;
      else {
        current->label = strtol(s, &d2, 10);
        if( d2 != s ) p = d2, *xrp++ = current;
      }
      if( cont == 1 ) {
        current->indent += 2;
        if( !space ) *d++ = '&';
      }
    }
    p = (char *)memccpy(d, p + strspn(p, " \t"), 0, 256) - 2;
    while( p > s && (*p == ' ' || *p == '\t') ) --p;
    *++p = 0;
    if( *s == '*' || (*s | 0x20) == 'c' ) {
      *d = '!';
			/* this is a dirty hack to cure some problems
			   the DEC f90 compiler has with FF */
      if( strstr(s, "#] declarations") ) strcpy(p, "\ncontinue");
      continue;
    }
    for( p = s, d2 = d; *d2; ) *p++ = tolower(*d2++);
    *p = 0;
    if( strncmp(s, "include", 7) == 0 || strncmp(s, "#include", 8) == 0 ) {
      if( (p = strpbrk(d + 7, "'\"<")) && (d2 = strpbrk(++p, "'\">")) ) {
        ch = *d2;
        *d2 = 0;