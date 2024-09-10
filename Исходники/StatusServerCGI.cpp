OsStatus
StatusServerCGI::execute(UtlString* out)
{
    // forward the request to the mailbox manager
#ifdef WIN32
//  DebugBreak();
#endif
    UtlString notifyBodyText;
    OsStatus result =
       MailboxManager::getInstance()->getMWINotifyText ( m_mailboxIdentity, NULL, notifyBodyText );
    // send an OK back to the Status Server
    if (out)
    {
        // clear the response
        out->remove(0);

        // set the http headers
        char contentLengthHeader[40];
        sprintf( contentLengthHeader, "Content-Length: %zu\r\n", notifyBodyText.length() );
        out->append( (UtlString)contentLengthHeader );
        out->append( "Content-Type: application/simple-message-summary\r\n" );


        // Separate the headers from the body content (very important otherwise no body sent!)
        out->append( "\r\n" );
        out->append( notifyBodyText.data() );
    }
    return result;
}