main(int argc, char *argv[]) {
   FILE *fp;
   int nl = 1;
   char line[512];

   if((fp = fopen(argv[1], "r")) == NULL) {
     printf("Plik nie istnieje lub wystąpił problem z jego odczytem.");
     return(-1);
   }

   while(fgets(line, sizeof(line), fp) != NULL) {
	 if(strStr(line, argv[2])) {
		printf("%d -> %s\n", nl, line);
     }
     nl++;
   }

   if(fp) {
  	 fclose(fp);
   }

   return(0);
}