void AppRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	// Check for the favicon.ico request, we don't have one for now,
	// so set status code to HTTP_NOT_FOUND
	if ( request.getURI().compare("/favicon.ico") == 0 )
	{
		response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
		response.send();
		return;
	}

	std::string lastModifiedHeader = request.get("If-Modified-Since", "");

	Poco::URI uri(request.getURI());

	Poco::Util::Application& app = Poco::Util::Application::instance();
	std::string staticPathname = app.config().getString("mq.web.app", "");
	if ( staticPathname.empty() )
	{
		Poco::Logger& logger = Poco::Logger::get("mq.web");
		logger.error("mq.web.app property not defined. Check your configuration.");
		response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
		response.send();
		return;
	}

	Poco::Path staticPath(staticPathname);
	staticPath.makeDirectory();

	std::vector<std::string> uriPathSegments;
	uri.getPathSegments(uriPathSegments);
	std::vector<std::string>::iterator it = uriPathSegments.begin();
	it++;
	for(; it != uriPathSegments.end(); ++it)
	{
		staticPath.append(*it);
	}
	if (staticPath.isDirectory())
	{
		staticPath.append("index.html");
	}

	Poco::File staticFile(staticPath);

	Poco::Logger& logger = Poco::Logger::get("mq.web.access");
	if ( staticFile.exists() )
	{
		if ( !lastModifiedHeader.empty() )
		{
			Poco::DateTime lastModifiedDate;
			int timeZoneDifferential = 0;
			if ( Poco::DateTimeParser::tryParse(Poco::DateTimeFormat::HTTP_FORMAT, lastModifiedHeader, lastModifiedDate, timeZoneDifferential) )
			{
				if ( staticFile.getLastModified() <= lastModifiedDate.timestamp() )
				{
					logger.information(Poco::Logger::format("$0 : HTTP_NOT_MODIFIED", staticPath.toString()));
					response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_MODIFIED);
					response.send();
					return;
				}
			}
		}

		logger.information(Poco::Logger::format("$0 : HTTP_OK", staticPath.toString()));

		std::string mimeType;
		if ( staticPath.getExtension().compare("gif") == 0 )
		{
			mimeType = "image/gif";
		}
		else if ( staticPath.getExtension().compare("css") == 0 )
		{
			mimeType = "text/css";
		}
		else if ( staticPath.getExtension().compare("html") == 0 || staticPath.getExtension().compare("htm") == 0)
		{
			mimeType = "text/html";
		}
		else if ( staticPath.getExtension().compare("js") == 0 )
		{
			mimeType = "text/javascript";
		}
		else if ( staticPath.getExtension().compare("png") == 0 )
		{
			mimeType = "image/png";
		}
		else if ( staticPath.getExtension().compare("jpg") == 0 || staticPath.getExtension().compare("jpeg") == 0)
		{
			mimeType = "image/jpeg";
		}

		try
		{
			response.sendFile(staticPath.toString(), mimeType);
		}
		catch(Poco::FileNotFoundException&)
		{
			// We can't get here normally ... but you never know :)
			response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND, Poco::Logger::format("Can't find file $0", staticPath.toString()));
		}
		catch(Poco::OpenFileException&)
		{
			response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR, Poco::Logger::format("Can't open file $0", staticPath.toString()));
		}
		return;
	}

	logger.error(Poco::Logger::format("$0 : HTTP_NOT_FOUND", staticFile.path()));
	response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
	response.send();
}