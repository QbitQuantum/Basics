int main( int argc, char*argv[] ) {
   LOG_NOTICE( "Test Started" );

   URI u;

   u.setScheme( "http" );
   u.setAuthority( "www.jetheaddev.com" );
   u.setPath( "pages/index.html" );

   string ustr = u.getString();
   LOG_NOTICE( "URI is: %s", ustr.c_str() );

   for (uint32_t i = 0; i < ARRAY_SIZE( test_urls ); i++) {
      bool res = u.setString( test_urls[i] );

#ifdef DEBUG_PRINTS
      cout << "scheme: " << u.getScheme() << endl;
      cout << "authority: " << u.getAuthority() << endl;
      cout << "host: " << u.getHost() << endl;
      cout << "port: " << u.getPort() << endl;
      cout << "query: " << u.getQuery() << endl;
      cout << "path: " << u.getPath() << endl;
      cout << "fragment: " << u.getFragment() << endl;
      cout << "query param \"c\": " << u.getQueryParam( "c" ) << endl;
      cout << "query param \"e\": " << u.getQueryParam( "e" ) << endl;
      cout << "is relative: " << u.isRelative() << endl;
#endif

      if ( not res ) {
         LOG_WARN( "parse uri %s: FAILED", test_urls[i] );
         exit( 1 );
      } else {
         LOG_NOTICE( "parse uri %s: PASSED", test_urls[ i ] );
      }
   }

   u.clear();
   u.setScheme( "http" );
   u.setAuthority( "www.jetheaddev.com" );
   u.setPath( "pages/index.html" );
   u.appendQueryParam( "a", "b" );
   u.appendQueryParam( "c", "d" );
   u.setFragment( "m" );

   URI copy = u;

   ustr = u.getString();
   LOG_NOTICE( "URI is: %s", ustr.c_str() );
   ustr = copy.getString();
   LOG_NOTICE( "Copy is: %s", ustr.c_str() );

#ifdef DEBUG_PRINTS
   cout << "scheme: " << u.getScheme() << endl;
   cout << "scheme: " << copy.getScheme() << endl;
   cout << "authority: " << u.getAuthority() << endl;
   cout << "authority: " << copy.getAuthority() << endl;
   cout << "host: " << u.getHost() << endl;
   cout << "host: " << copy.getHost() << endl;
   cout << "port: " << u.getPort() << endl;
   cout << "port: " << copy.getPort() << endl;
   cout << "query: " << u.getQuery() << endl;
   cout << "query: " << copy.getQuery() << endl;
   cout << "path: " << u.getPath() << endl;
   cout << "path: " << copy.getPath() << endl;
   cout << "fragment: " << u.getFragment() << endl;
   cout << "fragment: " << copy.getFragment() << endl;
   cout << "query param \"a\": " << u.getQueryParam( "a" ) << endl;
   cout << "query param \"a\": " << copy.getQueryParam( "a" ) << endl;
   cout << "query param \"c\": " << u.getQueryParam( "c" ) << endl;
   cout << "query param \"c\": " << copy.getQueryParam( "c" ) << endl;
   cout << "is relative: " << u.isRelative() << endl;
   cout << "is relative: " << copy.isRelative() << endl;
#endif

   if ( u.getScheme() != copy.getScheme()
         or u.getAuthority() != copy.getAuthority()
         or u.getQuery() != copy.getQuery() or u.getPath() != copy.getPath()
         or u.getFragment() != copy.getFragment()
         or u.getQueryParam( "a" ) != copy.getQueryParam( "a" )
         or u.getQueryParam( "c" ) != copy.getQueryParam( "c" )
         or u.isRelative() != copy.isRelative() ) {
      LOG_WARN( "copy of uri: FAILED" );
   } else {
      LOG_NOTICE( "copy of uri: PASSED" );
   }

   return 0;
}