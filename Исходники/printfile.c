int printfile(FILE *fp, char *format, char *label, char *subject,
	      char *dir, char *name, char *email, char *message_id,
	      char *charset, char *date, char *filename)
{
    register char *cp;
    register char *aptr;
    char c;
    char *ptr,*tmpptr=NULL;
    size_t tmplen;

    aptr = format;

    while ((c = *aptr++)) {
	if (c == '\\') {
	    switch (*aptr++) {
	    case 'n':		/* Add the \n character */
		putc('\n', fp);
		continue;
	    case 't':		/* Add the \t character */
		putc('\t', fp);
		continue;
	    default:
		break;
	    }			/* end switch */
	}
	else if (c == '%') {
            char nextone = *aptr++;
	    switch (nextone) {
	    case '%':		/* Add the % character */
		putc('%', fp);
		continue;
	    case '~':		/* %~ - storage directory */
		for (cp = dir; *cp; cp++)
		    putc(*cp, fp);
		continue;
	    case 'A':		/* %e - email address of message author */
		if (email && name) {
#ifdef HAVE_ICONV
		  tmpptr=i18n_convstring(name,"UTF-8",charset,&tmplen);
		  cp = convchars(tmpptr,charset);
		  if(tmpptr)
		    free(tmpptr);
		  fprintf(fp,
			"<meta name=\"Author\" content=\"%s (%s)\" />",
			cp, obfuscate_email_address(email));
		  if (cp)
		    free(cp);
#else
		fprintf(fp,
			"<meta name=\"Author\" content=\"%s (%s)\" />",
			tmpptr=convchars(name,charset), obfuscate_email_address(email));
		if (tmpptr)
		  free(tmpptr);
#endif
		}
		continue;
	    case 'a':		/* %a - Other Archives URL */
		if (set_archives) {
		    for (cp = set_archives; *cp; cp++)
			putc(*cp, fp);
		}
		continue;
	    case 'B':
	      printf("Warning: the %%B option has been disabled. Use a\n"
		     "style sheet instead. See the INSTALL file for more info.\n");
	      continue;
	    case 'b':		/* %b - About this archive URL */
		if (set_about) {
		    for (cp = set_about; *cp; cp++)
			putc(*cp, fp);
		}
		continue;
	    case 'c':
		if (charset && *charset) {
		    /* only output this if we have a charset */
		    fprintf(fp, "<meta http-equiv=\"Content-Type\""
			    " content=\"text/html; charset=%s\" />\n",
			    charset);
		}
		continue;

	    case 'D':		/* %D - date of message */
		if (date) {
		    fprintf(fp,
			    "<meta name=\"Date\" content=\"%s\" />",
			    date);
		}
		continue;
	    case 'e':		/* %e - email address of message author */
		if (email) {
		    for (cp = email; *cp; cp++)
			putc(*cp, fp);
		}
		continue;
	    case 'f':		/* %f - file name */
		if (filename) {
		    for (cp = filename; *cp; cp++)
			putc(*cp, fp);
		}
		continue;
	    case 'g':		/* %g - date and time archive generated */
		for (cp = getlocaltime(); *cp; cp++)
		    putc(*cp, fp);
		continue;
	    case 'G':		/* %G - Language code */
		if (set_language) {
		    for (cp = set_language; *cp; cp++)
			putc(*cp, fp);
		}
		continue;
	    case 'h':		/* %h - Hypermail Resource Center */
		for (cp = HMURL; *cp; cp++)
		    putc(*cp, fp);
		continue;
	    case 'i':		/* %m - Message-ID of message */
		if (message_id) {
		    for (cp = message_id; *cp; cp++)
			putc(*cp, fp);
		}
		continue;
	    case 'l':		/* %l - Archive label  */
		for (cp = label; *cp; cp++)
		    putc(*cp, fp);
		continue;
	    case 'm':		/* %m - mailto */
		if (set_mailto) {
		    for (cp = set_mailto; *cp; cp++)
			putc(*cp, fp);
		}
		continue;
	    case 'p':		/* %p - PROGNAME */
		for (cp = PROGNAME; *cp; cp++)
		    putc(*cp, fp);
		continue;
	    case 's':		/* %s - Subject of message or Index Title */
		for (ptr = cp = convchars(subject, charset); *cp; cp++)
		    putc(*cp, fp);
		free(ptr);
		continue;
	    case 'S':		/* %s - Subject of message or Index Title */
#ifdef HAVE_ICONV
	        tmpptr=i18n_convstring(subject,"UTF-8",charset, &tmplen);
		fprintf(fp, "<meta name=\"Subject\" content=\"%s\" />",
			cp = convchars(tmpptr,charset));
#else
		fprintf(fp, "<meta name=\"Subject\" content=\"%s\" />",
			cp = convchars(subject, charset));
#endif
		free(cp);
		continue;
	    case 't':
	      {
		struct emailinfo *ep;
		if(hashnumlookup(0, &ep))
		    fprintf(fp, ep->subdir ? ep->subdir->rel_path_to_top : "");
		continue;
	      }
	    case 'v':		/* %v - VERSION */
		for (cp = VERSION; *cp; cp++)
		    putc(*cp, fp);
		continue;
	    case 'u':		/* %u - Expanded Version link */
		fprintf(fp, "<a href=\"%s\">%s %s</a>",
			HMURL, PROGNAME, VERSION);
		continue;
	    default:
		putc('%', fp);
		putc(nextone, fp);
		continue;
	    }			/* end switch */
	}
	putc(c, fp);
    }				/* end while */

    fflush(fp);
    return (0);
}