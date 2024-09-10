SimpleRTPSink::SimpleRTPSink(UsageEnvironment& env, Groupsock* RTPgs,
			     unsigned char rtpPayloadFormat,
			     unsigned rtpTimestampFrequency,
			     char const* sdpMediaTypeString,
			     char const* rtpPayloadFormatName,
			     unsigned numChannels,
			     Boolean allowMultipleFramesPerPacket,
			     Boolean doNormalMBitRule)
  : MultiFramedRTPSink(env, RTPgs, rtpPayloadFormat,
		       rtpTimestampFrequency, rtpPayloadFormatName,
		       numChannels),
    fAllowMultipleFramesPerPacket(allowMultipleFramesPerPacket) {
  fSDPMediaTypeString
    = strDup(sdpMediaTypeString == NULL ? "unknown" : sdpMediaTypeString);
  fSetMBitOnLastFrames = doNormalMBitRule && strcmp(fSDPMediaTypeString, "audio") != 0;
}