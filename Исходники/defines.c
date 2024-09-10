int   STDCALL os_ustrcmplen( pushort one, pushort two, uint len )
{
 #ifdef LINUX
  int cmp = strncmp(one,two,len);
  if (cmp < 0)
   return -1;
  if (cmp > 0)
   return 1;
 #else
   int cmp = CompareStringW( LOCALE_USER_DEFAULT, 0, one, len, two, len );
   if ( cmp == CSTR_LESS_THAN )
      return -1;
   if ( cmp == CSTR_GREATER_THAN )
      return 1;
 #endif
   return 0;
}