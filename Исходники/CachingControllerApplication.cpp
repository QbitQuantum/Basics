    void CachingControllerApplication::HandleClientConfigurationInput(Ptr<Socket> HandleClientConfigurationInput) {
        NS_LOG_FUNCTION(this);
        std::ostringstream buf;
        HandleClientConfigurationInput->Recv()->CopyData(&buf, INT_MAX);
        HandleNewResourceAsked(buf.str());


    }