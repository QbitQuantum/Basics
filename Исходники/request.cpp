 static bool isUsAscii( const QString & s ) {
   for ( int i = 0 ; i < s.length() ; ++i )
     if ( s[i].unicode() > 127 ) return false;
   return true;
 }