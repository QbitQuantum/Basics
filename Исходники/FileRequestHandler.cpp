void FileRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
    setContentType(request, response);
    std::ostream& ostr = response.send();
    try {
        Poco::Path basedir = Poco::Util::Application::instance().config().getString("application.dir");
        basedir.append("web");
        basedir.append(request.getURI());
        Poco::FileInputStream fis(basedir.toString());
        Poco::StreamCopier::copyStream(fis, ostr);
        response.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
    }
    catch (Poco::Exception& ex) {
        response.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
        ostr << ex.displayText();
        _logger.error("Request failed: %s: %s", request.getURI(), ex.displayText());
    }

}