 static bool match( Input& in ) noexcept( noexcept( Peek::peek( in ) ) )
 {
    if( const auto r = Peek::peek( in ) ) {
       if( u_getIntPropertyValue( r.data, P ) == V ) {
          in.bump( r.size );
          return true;
       }
    }
    return false;
 }