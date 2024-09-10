/*      Output parent directory entry
**
**    This gives the TITLE and H1 header, and also a link
**    to the parent directory if appropriate.
*/
PUBLIC void HTDirTitles ARGS2(HTStructured *, target,
		 HTAnchor * , anchor)

{
    char * logical = HTAnchor_address(anchor);
    char * path = HTParse(logical, "", PARSE_PATH + PARSE_PUNCTUATION);
    char * current;

    current = strrchr(path, '/');	/* last part or "" */
    free(logical);

    {
      char * printable = NULL;
      StrAllocCopy(printable, (current + 1));
      HTUnEscape(printable);
      START(HTML_TITLE);
      PUTS(*printable ? printable : "Welcome ");
      PUTS(" directory");
      END(HTML_TITLE);    
    
      START(HTML_H1);
      PUTS(*printable ? printable : "Welcome");
      END(HTML_H1);
      free(printable);
    }

    /*  Make link back to parent directory
     */

    if (current && current[1]) {   /* was a slash AND something else too */
        char * parent;
	char * relative;
	*current++ = 0;
      parent = strrchr(path, '/');  /* penultimate slash */

	relative = (char*) malloc(strlen(current) + 4);
	if (relative == NULL) outofmem(__FILE__, "DirRead");
	sprintf(relative, "%s/..", current);
        PUTS ("<A HREF=\"");
        PUTS (relative);
        PUTS ("\">");
	free(relative);

	PUTS("Up to ");
	if (parent) {
	  char * printable = NULL;
	  StrAllocCopy(printable, parent + 1);
	  HTUnEscape(printable);
	  PUTS(printable);
	  free(printable);
	} else {
	  PUTS("/");
	}

        PUTS("</A>");
      }
    free(path);
}