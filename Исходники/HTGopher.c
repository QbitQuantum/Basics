PRIVATE void parse_menu ARGS2 (
                               CONST char *,	arg,
                               HTParentAnchor *,anAnchor)
{
  char gtype;
  char ch;
  char line[BIG];
  char address[BIG];
  char *name, *selector;		/* Gopher menu fields */
  char *host;
  char *port;
  char *p = line;
  
  
#define TAB 		'\t'
#define HEX_ESCAPE 	'%'
  
  if (!HTAnchor_title(anAnchor))
    HTAnchor_setTitle(anAnchor, arg);/* Tell user something's happening */
  
  node_anchor = anAnchor;
  HT = HText_new(anAnchor);
  
  HText_beginAppend(HT);
  HText_appendText(HT, "Select one of:<P>\n<UL>");
  /* HText_appendText(HT, "Select one of:<P>\n<UL>"); */
  
  while ((ch=NEXT_CHAR) != (char)EOF) 
    {
      if (ch != '\n') 
        {
          *p = ch;		/* Put character in line */
          if (p< &line[BIG-1]) p++;
        } 
      else 
        {
          *p++ = 0;		/* Terminate line */
          p = line;		/* Scan it to parse it */
          port = 0;		/* Flag "not parsed" */
          if (TRACE) fprintf(stderr, "HTGopher: Menu item: %s\n", line);
          gtype = *p++;
          
          /* Break on line with a dot by itself */
          if ((gtype=='.') && ((*p=='\r') || (*p==0))) break;
          
          if (gtype && *p) 
            {
              name = p;
              selector = strchr(name, TAB);
              if (selector) {
                *selector++ = 0;	/* Terminate name */
                host = strchr(selector, TAB);
                if (host) {
                  *host++ = 0;	/* Terminate selector */
                  port = strchr(host, TAB);
                  if (port) {
                    char *junk;
                    port[0] = ':';	/* delimit host a la W3 */
                    junk = strchr(port, 13 /* was TAB */);
                    if (junk) *junk++ = 0;	/* Chop port */
                    if ((port[1]=='0') && (!port[2]))
                      port[0] = 0;	/* 0 means none */
                  } /* no port */
                } /* host ok */
              } /* selector ok */
            } /* gtype and name ok */
          
          if (gtype == GOPHER_WWW) 
            {	/* Gopher pointer to W3 */
              HText_appendText(HT, "<LI> ");
              write_anchor(name, selector);
              HText_appendText(HT, "\n");
              /* HText_appendParagraph(HT); */
            } 
          else if (port) 
            {		/* Other types need port */
              if (gtype == GOPHER_TELNET) 
                {
                  if (*selector) 
                    sprintf(address, "telnet://%s@%s/",
                            selector, host);
                  else 
                    sprintf(address, "telnet://%s/", host);
                }
              else if (gtype == GOPHER_TN3270) 
                {
                  if (*selector) 
                    sprintf(address, "tn3270://%s@%s/",
                            selector, host);
                  else 
                    sprintf(address, "tn3270://%s/", host);
                }
              else 
                {			/* If parsed ok */
                  char *q;
                  char *p;
                  sprintf(address, "gopher://%s/%c", host, gtype);
                  q = address+ strlen(address);
                  for(p=selector; *p; p++) {	/* Encode selector string */
                    /* fprintf (stderr, "Checking %d (%c) for acceptable.\n",
                     *p, *p); */
                    if (acceptable[*p]) *q++ = *p;
                    else {
                      *q++ = HEX_ESCAPE;	/* Means hex coming */
                      *q++ = hex[(TOASCII(*p)) >> 4];
                      *q++ = hex[(TOASCII(*p)) & 15];
                    }
                  }
                  *q++ = 0;			/* terminate address */
                }
              /* HText_appendText(HT, "        "); */ /* Prettier JW/TBL */
              HText_appendText(HT, "<LI> ");
              /* Error response from Gopher doesn't deserve to
                 be a hyperlink. */
              if (strcmp (address, "gopher://error.host:1/0"))
                write_anchor(name, address);
              else
                HText_appendText(HT, name);
              HText_appendText(HT, "\n");
              /* HText_appendParagraph(HT); */
            } 
          else 
            { /* parse error */
              if (TRACE) fprintf(stderr,
                                 "HTGopher: Bad menu item.\n");
              HText_appendText(HT, line);
              HText_appendParagraph(HT);
            } /* parse error */
          
          p = line;	/* Start again at beginning of line */
          
        } /* if end of line */
      
    } /* Loop over characters */