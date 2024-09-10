FILE *findfontfile(const char *fontname)
{
   int i;
   char tempname[256];
   FILE *fd;

   /* Add subdirectory "fonts".  We will try both with and	*/
   /* without the subdirectory.					*/

   sprintf(_STR, "fonts/%s", fontname);

   /* change string to all lowercase and remove dashes */

   for (i = 0; i < strlen(_STR); i++) {
      _STR[i] = tolower(_STR[i]);
      if (_STR[i] == '-') _STR[i] = '_';
   }

   /* Fprintf(stdout, "Searching for font file \"%s\"\n", _STR); */

   /* Use the mechanism of "libopen" to find the encoding file	*/
   /* in the search path					*/

   fd = libopen(_STR + 6, FONTENCODING);

   if (fd == NULL) fd = libopen(_STR, FONTENCODING);

   /* Some other, probably futile, attempts (call findfontfile recursively) */

   if (fd == NULL) {
      char *dashptr;

      /* If this font has a suffix, remove it and look for its root */
      /* font on the supposition that this font is derived from the */
      /* root font.						    */

      strncpy(tempname, fontname, 99);
      if ((dashptr = strrchr(tempname, '-')) != NULL) {
	 *dashptr = '\0';
	 if ((fd = findfontfile(tempname)) != NULL) return fd;

	 /* And finally, because it's a common case, try adding	*/
	 /* -Roman and trying again (but don't infinite loop!)	*/

	 if (strcmp(dashptr + 1, "Roman")) {
	    strcat(dashptr, "-Roman");
	    if ((fd = findfontfile(tempname)) != NULL) return fd;
	 }
      }

      Wprintf("No font encoding file found.");
      if (fontcount > 0) {	/* Make font substitution */
	 char *dchr, *psname = NULL;
	 short fval;

	 if ((dchr = strrchr(_STR, '.')) != NULL) *dchr = '\0';
	 if ((fval = findhelvetica()) == fontcount) {
	    /* This will cause some chaos. . . */
	    Fprintf(stderr, "Error:  No fonts available!  Check library path?\n");
            qApp->exit(1);
            return NULL;
	 }

	 psname = (char *)malloc((1 + strlen(fontname)) * sizeof(char));
	 strcpy(psname, fontname);
	 Wprintf("No encoding file found for font %s: substituting %s",
			psname, fonts[fval].psname);
         fonts = (fontinfo *)realloc(fonts, (fontcount + 1) * sizeof(fontinfo));
         fonts[fontcount].psname = psname;
         fonts[fontcount].family = psname;
         fonts[fontcount].encoding = fonts[fval].encoding;
         fonts[fontcount].flags = 0; 
         fonts[fontcount].scale = 1.0;
         fontcount++;
	 makenewfontbutton();
      }
      else {
	 Fprintf(stderr, "Error:  font encoding file missing for font \"%s\"\n",
		fontname);
	 Fprintf(stderr, "No fonts exist for a subsitution.  Make sure "
		"fonts are installed or that\nenvironment variable "
		"XCIRCUIT_LIB_DIR points to a directory of valid fonts.\n");
      }
      return (FILE *)NULL;
   }
   return fd;
}