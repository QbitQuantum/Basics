HDDEDATA CDDEServer::DoWildConnect(HSZ hszTopic)
{
    //
    // See how many topics we will be returning
    //

    int iTopics = 0;
    CString strTopic = "<null>";
    if (hszTopic == NULL) {

        //
        // Count all the topics we have
        //

        iTopics = m_TopicList.GetCount();

    } else {

        //
        // See if we have this topic in our list
        //

        strTopic = StringFromHsz(hszTopic);
        CDDETopic* pTopic = FindTopic(strTopic);
        if(pTopic) {
            iTopics++;
        }
    }

    //
    // If we have no match or no topics at all, just return
    // NULL now to refuse the connect
    //

    if (!iTopics) {
        Status(_T("Wild connect to %s refused"), (const TCHAR*)strTopic);
        return (HDDEDATA) NULL;
    }

    //
    // Allocate a chunk of DDE data big enough for all the HSZPAIRS
    // we'll be sending back plus space for a NULL entry on the end
    //

    HDDEDATA hData = ::DdeCreateDataHandle(m_dwDDEInstance,
                                  NULL,
                                  (iTopics + 1) * sizeof(HSZPAIR),
                                  0,
                                  NULL,
                                  0,
                                  0);

    //
    // Check we actually got it.
    //

    if (!hData) return (HDDEDATA) NULL;

    HSZPAIR* pHszPair = (PHSZPAIR) DdeAccessData(hData, NULL);

    //
    // Copy the topic data
    //

    if (hszTopic == NULL) {

        //
        // Copy all the topics we have (includes the system topic)
        //

        POSITION pos = m_TopicList.GetHeadPosition();
        while (pos) {

            CDDETopic* pTopic = m_TopicList.GetNext(pos);
            pHszPair->hszSvc = ::DdeCreateStringHandle(m_dwDDEInstance,
                                                       (TCHAR*)(const TCHAR*)m_strServiceName,
                                                       DDE_STRING_CODEPAGE);
            pHszPair->hszTopic = ::DdeCreateStringHandle(m_dwDDEInstance,
                                                         (TCHAR*)(const TCHAR*)pTopic->m_strName,
                                                         DDE_STRING_CODEPAGE);

            pHszPair++;
        }

    } else {

        //
        // Just copy the one topic asked for
        //

        pHszPair->hszSvc = m_hszServiceName;
        pHszPair->hszTopic = hszTopic;

        pHszPair++;

    }

    //
    // Put the terminator on the end
    //

    pHszPair->hszSvc = NULL;
    pHszPair->hszTopic = NULL;

    //
    // Finished with the data block
    //

    ::DdeUnaccessData(hData);

    //
    // Return the block handle
    //

    return hData;
}