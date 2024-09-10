        void FixedPathHandler::handleRequest(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &response) {
            Poco::Net::MediaType mediaType("text", "plain");
            response.setContentType(mediaType);
            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);

            std::ostream &stream = response.send();
            stream << "value";
        }