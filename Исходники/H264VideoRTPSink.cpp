H264VideoRTPSink
::H264VideoRTPSink(UsageEnvironment& env, Groupsock* RTPgs,
                   unsigned char rtpPayloadFormat,
                   unsigned profile_level_id,
                   char const* sprop_parameter_sets_str)
    : VideoRTPSink(env, RTPgs, rtpPayloadFormat, 90000, "H264"),
      fOurFragmenter(NULL) {
    // Set up the "a=fmtp:" SDP line for this stream:
    char const* fmtpFmt =
        "a=fmtp:%d packetization-mode=1"
        ";profile-level-id=%06X"
        ";sprop-parameter-sets=%s\r\n";
    unsigned fmtpFmtSize = strlen(fmtpFmt)
                           + 3 /* max char len */
                           + 8 /* max unsigned len in hex */
                           + strlen(sprop_parameter_sets_str);
    char* fmtp = new char[fmtpFmtSize];
    sprintf(fmtp, fmtpFmt,
            rtpPayloadFormat,
            profile_level_id,
            sprop_parameter_sets_str);
    fFmtpSDPLine = strDup(fmtp);
    delete[] fmtp;
}