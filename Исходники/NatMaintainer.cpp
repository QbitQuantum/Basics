NatMaintainer::NatMaintainer( SipRouter* sipRouter ) :
   mRefreshRoundNumber( 0 ),
   mpRegistrationDB( RegistrationDB::getInstance() ),
   mpSubscriptionDB( SubscriptionDB::getInstance() ),
   mTimerMutex( OsMutex::Q_FIFO ),
   mpSipRouter( sipRouter ),
   mpEndpointsKeptAliveList(
      new KeepAliveEndpointDescriptor[ NUMBER_OF_UDP_PORTS ] ),
   mpKeepAliveMessage( 0 ),
   mExternalKeepAliveListMutex( OsMutex::Q_FIFO )
{
   mTimerMutex.acquire();

   // Build SIP Options message that will be used to keep remote NATed NAT & firewall pinholes open.
   UtlString optionsMessageString =
       "OPTIONS sip:[email protected] SIP/2.0\r\n"
       "To: sip:[email protected]\r\n"
       "From: \"SipXecs Keepalive\"<sip:[email protected]>;tag=30543f3483e1cb11ecb40866edd3295b-reniatniamtan\r\n"
       "Call-ID: f88dfabce84b6a2787ef024a7dbe8749-reniatniamtan\r\n"
       "Cseq: 1 OPTIONS\r\n"
       "Via: SIP/2.0/UDP willgetpatched:5060;branch=z9hG4bK-234fc22f2nnthda-reniatniamtan\r\n"
       "Max-Forwards: 20\r\n"
       "Accept: application/sdp\r\n"
       "Contact: [email protected]\r\n"
       "Content-Length: 0\r\n"
       "\r\n";  
   
   mpKeepAliveMessage = new SipMessage( optionsMessageString, optionsMessageString.length() );

}