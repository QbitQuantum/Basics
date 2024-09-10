OsStatus
UpdateMessageStatesCGI::handleOpenVXIRequest( UtlString* out )
{
    // Instantiate the mailbox manager
    MailboxManager* pMailboxManager = MailboxManager::getInstance();
        OsStatus result = pMailboxManager->updateMessageStates(m_mailboxIdentity, m_category, m_messageIds);

        UtlString dynamicVxml = getVXMLHeader();

        if( result == OS_SUCCESS )
        {
                dynamicVxml += VXML_SUCCESS_SNIPPET;
        }
        else
        {
                dynamicVxml += VXML_FAILURE_SNIPPET;
        }

        dynamicVxml += VXML_END;

        // Write out the dynamic VXML script to be processed by OpenVXI
        if (out)
        {
        out->remove(0);
        UtlString responseHeaders;
        MailboxManager::getResponseHeaders(dynamicVxml.length(), responseHeaders);

        out->append(responseHeaders.data());
        out->append(dynamicVxml.data());
        }

        return OS_SUCCESS;
}