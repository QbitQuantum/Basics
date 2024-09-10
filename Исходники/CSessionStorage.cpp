void CSessionStorage::restoreSessionStateRevs(CStream* stream) {
	restoreRootItemRevs(sessionStateSubdir);

	// check if all render clients are in the same state as in last revision
	int num_clients;
    CRootItem* sstate = m_session->getSessionState( );
    CRootItem* newSState = new CRootItem(*sstate);

    CCategoryItem* base = newSState->getCategoryPtr("/RenderClients");
    if(base == 0) {
        base = newSState->mkPath("/RenderClients");
        num_clients = 0;
    }
    else {
        num_clients = base->getNumContentItems();
    }

    ostringstream oss;
    oss << "Restoring state of session '" << m_session->getName() << "':" << endl;

    for(int i=0; i < num_clients; i++) {
        IContentItem* ci = base->getContentItem(i);
        if(ci->type() == CItemType::E_STREAM_CLIENT) {
            CStreamClientItem* sci = reinterpret_cast<CStreamClientItem*>(ci);

            ServDescPtr srvPtr = m_session->getServiceByName(sci->getServiceName());
            string sessionName = m_session->getName();
            oss << "\t'" << sci->getServiceName() << "' (" << sci->getHostName() << ") was part of session '" << sci->getOwnerSessionName() << "'" << endl;

            if(srvPtr) {
               // service is there, if it part of this session, enable it, else do nothing
                if(sessionName.compare(sci->getOwnerSessionName()) == 0) {
                    // client is not active, but this session has owned it -> keep it as disabled
                    sci->setEnabled(true);
                    // add this render client to streamserver
                    stream->addReceiver(srvPtr);
                    oss << "\t\t is available and belongs to this session -> enabled" << endl;
                }
            }
            else {
                // service is not there, if it is part of this session, disable it, else remove it
                if(sessionName.compare(sci->getOwnerSessionName()) == 0) {
                    // client is not active, but this session has owned it -> keep it as disabled
                    sci->setEnabled(false);
                    oss << "\t\t is not available now but belonged to this session -> disable but keep it. Will be enabled automatically when it appears on the network again." << endl;
                }
                else {
                    base->delContentItem(i);
                    num_clients--;
                    oss << "\t\t is not available now but did not belong to this session anyway -> remove it from list." << endl;
                }
            }
        }
    }

    LOG4CPLUS_INFO(m_app->logger(), oss.str());

    if( *newSState == *sstate ) {
        delete newSState;
    }
    else {
        m_session->addSessionStateRev(newSState);
    }


}