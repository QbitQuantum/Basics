RTPSink::RTPSink(UsageEnvironment& env,
		 Groupsock* rtpGS, unsigned char rtpPayloadType,
		 unsigned rtpTimestampFrequency,
		 char const* rtpPayloadFormatName,
		 unsigned numChannels)
  : MediaSink(env), fRTPInterface(this, rtpGS),
    fRTPPayloadType(rtpPayloadType),
    fPacketCount(0), fOctetCount(0), fTotalOctetCount(0),
    fTimestampFrequency(rtpTimestampFrequency), fNextTimestampHasBeenPreset(True),
    fNumChannels(numChannels) {
  fRTPPayloadFormatName
    = strDup(rtpPayloadFormatName == NULL ? "???" : rtpPayloadFormatName);
  gettimeofday(&fCreationTime, NULL);
  fTotalOctetCountStartTime = fCreationTime;

  fSeqNo = (u_int16_t)our_random();
  fSSRC = our_random32();
  fTimestampBase = our_random32();

  fTransmissionStatsDB = new RTPTransmissionStatsDB(*this);
}