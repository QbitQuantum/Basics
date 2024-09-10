char const* MPEG4ESVideoRTPSink::auxSDPLine() {
  // Generate a new "a=fmtp:" line each time, using parameters from
  // our framer source (in case they've changed since the last time that
  // we were called):
  MPEG4VideoStreamFramer* framerSource = (MPEG4VideoStreamFramer*)fSource;
  if (framerSource == NULL) return NULL; // we don't yet have a source

  u_int8_t profile_level_id = framerSource->profile_and_level_indication();
  if (profile_level_id == 0) return NULL; // our source isn't ready

  unsigned configLength;
  unsigned char* config = framerSource->getConfigBytes(configLength);
  if (config == NULL) return NULL; // our source isn't ready

  char const* fmtpFmt =
    "a=fmtp:%d "
    "profile-level-id=%d;"
    "config=";
  unsigned fmtpFmtSize = strlen(fmtpFmt)
    + 3 /* max char len */
    + 3 /* max char len */
    + 2*configLength /* 2*, because each byte prints as 2 chars */
    + 2 /* trailing \r\n */;
  char* fmtp = new char[fmtpFmtSize];
  sprintf(fmtp, fmtpFmt, rtpPayloadType(), profile_level_id);
  char* endPtr = &fmtp[strlen(fmtp)];
  for (unsigned i = 0; i < configLength; ++i) {
    sprintf(endPtr, "%02X", config[i]);
    endPtr += 2;
  }
  sprintf(endPtr, "\r\n");

  delete[] fAuxSDPLine;
  fAuxSDPLine = strDup(fmtp);
  delete[] fmtp;
  return fAuxSDPLine;
}