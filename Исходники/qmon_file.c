char *qmonReadText(const char *filename, lList **alpp)
{
   char *text = NULL;
   SGE_STRUCT_STAT statb;
   FILE *fp = NULL;

   DENTER(GUI_LAYER, "qmonReadText");

   if (filename == NULL) {
      answer_list_add_sprintf(alpp, STATUS_ESYNTAX, ANSWER_QUALITY_ERROR,
                              "No filename specified");
      DRETURN(NULL);
   }

   /* 
   ** make sure the file is a regular text file and open it 
   */
   if (SGE_STAT(filename, &statb) == -1 
       || (statb.st_mode & S_IFMT) != S_IFREG 
       || !(fp = fopen(filename, "r"))) {
      answer_list_add_sprintf(alpp, STATUS_ESYNTAX, ANSWER_QUALITY_ERROR,
                      MSG_FILE_OPENFAILED_S, filename);
      DRETURN(NULL);
   }

   /* 
   ** put the contents of the file in the Text widget by allocating
   ** enough space for the entire file, reading the file into the
   ** allocated space, and using XmTextFieldSetString() to show the file.
   */
   if ((text = XtMalloc((unsigned)(statb.st_size + 1))) == NULL) {
      answer_list_add_sprintf(alpp, STATUS_ESYNTAX, ANSWER_QUALITY_ERROR,
                              "%s", MSG_MEMORY_MALLOCFAILED);
      FCLOSE(fp);
      DRETURN(NULL);
   }

   if (!fread(text, sizeof (char), statb.st_size + 1, fp)) {
      answer_list_add_sprintf(alpp, STATUS_ESYNTAX, ANSWER_QUALITY_ERROR,
                              MSG_FILE_FREADFAILED_SS, filename, strerror(errno));
   }

   text[statb.st_size] = 0; /* be sure to NULL-terminate */

   FCLOSE(fp);
   DRETURN(text);

FCLOSE_ERROR:
   XtFree(text);
   answer_list_add_sprintf(alpp, STATUS_ESYNTAX, ANSWER_QUALITY_ERROR,
                           MSG_FILE_NOCLOSE_SS, filename, strerror(errno));
   DRETURN(NULL);
}