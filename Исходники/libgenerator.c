int main(int argc, char *argv[])
{
   char *prefix;
   FILE *f;
   int size;

   if (argc != 4) {
      fprintf(stderr, "Argument error\n");
      return -1;
   }
      
   f = fopen(argv[1], "w");
   if (!f) {
      fprintf(stderr, "Failed to open %s: %s\n", argv[2], strerror(errno));
      return -1;
   }
   size = atoi(argv[2]);
   prefix = argv[3];

   writeFile(f, prefix, size);
   return 0;
}