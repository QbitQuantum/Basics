void
Intrinsics::marshall()
{
   beamBase.marshall();
   HTONL(beamId);
   SseMsg::marshall(pol);

   channelBase.marshall();
   HTONL(totalChannels);
   HTONL(outputChannels);
   HTOND(mhzPerChannel);

   HTONL(foldings);
   HTONF(oversampling);
}