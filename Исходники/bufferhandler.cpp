void
BufferHandler::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
    prepareResponse(resp);
    resp.set("ETag", etag);
    resp.set("Cache-Control", "max-age=300, private");

    if (req.get("If-None-Match", "") == etag) {
        // ETag matched. No content to send;
        resp.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_MODIFIED);
        resp.setReason("Not Modified");

        resp.send().flush();
        return;
    }

    resp.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
    resp.setContentType(contentType);
    resp.setContentLength(bufferLen);

    std::ostream & out = resp.send();
    out.write(reinterpret_cast<const char*>(buffer), bufferLen);
    out.flush();
};