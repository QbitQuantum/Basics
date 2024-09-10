bool NatTraversalRules::StunClient::getPublicIpAddress( UtlString& discoveredPublicIpAddress )
{
   bool rc = false;

   // Not yet resolved the STUN server to a valid IP address, try again in case
   // network conditions have cleared.
   if( !mbStunServerIsValid )
   {
      mbStunServerIsValid = stunQueryAgent.setServer( mStunServerName );
   }

   if( mbStunServerIsValid )
   {
      UtlString mappedAddress;
      int  mappedPort;
      OsTime timeout( STUN_QUERY_TIMEOUT_IN_MILLISECS );

      rc = stunQueryAgent.getMappedAddress( &mSocket, mappedAddress, mappedPort, 0, timeout );
      if( rc )
      {
         discoveredPublicIpAddress = mappedAddress;
         Os::Logger::instance().log(FAC_NAT,PRI_INFO,"StunClient::getPublicIpAddress obtained public IP address %s from server %s", mappedAddress.data(), mStunServerName.data() );
      }
      else
      {
         discoveredPublicIpAddress.remove( 0 );
         Os::Logger::instance().log(FAC_NAT,PRI_ERR,"StunClient::getPublicIpAddress failed to obtain mapping from server %s", mStunServerName.data() );
      }
   }
   return rc;
}