int main(int argc, char *argv[])
{
   char buf[LINE_LEN];              
   /* word string buffer */
   char fileName[LINE_LEN];         
   /* file name buffer */
   int howManyBins;                 
   /* number of bins to create */
   TABLE *hashTable;                
   /* pointer to hash table */
   FILE *fp;

   /* Read file name from command line */
   if (argc < MIN_ARGS || sscanf(argv[FILE_ARG_IX], BUFFMT "s", fileName) != 1)
   {
      fprintf(stderr, "No file name specified on command line\n");
      return EXIT_FAILURE;
   }
   fp = OpenFile(fileName);

   /* Read bin count from command line */
   if (sscanf(argv[BINS_ARG_IX], "%d", &howManyBins) != 1)
   {
      fprintf(stderr, "No bin count specified on command line\n");
      return EXIT_FAILURE;
   }
   hashTable = CreateTable((size_t)howManyBins);  
   /* allocate table array */

   /*
    * The following loop will read one string at a time from stdin until
    * EOF is reached.  For each string read the BuildList function will
    * be called to update the hash table.
    */
   while (fscanf(fp, BUFFMT "s", buf) != EOF) 
   /* get string from file */
   {
      /* find appropriate bin */
      BIN *bin = &hashTable->firstBin[HashFunction(buf, (size_t)howManyBins)];
      NODE *newStart = BuildTree(bin->firstNode, buf, bin);                   
      /* put string in list */
      bin->firstNode = newStart;
   }
   fclose(fp);
   PrintTable(hashTable);                    
   /* print all strings */
   FreeTable(hashTable);                     
   /* free the table */
   return(EXIT_SUCCESS);
}