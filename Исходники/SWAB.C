void main(void)
 {
   char *source = "AJSM'A S0110T pi!s";
   char target[64];

   memset(target, NULL, sizeof(target));  

   swab(source, target, strlen(source));

   printf("Source: %s Target %s\n", source, target);
 }