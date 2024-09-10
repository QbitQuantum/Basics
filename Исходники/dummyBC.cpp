static void closeOnSignal( int sig )
{
   printf( "signal %d\n", sig );
   closeHandle();
}