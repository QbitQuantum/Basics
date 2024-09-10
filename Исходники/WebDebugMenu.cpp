    void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
    {
        if(request.getURI()=="/command") {
            EachInputValue(request, [&](const char *id, const char *command){
                wdmEventData tmp = {std::atoi(id), command};
                wdmSystem::getInstance()->addEvent(tmp);
            });
            response.setContentType("text/plain");
            response.setContentLength(2);
            std::ostream &ostr = response.send();
            ostr.write("ok", 3);
        }
        else if(request.getURI()=="/data") {
            std::vector<wdmID> nodes;
            nodes.push_back(_wdmGetRootNode()->getID());
            EachNodeValue(request, [&](const char *id){
                nodes.push_back(std::atoi(id));
            });

            wdmString json;
            wdmJSONRequest request = {false, false, &json, nodes.empty() ? NULL : &nodes[0], (uint32_t)nodes.size()};
            wdmSystem::getInstance()->requestJSON(request);
            while(!request.done) { Poco::Thread::sleep(2); }
            if(request.canceled) { json="[]"; }

            response.setContentType("application/json");
            response.setContentLength(json.size());
            std::ostream &ostr = response.send();
            ostr.write(&json[0], json.size());
        }
    }