Boolean MediaSubsession::parseSDPAttribute_rtpmap(char const* sdpLine) {
  // Check for a "a=rtpmap:<fmt> <codec>/<freq>" line:
  // (Also check without the "/<freq>"; RealNetworks omits this)
  // Also check for a trailing "/<numChannels>".
  Boolean parseSuccess = False;

  // 获取编码类型和时钟频率.
  unsigned rtpmapPayloadFormat;
  char* codecName = strDupSize(sdpLine); // ensures we have enough space
  unsigned rtpTimestampFrequency = 0;
  unsigned numChannels = 1;
  if (sscanf(sdpLine, "a=rtpmap: %u %[^/]/%u/%u",
	     &rtpmapPayloadFormat, codecName, &rtpTimestampFrequency,
	     &numChannels) == 4
      || sscanf(sdpLine, "a=rtpmap: %u %[^/]/%u",
	     &rtpmapPayloadFormat, codecName, &rtpTimestampFrequency) == 3
      || sscanf(sdpLine, "a=rtpmap: %u %s",
		&rtpmapPayloadFormat, codecName) == 2) {
    parseSuccess = True;
    if (rtpmapPayloadFormat == fRTPPayloadFormat) {
      // This "rtpmap" matches our payload format, so set our
      // codec name and timestamp frequency:
      // (First, make sure the codec name is upper case)
      {
	Locale l("POSIX");
	for (char* p = codecName; *p != '\0'; ++p) *p = toupper(*p);
      }
      delete[] fCodecName; fCodecName = strDup(codecName);
      fRTPTimestampFrequency = rtpTimestampFrequency;
      fNumChannels = numChannels;
    }
  }
  delete[] codecName;

  return parseSuccess;
}