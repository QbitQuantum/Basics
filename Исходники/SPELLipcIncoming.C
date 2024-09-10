//=============================================================================
// METHOD: SPELLipcIncomingRequest:run
//=============================================================================
void SPELLipcIncomingRequest::run()
{
    std::string senderId = m_message->getSender();
    std::string receiverId = m_message->getReceiver();
    // If the request has been canceled beforehand
    if (m_cancel) return;
    SPELLipcMessage* response = m_listener->processRequest(m_message);
    if (response && !m_cancel)
    {
        response->setSender(receiverId);
        response->setReceiver(senderId);
        // Do not set sequence number if it is already set.
        // This happens when forwarding requests.
        if (response->getSequence() == -1)
        {
            response->setSequence( m_message->getSequence() );
        }
        try
        {
            if (m_interface->isConnected())
            {
                SPELLipcOutput& writer = m_interface->getWriter(m_message->getKey());
                writer.send(response);
                m_interface->endRequest( getThreadId() );
            }
        }
        catch(...) {};
        delete response;
    }
    finish();
    delete m_message;
}