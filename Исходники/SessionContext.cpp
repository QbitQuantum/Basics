bool SessionContext::getMediaRelayAddressToUseInSdp( UtlString& mediaRelayAddressToUse, EndpointRole endpointRole ) const
{
   bool bUseNativeMediaRelayIpAddress = false;

   mediaRelayAddressToUse.remove( 0 );
   if( mpMediaRelay->isPartOfsipXLocalPrivateNetwork() )
   {
      // if both the receiver of the SDP and the media relay are located with the
      // same network, use the media relay's native IP address in the SDP, otherwise
      // use its public.
      EndpointDescriptor* pSdpRecipient = ( endpointRole == CALLER ? mpCallee : mpCaller );
      if( pSdpRecipient->getLocationCode() == LOCAL_NATED )
      {
         mediaRelayAddressToUse = mpMediaRelay->getNativeAddress();
         bUseNativeMediaRelayIpAddress = true;
      }
      else
      {
         mediaRelayAddressToUse = mpMediaRelay->getPublicAddress();
      }
   }
   else
   {
      mediaRelayAddressToUse = mpMediaRelay->getPublicAddress();
   }
   return bUseNativeMediaRelayIpAddress;
}