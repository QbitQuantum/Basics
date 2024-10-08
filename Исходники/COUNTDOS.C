void main(void)
 {
   int i;

   // Zero the function counts
   for (i = 0; i < 255; i++)
     function[i] = 0;

   original_handler = _dos_getvect(0x21);
   _disable();
   _dos_setvect(0x21, handler);
   _enable();

   printf("This is a message\n");
   fprintf(stdout, "This is a second message\n");

   printf("Current disk is %c\n", getdisk() + 'A');

   _disable();
   _dos_setvect(0x21, original_handler);
   _enable();


   for (i = 0; i <= 255; i++)
     if (function[i])
       printf("Function %x called %d times\n", i, function[i]);
 }