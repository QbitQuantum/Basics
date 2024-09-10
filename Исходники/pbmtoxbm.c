static void
generateName(char const filenameArg[], const char ** const nameP) {
/*----------------------------------------------------------------------------
   Generate a name for the image to put in the bitmap file.  Derive it from
   the filename argument filenameArg[] and return it as a null-terminated
   string in newly malloc'ed space at *nameP.

   We take the part of the name after the rightmost slash
   (i.e. filename without the directory path part), stopping before
   any period.  We convert any punctuation to underscores.

   If the argument is "-", meaning standard input, we return the name
   "noname".  Also, if the argument is null or ends in a slash, we
   return "noname".
-----------------------------------------------------------------------------*/
    if (strcmp(filenameArg, "-") == 0) 
        *nameP = strdup("noname");
    else {
        int nameIndex, argIndex;
        /* indices into the input and output buffers */

        /* Start just after the rightmost slash, or at beginning if no slash */
        if (strrchr(filenameArg, '/') == 0) 
            argIndex = 0;
        else argIndex = strrchr(filenameArg, '/') - filenameArg + 1;

        if (filenameArg[argIndex] == '\0') 
            *nameP = strdup("noname");
        else {
            char * name;
            nameIndex = 0;  /* Start at beginning of name buffer */

            name = malloc(strlen(filenameArg));
    
            while (filenameArg[argIndex] != '\0' 
                   && filenameArg[argIndex] != '.') {
                const char filenameChar = filenameArg[argIndex++];
                name[nameIndex++] = 
                    ISALNUM(filenameChar) ? filenameChar : '_';
            }
            name[nameIndex] = '\0';
            *nameP = name;
        }
    }
}