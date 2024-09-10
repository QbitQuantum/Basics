// ********************************************************************
// Распечатка карты: краткая информация для прочтения программистом в
// отладочных целях.
// ********************************************************************
void SG_EntryGroup::Print( OFormatter &out ) const
{
 if( key.second==0 )
  out.printf( "%uc -> ", key.first );
 else if( key.third==0 )
  out.printf( "%uc%uc -> ", key.first, key.second );
 else
  out.printf( "%uc%uc%uc -> ", key.first, key.second, key.third );

 const int n=CastSizeToInt(size());
 out.printf( "%d item(s), ", n );

 if( !int1.empty() )
  out.printf( "[%d...%d] ", int1.from, int1.from+int1.n-1 );

 if( !int2.empty() )
  out.printf( "[%d...%d] ", int2.from, int2.from+int2.n-1 );

 if( !ientry.empty() )
  {
   out.printf( "{ " );

   for( Container::size_type i=0; i<ientry.size(); i++ )
    out.printf( "%d ", ientry[i] );

   out.printf( "}" );
  }

 return;
}