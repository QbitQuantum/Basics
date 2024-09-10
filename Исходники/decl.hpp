 CallStackEntry( string s ) 
 { 
     if( !uncaught_exception() )
         PushCallStack(s); 
 }