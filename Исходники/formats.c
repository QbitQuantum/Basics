void loadmat4(caddr_t nullval)
{
   char inname[150], *temp, *buffer, keyword[30], percentc, *pdchar;
   int bufsize = 256;
   short curcolor = DEFAULTCOLOR;
   char colorstr[100][5];
   short matcolors = 0;
   float curwidth = 1.0;
   int tmpstyle = UNCLOSED;

   sscanf(_STR, "%149s", inname);

   ps = fopen(inname, "r");
   if (ps == NULL) {
      sprintf(inname, "%s.ps", _STR);
      ps = fopen(inname, "r");
      if (ps == NULL) {
	 sprintf(inname, "%s.eps", _STR);
	 ps = fopen(inname, "r");
	 if (ps == NULL) {
	    Wprintf("Can't open Matlab PostScript file %s", inname);
	    return;
         }
      }
   }

   /* Keep same filename---overwriting file is end-user's own risk */

   if ((pdchar = strstr(_STR, ".ps")) != NULL) *pdchar = '\0';
   sprintf(topobject->name, "%s", _STR);
   Wprintf("Loaded file: %s", inname);
   renamepage(areawin->page);
   printname(topobject);

   /* Create input string buffer */

   buffer = (char *)malloc(bufsize * sizeof(char));
   temp = buffer;

   /* Read header information */

   if (fgets(temp, 149, ps) == NULL) {
      Wprintf("Error: end of file.");
      return;
   }
   if (*temp != '%' || *(temp + 1) != '!') {
      Wprintf("Not a PostScript file?");
      return;
   }
   if (fgets(temp, 149, ps) == NULL) {
      Wprintf("Error: end of file.");
      return;
   }
   if (!strstr(temp, "MATLAB")) {
      Wprintf("Not a Matlab PostScript file?");
      return;
   }

   /* Read through to Page start */

   do {
      if (fgets(temp, 149, ps) == NULL) {
         Wprintf("Error: no pages in input.");
         return;
      }
      if (strstr(temp, "%%Page:") != NULL) break;
   } while (1);

   /* Read objects */

   do {
      char *lineptr, keyptr;

      if (fgets(temp, 255, ps) == NULL) break;		/* End-Of-File */
      temp = buffer;

      /* scan from the end;  ignore blank lines. */

      for (lineptr = buffer; (*lineptr != '\n') && (*lineptr != '\0'); lineptr++);

      /* ignore any blank lines and PostScript comment lines */

      if (lineptr != buffer && *buffer != '%') {
         for (keyptr = lineptr - 1; isspace(*keyptr) && keyptr != buffer; keyptr--);
         for (; !isspace(*keyptr) && keyptr != buffer; keyptr--);
         sscanf(keyptr, "%29s", keyword);

	 if (!strcmp(keyword, "showpage")) {
            free(buffer);
            return False;  /* end of page */
         }

	 else if (!strcmp(keyword, "bdef")) {   /* new color definition */
	    char *bb;
	    float red, green, blue;
	    if ((bb = strchr(buffer, '{')) != NULL) {
	       sscanf(bb + 1, "%f %f %f", &red, &green, &blue);
	       curcolor = rgb_alloccolor((int)(red * 65535), (int)(green * 65535),
			(int)(blue * 65535));
	       addnewcolorentry(curcolor);	
	    }
	    if ((bb = strchr(buffer, '/')) != NULL) {
	       sscanf(bb, "%4s", &colorstr[matcolors]);
	       matcolors++;
	    }
	 } 

	 else if (!strcmp(keyword, "w")) {	/* linewidth */
	    float tmpwidth;
	    sscanf(buffer, "%f", &tmpwidth)
	 }
	 else if (!strcmp(keyword, "DO")) {	/* style */
	    tmpstyle = DOTTED | UNCLOSED;
	 }
	 else if (!strcmp(keyword, "SO")) {	/* style */
	    tmpstyle = UNCLOSED;
	 }
	 else if (!strcmp(keyword, "DA")) {	/* style */
	    tmpstyle = DASHED | UNCLOSED;
	 }
	 else if (!strcmp(keyword, "FMSR")) ;   /* ignore font spec for now */
	 else if (!strcmp(keyword, "j")) ;   /* ignore line join */
	 else if (!strcmp(keyword, "def")) ;   /* ignore */
	 else if (!strcmp(keyword, "dictionary")) ;   /* ignore */
	 else if (!strcmp(keyword, "np")) ;   /* ignore clip paths */
	 else {  /* continuation line ? */
	    for (lineptr = buffer; (*lineptr != '\n') && (*lineptr != '\0');
			lineptr++);
	    if (*lineptr == '\n') *lineptr = ' ';

	    bufsize = (int)(lineptr - buffer) + 256;
	    buffer = (char *)realloc(buffer, bufsize * sizeof(char));
	    temp = buffer + (bufsize - 256);
         }
      }