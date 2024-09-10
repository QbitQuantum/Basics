int main()
{
   size_t result;

   char mbstring[ ] = "This is originally a multibyte string.\n";
   const char *mbsptr = mbstring;

   wchar_t widestring[256] = { L'\0' };

   mbstate_t state;
   memset( &state, '\0', sizeof state );

   printf( "The current locale is %s.\n", setlocale( LC_CTYPE, "" ));

   result = mbsrtowcs( widestring, &mbsptr, 256, &state );
   if ( result == (size_t)-1 )
   {
      fputs( "Encoding error in multibyte string", stderr );
      return -1;
   }
   else
   {
      printf( "Converted %u multibyte characters. The result:\n", result );
      printf( "%ls", widestring );
   }
   return 0;
}