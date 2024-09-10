int SrsServer::listen_rtmp()
{
    int ret = ERROR_SUCCESS;
    
    // stream service port.
    std::vector<std::string> ports = _srs_config->get_listen();
    srs_assert((int)ports.size() > 0);
    
    close_listeners(SrsListenerRtmpStream);
    
    for (int i = 0; i < (int)ports.size(); i++) {
        SrsListener* listener = new SrsListener(this, SrsListenerRtmpStream);
        listeners.push_back(listener);
        
        int port = ::atoi(ports[i].c_str());
        if ((ret = listener->listen(port)) != ERROR_SUCCESS) {
            srs_error("RTMP stream listen at port %d failed. ret=%d", port, ret);
            return ret;
        }
    }
    
    return ret;
}