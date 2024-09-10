int EE_Evaluate( char* e, double* result, int* a )
{
   //if( setjmp( jb ) )
   //   return( ERROR );
   expression = e;
   ERANC = e;
   STRLWR( expression );
   *result = 0;
   Parse();
   if( ! *token )
      return ( E_EMPTY );
   *a = Level1( result );
   return( E_OK );
}