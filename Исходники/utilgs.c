int main(int argc, char **argv) {
   char *p;
   char buf[1024];
   int i;
   fileType *ft;

   if (argc!=2) return -1;

   ft = getFileType(argv[1]);
   if (ft == NULL) {
      perror(argv[1]);
      exit(1);
   } else {
      printf("type =    %x\nauxtype = %lx\n",ft->type,ft->auxtype);
   }
   return 0;
}