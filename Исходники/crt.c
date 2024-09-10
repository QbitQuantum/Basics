void _cdecl wr_counter(dword ctr, int col, int row, int Fcolor, int Bcolor, int radix)
{
#if (DEVICE_CONSOLE_OUT)

   char  buffer[11];
   uint  i, j;

   ENTER_CLIB();
   _ultoa(ctr, buffer, radix);
   EXIT_CLIB();

   for(i = 0; buffer[i] && i < 6; i++) {}  /* find end of string */
   for(; i < 6; i++)                       /* right align */
   {
      for(j = i+1; j > 0; j--)
         buffer[j] = buffer[j-1];
      buffer[j] = '0';
   }

   wr_string(col,row,Fcolor,Bcolor,!BLINK,buffer);

#else
   /* Avoid compiler warning about unused pars. */
   (void) ctr;
   (void) col;
   (void) row;
   (void) Fcolor;
   (void) Bcolor;
   (void) radix;

#endif /* DEVICE_CONSOLE_OUT */
}