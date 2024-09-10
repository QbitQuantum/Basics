void
ZMLE::MLENUpdate( )
{
#ifdef DEBUG_ALL
   TraceLineS( "ZMLE::MLENUpdate: ", *m_pzsTag );
#endif
   ProcessEvent( this, 2048 );
   Default( );             // pass it along to parent
}