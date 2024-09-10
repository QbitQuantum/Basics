	void process(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, const std::string& path, std::istream& resourceStream, Poco::OSP::Bundle::ConstPtr pBundle)
	{
		std::string content;
		Poco::StreamCopier::copyToString(resourceStream, content);
		std::string dateTime = Poco::DateTimeFormatter::format(Poco::DateTime(), Poco::DateTimeFormat::HTTP_FORMAT);
		Poco::replaceInPlace(content, std::string("$$DATETIME$$"), dateTime);
		response.setContentType("text/html");
		response.send() << content;
	}