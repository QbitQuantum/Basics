int main(int argc, char **argv)
{
   char *p;
   char dt[1000];
   int status = 0;

   if (argc < 2) {
      p = (argc < 1) ? "drivetype" : argv[0];
      printf("usage:\t%s path ...\n"
            "\t%s prints the drive type and pathname of the paths.\n",
            p, p);
      return EXIT_FAILURE;
   }
   while (*++argv) {
      if (!drivetype(*argv, dt, sizeof(dt))) {
         status = EXIT_FAILURE;
      } else {
         printf("%s\t%s\n", dt, *argv);
      }
   }
   return status;
}