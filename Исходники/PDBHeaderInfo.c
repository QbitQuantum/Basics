/*>char *blGetTitleWholePDB(WHOLEPDB *wpdb)
   ----------------------------------------
*//**
   \param[in]    *wpdb    WHOLEPDB structure
   \return                Tit;le from PDB file (malloc()'d)

   Extracts the title from a PDB file malloc()ing a string in which to
   store the data. This must be freed by user code

-  28.04.15 Original   By: ACRM
-  11.05.15 Return NULL if TITLE line absent. By: CTP
-  09.06.15 Add columns 11 to 80 to title string for both start and 
            continuation lines. By: CTP
*/
char *blGetTitleWholePDB(WHOLEPDB *wpdb)
{
   char       *title = NULL,
              *cleanTitle = NULL;
   STRINGLIST *s;
   BOOL       inTitle = FALSE;

   for(s=wpdb->header; s!=NULL; NEXT(s))
   {
      if(!strncmp(s->string, "TITLE ", 6))
      {
         char buffer[MAXPDBANNOTATION];
         strcpy(buffer, s->string);
         TERMINATE(buffer);

         /* append cols 11-80 to title string                           */
         title = blStrcatalloc(title, buffer+10);

         if(title == NULL)
            return(NULL);
      }
      else if(inTitle)
      {
         break;
      }
   }

   /* title line not found                                              */
   if(title == NULL)
      return(NULL);

   cleanTitle = blCollapseSpaces(title);
   free(title);
   KILLTRAILSPACES(cleanTitle);
   
   return(cleanTitle);
}