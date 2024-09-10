	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		Timestamp now;
		std::string dt(DateTimeFormatter::format(now, DateTimeFormat::SORTABLE_FORMAT));

		response.setChunkedTransferEncoding(true);
		response.setContentType("text/html");

		std::ostream& ostr = response.send();
		ostr << "<html><head><title>TimeServer powered by POCO ApacheConnector</title>";
		ostr << "<meta http-equiv=\"refresh\" content=\"1\"></head>";
		ostr << "<body><p style=\"text-align: center; font-size: 48px;\">";
		ostr << dt;
		ostr << "</p></body></html>";
	}