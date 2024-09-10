char const*
H264MediaSubsession::sdpLines() {
  if (fSDPLines == NULL) {
	AddressString ipAddressStr(fServerAddressForSDP);
	const char* rtpmapLine = "a=rtpmap:96 H264/90000\r\n";
	char const* rangeLine = rangeSDPLine();
	char const* const sdpFmt =
	"m=%s %u RTP/AVP %d\r\n"
	"c=IN IP4 %s\r\n"
	"b=AS:%u\r\n"
	"%s"
	"%s"
	"%s"
	"a=control:%s\r\n";
	unsigned sdpFmtSize = strlen(sdpFmt)
	+ strlen(mediaType) + 5 /* max short len */ + 3 /* max char len */
	+ strlen(ipAddressStr.val())
	+ 20 /* max int len */
	+ strlen(rtpmapLine)
	+ strlen(rangeLine)
	+ strlen(auxSDPLine())
	+ strlen(trackId());
	char* sdpLines = new char[sdpFmtSize];
	sprintf(sdpLines, sdpFmt,
		mediaType, // m= <media>
		fPortNumForSDP, // m= <port>
		rtpPayloadType, // m= <fmt list>
		ipAddressStr.val(), // c= address
		m_Watcher->GetVideoBitrate(), // b=AS:<bandwidth>
		rtpmapLine, // a=rtpmap:... (if present)
		rangeLine, // a=range:... (if present)
		auxSDPLine(), // optional extra SDP line
		trackId()); // a=control:<track-id>
	
	delete[] (char*)rangeLine; 
	
	fSDPLines = strDup(sdpLines);
	delete[] sdpLines;
  }

  return fSDPLines;
}