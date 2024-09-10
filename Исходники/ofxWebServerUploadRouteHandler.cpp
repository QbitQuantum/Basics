//------------------------------------------------------------------------------
void ofxWebServerUploadRouteHandler::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
    if(isValidRequest(settings.route, request, response)) {
        HTMLForm form(request, request.stream(), *this);
        
        if(!settings.uploadRedirect.empty()) {
            response.redirect(settings.uploadRedirect);
        } else {
            response.setStatusAndReason(HTTPResponse::HTTP_OK);
            response.setContentLength(0);
            response.send();
        }
    } else {
        return; // isValidRequest took care of the response
    }
}