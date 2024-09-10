   void testSupportedAndRequiredFields()
   {
      SipUserAgent sipUA( 5090, 5090, 5091, 
                          NULL, NULL,   // default publicAddress and defaultUser
                         "127.0.0.1" ); 

      // Supported
      CPPUNIT_ASSERT( ! sipUA.isExtensionAllowed( "nope" ) );

      UtlString supported( "supported-1" );
      sipUA.allowExtension( supported );

      UtlString tmp;
      sipUA.getSupportedExtensions( tmp );
      CPPUNIT_ASSERT( supported == tmp );
      supported.toUpper();
      CPPUNIT_ASSERT( sipUA.isExtensionAllowed( supported ) );
      CPPUNIT_ASSERT( ! sipUA.isExtensionAllowed( "nope" ) );


      // Required
      CPPUNIT_ASSERT( ! sipUA.isExtensionRequired( "nope" ) );

      UtlString required( "required-1, required-2, required-3" );
      UtlString copy_required( required );
      copy_required += ',';
      ssize_t prev = 0;
      ssize_t index = copy_required.index( ',', prev );
      while( UTL_NOT_FOUND != index )
      {
         UtlString field = copy_required( prev, index - prev );
         field.strip( UtlString::both );
         sipUA.requireExtension( field );
         prev = index + 1;
         index = copy_required.index( ',', prev );
      }

      sipUA.getRequiredExtensions( tmp );
      CPPUNIT_ASSERT( required == tmp );
      index = copy_required.index( ',', prev );
      while( UTL_NOT_FOUND != index )
      {
         UtlString field = copy_required( prev, index - prev );
         field.strip( UtlString::both );
         field.toUpper();
         CPPUNIT_ASSERT( sipUA.isExtensionRequired( field ) );
         prev = index + 1;
         index = copy_required.index( ',', prev );
      }
      CPPUNIT_ASSERT( ! sipUA.isExtensionRequired( "nope" ) );
   }