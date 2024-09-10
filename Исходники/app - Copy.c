BOOL TEST_LOAD_DATABASE(FILE *ptr_file)
{
   BOOL number_flag = TRUE;  
   char buf[DATABASE_LINE_SIZE];
   char *database_temp;
   int  bytecounter = 0;
   BOOL found = FALSE;

   strcpy(databaseblock, "");
   while (!full_buffer)
   //while (fgets(buf, 1000, ptr_file) != NULL)
   {
      if(bytecounter + DATABASE_LINE_SIZE > DATABASE_BLOCK_SIZE)
      {
         full_buffer = TRUE;
		 bytecounter = 0;
      }
      else
      {
         //printf("%s", buf);
		 if(fgets(buf, DATABASE_LINE_SIZE, ptr_file) == NULL){
			 printf("07: Cant read file\n");
			 return FALSE;
		 }
         linecounter++;
         if (found)
         {
           if (strncmp(buf, endMakerdata, EndMarkersize) == 0)
           {
             //printf("[Binh]%s", buf);
             found = FALSE;
           }
           else
           {
              /* get the first token */
              database_temp = strtok(buf, delimiter);
              number_flag = TRUE;
              /* walk through other tokens */
              strcpy(database_line, "");
              while (database_temp != NULL){

                 if (number_flag == FALSE){
                    //printf("%s", database_temp);
                    strcat(database_line, database_temp);
                 }
                 else
                 {
                    number_flag = FALSE;
                 }
                 database_temp = strtok(NULL, delimiter);
              }
              //printf(database_line);
              CovertQuery2Bit(database_line, strlen(database_line),
                              database_convert_byte, strlen(database_line) / 3 + 1);
              //printHexString(database_convert_byte);
			  strncat(databaseblock,database_convert_byte,strlen(database_line));
              bytecounter += strlen(database_line);
           }
        }
        else if (strncmp(buf, startMakerdata, StartMarkersize) == 0){
          //printf("[Binh] %s", buf);
          found = TRUE;
        }
      }
   }
   printHexString(databaseblock);
   full_buffer = FALSE; //reset for next reading
   printf("#line: %d", linecounter);
   return TRUE;
}