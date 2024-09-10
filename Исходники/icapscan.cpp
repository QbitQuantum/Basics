// send ICAP request headers, returning success or failure
bool icapinstance::doHeaders(Socket & icapsock, HTTPHeader *reqheader, HTTPHeader *respheader, unsigned int objectsize)
{
	int rc = icapsock.connect(icapip.toCharArray(), icapport);
	if (rc) {
#ifdef DGDEBUG
		std::cerr << "Error connecting to ICAP server" << std::endl;
#endif
		lastmessage = "Error connecting to ICAP server";
		syslog(LOG_ERR, "Error connecting to ICAP server");
		return false;
	}
	char objectsizehex[32];
	// encapsulated HTTP request header:
	// use a dummy unless it proves absolutely necessary to do otherwise,
	// as using real data could lead to e.g. yet another source of password
	// leakage over the network.
	String encapsulatedheader("GET " + reqheader->getUrl() + " HTTP/1.0\r\n\r\n");
	// body chunk size in hex - either full body, or just preview
	if (usepreviews && (objectsize > previewsize)) {
		snprintf(objectsizehex, sizeof(objectsizehex), "%x\r\n", previewsize);
	} else {
		snprintf(objectsizehex, sizeof(objectsizehex), "%x\r\n", objectsize);
	}
	// encapsulated HTTP response header:
	// use real data, because scanners can use this to aid the process
	/*String httpresponseheader;
	for (std::deque<String>::iterator i = respheader->header.begin(); i != respheader->header.end(); i++) {
		httpresponseheader += (*i) + "\r\n";
	}
	httpresponseheader += "\r\n";*/
	String httpresponseheader("HTTP/1.0 200 OK\r\n\r\n");
	// ICAP header itself
	String icapheader("RESPMOD " + icapurl + " ICAP/1.0\r\nHost: " + icaphost + "\r\nAllow: 204\r\nEncapsulated: req-hdr=0, res-hdr=" + String(encapsulatedheader.length()) + ", res-body=" + String(httpresponseheader.length() + encapsulatedheader.length()));
	if (usepreviews && (objectsize > previewsize)) {
		icapheader += "\r\nPreview: " + String(previewsize);
	}
	icapheader += "\r\n\r\n";

#ifdef DGDEBUG
	std::cerr << "About to send icapheader:\n" << icapheader << encapsulatedheader << httpresponseheader << objectsizehex << std::endl;
#endif
	try {
		icapsock.writeString(icapheader.toCharArray());
		icapsock.writeString(encapsulatedheader.toCharArray());
		icapsock.writeString(httpresponseheader.toCharArray());
		icapsock.writeString(objectsizehex);
	}
	catch(std::exception & e) {
#ifdef DGDEBUG
		std::cerr << "Exception sending headers to ICAP: " << e.what() << std::endl;
#endif
		lastmessage = "Exception sending headers to ICAP";
		syslog(LOG_ERR, "Exception sending headers to ICAP: %s", e.what());
		return false;
	}
	return true;
}