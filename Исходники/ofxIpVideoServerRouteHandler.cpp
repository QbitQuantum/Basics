//------------------------------------------------------------------------------
void ofxIpVideoServerRouteHandler::handleRequest(HTTPServerRequest& request,
                                                 HTTPServerResponse& response) {
    
    
    if(isValidRequest(settings.route,request,response)) {
        MediaType mediaType("multipart/x-mixed-replace");
        mediaType.setParameter("boundary", settings.boundary);

        string expires = DateTimeFormatter::format(Timestamp(0), // the beginning of time
                                                   DateTimeFormat::HTTP_FORMAT);
        
        response.set("Cache-control","no-cache");
        response.setContentType(mediaType);
        response.set("Expires",expires);
        response.set("Pragma","no-cache");
        
        std::ostream& ostr = response.send(); // get output stream

        bool stopStreaming = false;
        
        while(ostr.good() && !stopStreaming) {
            if(!queue.empty()) {
                ofxIpVideoServerFramePtr frame = queue.pop();
                    if(frame != NULL) {
                        ofBuffer* buffer = &frame.get()->buffer;
                        ostr << settings.boundary;
                        ostr << "\r\n";
                        ostr << "Content-Type: image/jpeg";
                        ostr << "\r\n";
                        ostr << "Content-Length: " << ofToString(buffer->size());
                        ostr << "\r\n";
                        ostr << "\r\n";
                        ostr << *buffer;
                    } else {
                        ofLogVerbose("ofxIpVideoServerRouteHandler::handleRequest") << "Null buffer.";
                    }
                } else {
                    ofLogVerbose("ofxIpVideoServerRouteHandler::handleRequest") << "Queue empty.";
                }
            
            Thread::sleep(50);
        }
        
        queue.setActive(false); // a desperate move 
        
        ofLogNotice("ofxIpVideoServerRouteHandler::handleRequest") << "Client disconneted.";
        
        //sendErrorResponse(response);
    }
}