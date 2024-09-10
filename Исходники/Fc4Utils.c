_TCHAR * get_nice_number( __int64 num, size_t width )
{
   size_t len, i;
   _TCHAR * pb1 = get_next_buffer();
   _TCHAR * pb2 = get_next_buffer();
   SPRINTF(pb1, "%lld", num);
   nice_num( pb2, pb1 );
   len = STRLEN(pb2);
   if( len < width )
   {
      *pb1 = 0;
      i = width - len;  // get pad
      while(i--)
         STRCAT(pb1, " ");
      STRCAT(pb1,pb2);
      pb2 = pb1;
   }
   return pb2;
}