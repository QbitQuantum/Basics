OsStatus 
SipRedirectorFallback::determineCallerLocationFromProvisionedUserLocation(
   const SipMessage& message,
   UtlString& callerLocation )
{
   OsStatus result = OS_FAILED;
   callerLocation.remove( 0 );


  // First, determine the identity of the caller.  This is done by looking for
  // a properly signed P-Asserted identity in the request message.
  // If the request contains a P-Asserted-Identity header and is not signed,
  // we will not trust it the returned location will be blank.
  UtlString matchedIdentityHeader;
  SipXauthIdentity sipxIdentity;
  Os::Logger::instance().log(FAC_SIP, PRI_DEBUG, "SipRedirectorFallback:: unbound entities allowing: %s", mAllowUnbound ? "TRUE" : "FALSE");
  if (!mAllowUnbound) {
	  SipXauthIdentity sipxIdentity( message, matchedIdentityHeader, false );
  } else {
	  SipXauthIdentity sipxIdentity( message, matchedIdentityHeader, false, SipXauthIdentity::allowUnbound);
  }

  if( !matchedIdentityHeader.isNull() )
  {

     UtlString authenticatedUserIdentity;
     bool bRequestIsAuthenticated;
     bRequestIsAuthenticated = sipxIdentity.getIdentity( authenticatedUserIdentity );
     if( bRequestIsAuthenticated )
     {
        // we now have the autheticated identity of the caller.  Look up the user location
        // database to find out the location that is mapped to it.
        //ResultSet userLocationsResult;

        // Check in User Location database if user has locations
        //mpUserLocationDbInstance->getLocations( authenticatedUserIdentity, userLocationsResult );

        // Get the caller's site location. Only the first returned location is used.
        // This is not a problem given that a user should only belong to one location.

         EntityRecord entity;
         EntityDB* entityDb = SipRegistrar::getInstance(NULL)->getEntityDB();
         if (entityDb->findByIdentity(authenticatedUserIdentity.str(), entity))
        {

              callerLocation = entity.location().c_str();
              result = OS_SUCCESS;
              Os::Logger::instance().log(FAC_SIP, PRI_DEBUG,
                            "%s::determineCallerLocationFromProvisionedUserLocation mapped user '%s' taken from header '%s' to location '%s' based on its provisioned location",
                            mLogName.data(), authenticatedUserIdentity.data(),
                            authenticatedUserIdentity.data(),
                            entity.location().c_str() );
        }
     }
  }
   return result;
}