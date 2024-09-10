IppTransport::~IppTransport()
{
	string error_msg;

	if (!__error && __fs.good()) {
		DBGMSG(("create IppContent\n"));
		IppContent *request = new IppContent;
		request->setOperationId(IPP_PRINT_JOB);
		request->setDelimiter(IPP_OPERATION_ATTRIBUTES_TAG);
		request->setCharset("attributes-charset", "utf-8");
		request->setNaturalLanguage("attributes-natural-language", "en-us");
		request->setURI("printer-uri", __url);
		request->setMimeMediaType("document-format", "application/octet-stream");
		request->setNameWithoutLanguage("requesting-user-name", __user);
//		request->setNameWithoutLanguage("job-name", __file);	// optional
		request->setDelimiter(IPP_END_OF_ATTRIBUTES_TAG);

		long fssize = __fs.tellg();
		__fs.seekg(0, ios::beg);
		request->setRawData(__fs, fssize);

		URL url(__url);
		IppURLConnection conn(url);
		conn.setIppRequest(request);
		conn.setRequestProperty("Connection", "close");

		DBGMSG(("do connect\n"));

		HTTP_RESPONSECODE response_code = conn.getResponseCode();
		if (response_code == HTTP_OK) {
			const char *content_type = conn.getContentType();
			if (content_type && !strncasecmp(content_type, "application/ipp", 15)) {
				const IppContent *ipp_response = conn.getIppResponse();
				if (ipp_response->fail()) {
					__error = true;
					error_msg = ipp_response->getStatusMessage();
				}
			} else {
				__error = true;
				error_msg = "cannot get a IPP response.";
			}
		} else if (response_code != HTTP_UNKNOWN) {
			__error = true;
			error_msg = conn.getResponseMessage();
		} else {
			__error = true;
			error_msg = "cannot connect to the IPP server.";
		}
	}

	unlink(__file);

	if (__error) {
		BAlert *alert = new BAlert("", error_msg.c_str(), "OK");
		alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
		alert->Go();
	}
}