OsStatus
MessageIDGenerator::recoverMessageID ( UtlString& rMessageName ) const
{
    OsSysLog::add(FAC_MEDIASERVER_CGI, PRI_DEBUG,
                  "MessageIDGenerator::recoverMessageID called");
    OsStatus result = OS_SUCCESS;

    // Create a filename in the data directory
    OsFile messageIDFile ( m_dataFileName );

    result = messageIDFile.open( OsFile::CREATE );
    OsSysLog::add(FAC_MEDIASERVER_CGI, PRI_DEBUG,
                  "MessageIDGenerator::recoverMessageID: attempt to open file '%s' returns %d",
                  m_dataFileName.data(), result);

    if (result == OS_SUCCESS)
    {
        // Recurse directories (@JC TODO)
        // Choose 1 as the sequence number to return.
        rMessageName = "00000001";
        // Save 2 as the next sequence number.
        UtlString nextSequenceNum = "00000002";
        size_t bytesWritten;
        result = messageIDFile.write( nextSequenceNum , nextSequenceNum.length(), bytesWritten );
        OsSysLog::add(FAC_MEDIASERVER_CGI, PRI_DEBUG,
                      "MessageIDGenerator::recoverMessageID: write to ID file returns %d",
                      result);
        messageIDFile.close();
    }
    else
    {
        OsSysLog::add(FAC_MEDIASERVER_CGI, PRI_CRIT,
                      "MessageIDGenerator::recoverMessageID: Attempt to recover the message ID file '%s' failed",
                      m_dataFileName.data());
    }

    OsSysLog::add(FAC_MEDIASERVER_CGI, PRI_DEBUG,
                  "MessageIDGenerator::recoverMessageID returns %d, rMessageName = '%s'",
                  result, rMessageName.data());
    return result;
}