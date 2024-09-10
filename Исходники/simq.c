/*>void WriteJobFile(char *queueDir, int pid, char **progArgs, 
                     int nProgArgs)
   -----------------------------------------------------------
*//**
   \param[in]  *queueDir    queue directory
   \param[in]  pid          job number
   \param[in]  **progArgs   Program and arguments in an array
   \param[in]  nProgArgs    Number of items in progArgs

   Creates a job file

-  16.10.15  Original   By: ACRM
*/
void WriteJobFile(char *queueDir, int pid, char **progArgs, int nProgArgs)
{
   char jobFile[MAXBUFF],
        pwd[MAXBUFF];
   FILE *fp;


   sprintf(jobFile, "%s/%d", queueDir, pid);
   getcwd(pwd, MAXBUFF);
   TERMINATE(pwd);

   if((fp=fopen(jobFile, "w"))!=NULL)
   {
      int i;
      fprintf(fp, "%s\n", pwd);
      for(i=0; i<nProgArgs; i++)
      {
         fprintf(fp, "%s ", progArgs[i]);
      }
      fprintf(fp, "\n");
      fclose(fp);
   }
   else
   {
      char msg[MAXBUFF];
      sprintf(msg,"Unable to create job file %s", jobFile);
      Message(PROGNAME, MSG_FATAL, msg);
   }
}