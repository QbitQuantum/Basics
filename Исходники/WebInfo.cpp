	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		response.setContentType("text/html");
		response.setChunkedTransferEncoding(true);
		std::ostream& ostr = response.send();

		const std::string& softwareVersion = request.serverParams().getSoftwareVersion();
		LocalDateTime now;

		std::string osName = Environment::osName();
		std::string osDisplayName = Environment::osDisplayName();
		if (osDisplayName != osName)
		{
			osName += " (";
			osName += osDisplayName;
			osName += ")";
		}

		ostr << "<HTML><HEAD><TITLE>Server Information</TITLE>"
		        "<LINK REL=\"stylesheet\" HREF=\"css/styles.css\" TYPE=\"text/css\"/></HEAD><BODY>"
		        "<DIV CLASS=\"header\">"
				"<H1 CLASS=\"category\">Open Service Platform</h1>"
				"<H1 CLASS=\"title\">Server Information</H1>"
				"</DIV>"
		        "<DIV CLASS=\"body\">"
		        "<UL>";
		    
		ostr << "<LI><B>Host:</B> " << Environment::nodeName() << "</LI>"
		     << "<LI><B>Node ID:</B> " << Environment::nodeId() << "</LI>"
		     << "<LI><B>IP Addresses:</B> " << getHostAddresses() << "</LI>"
		     << "<LI><B>OS Name:</B> " << osName << "</LI>"
		     << "<LI><B>OS Version:</B> " << Environment::osVersion() << "</LI>"
		     << "<LI><B>OS Architecture:</B> " << Environment::osArchitecture() << "</LI>"
		     << "<LI><B>Processor Cores:</B> " << Environment::processorCount() << "</LI>"
		     << "<LI><B>Local Server Time:</B> " << DateTimeFormatter::format(now, DateTimeFormat::HTTP_FORMAT) << "</LI>"
		     << "<LI><B>Server Process ID:</B> " << Process::id() << "</LI>";
		   
		ostr << "</UL><HR><P>";
		ostr << htmlize(softwareVersion) << " at " << request.serverAddress().toString();
		ostr << "</P></DIV></BODY></HTML>";
	}