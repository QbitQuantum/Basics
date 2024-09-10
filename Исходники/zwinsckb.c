void TraceLineI( LPSTR psz1, LONG l )
{
   char szL[ 10 ];

   _ltoa( l, szL, 10 );
   TraceLineS( psz1, szL );
}