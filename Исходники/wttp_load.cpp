void* startThread(void* arg)
{
    /*
    SELECT W.PageID,PageType,URL,ResetCookies,AuthUser,AuthPass,DownloadThreshold,HackingString,ResetCache,ServiceType,SecurityID,WPS.CurrentErrorRef,WPS.AlertCount,AlertLevel2Count,AlertLevel3Count,WPS.ErrorStatus,W.Status,W.IgnoreRudeWords,W.CustomerNo,W.HTTPMethod,W.IgnoreContentErrors,W.DownloadSpeed,W.Referer,W.StoreResultDetail,W.MinSize,W.MaxSize,C.AlertCount,W.CertID,W.StepName,W.AgentString,W.sm_processScript,WPS.OverallAlertCount,W.StoreRequest,W.StoreHeaders,W.StoreHTML,W.StoreDiag,W.ContentType,W.Header1,W.Header2,W.GzipEncoding from WebPage W, Customer C, WebPageStatus WPS where W.PageID=13714 and WPS.PageID=W.PageID and W.CustomerNo=C.CustomerNo and (W.Status=1 or W.Status=3)
    select VariableName, VariableValue, Encode from FormVariables where PageID=13714 order by OrderNo asc
    SELECT Phrase, ID from ContentError
    SELECT Word, ID from ObsceneWord
    SELECT Phrase, ErrorCode from WebPagePhrase where PageID=13714 order by PhraseOrder
    select CookieValue, CookieDomain from Cookies where PageID=13714
    select URL, RequiredText from WebPageExtraFiles where PageID=13714 and Type=0
    select URL, RequiredText from WebPageExtraFiles where PageID=13714 and Type=1
    select URL, RequiredText from WebPageExtraFiles where PageID=13714 and Type=2
    INSERT INTO ResultHeader040303 (ResultID,PageID,TestServer,StartDateTime,ResultCode,DNSTime,FirstByteTime,CompleteTime,TotalBytes,RunID,BatchID,FirstDataTime) VALUES (0,13714,10,'2004-03-03 14:39:20',1,8,9,5309,25291,0,0,15)
    SELECT LAST_INSERT_ID() from ResultHeader040303 where ResultID=LAST_INSERT_ID()
    INSERT INTO ResultDetail040303 (ResultID,StartDateTime,StartOffset,DNSTime,FirstByteTime,FirstDataTime,CompleteTime,ResultCode,TotalBytes,FileName,ComponentNo) VALUES (40,'2004-03-03 14:39:20',0,8,9,15,892,200,4338,'http://192.168.1.5',1)
    INSERT INTO ResultDetail040303 (ResultID,StartDateTime,StartOffset,DNSTime,FirstByteTime,FirstDataTime,CompleteTime,ResultCode,TotalBytes,FileName,ComponentNo) VALUES (40,'2004-03-03 14:39:21',1012,1,1,7,4188,200,6543,'http://192.168.1.5/g/p10.png',2)
    INSERT INTO ResultDetail040303 (ResultID,StartDateTime,StartOffset,DNSTime,FirstByteTime,FirstDataTime,CompleteTime,ResultCode,TotalBytes,FileName,ComponentNo) VALUES (40,'2004-03-03 14:39:21',1025,0,2,3,4185,200,12237,'http://192.168.1.5/g/MYSQLAuthCSP_small.png',3)
    INSERT INTO ResultDetail040303 (ResultID,StartDateTime,StartOffset,DNSTime,FirstByteTime,FirstDataTime,CompleteTime,ResultCode,TotalBytes,FileName,ComponentNo) VALUES (40,'2004-03-03 14:39:21',1008,1,2,6,4301,200,2173,'http://192.168.1.5/g/newlogo.png',4)
    SELECT PageID from WebPageStatus where PageID=13714
    UPDATE WebPageStatus set LastResultID=40,StartDateTime='2004-03-03 14:39:20',LastResultCode=1,CompleteTime=5309 where PageID=13714
    SELECT WS.ErrorStatus,WS.CurrentErrorRef,WS.AlertCount,C.AlertLevel2Count,C.AlertLevel3Count,C.AlertCount,W.OverallAlertCount from Customer C, WebPage W, WebPageStatus WS WHERE C.CustomerNo=W.CustomerNo and W.PageID=WS.PageID and W.PageID=13714
    UPDATE WebPageStatus SET ErrorStatus=0,CurrentErrorRef=0,AlertCount=0 WHERE PageID=13714
    UPDATE WebPageStatus SET OverallAlertCount=0 WHERE PageID=13714
    select ErrorRef from WebPageError where PageID=13714 and Status<>2
    */

    mysql_thread_init();

    Connection* connection;
    Result* result;
    char query[10240];

    for (int repNo = 0; repNo < numRepsPerThreads; ++repNo)
    {
        try
        {
            Trace("Connecting to db", "", repNo);
            connection = new Connection(CConfig::getDBServer(), CConfig::getDBDatabase(),
                                        CConfig::getDBUser(), CConfig::getDBPass(), CConfig::getDBRetryTime());

            // run all the queries here...
            result = connection->Query("SELECT W.PageID,PageType,URL,ResetCookies,AuthUser,AuthPass,DownloadThreshold,HackingString,ResetCache,ServiceType,SecurityID,WPS.CurrentErrorRef,WPS.AlertCount,AlertLevel2Count,AlertLevel3Count,WPS.ErrorStatus,W.Status,W.IgnoreRudeWords,W.CustomerNo,W.HTTPMethod,W.IgnoreContentErrors,W.DownloadSpeed,W.Referer,W.StoreResultDetail,W.MinSize,W.MaxSize,C.AlertCount,W.CertID,W.StepName,W.AgentString,W.sm_processScript,WPS.OverallAlertCount,W.StoreRequest,W.StoreHeaders,W.StoreHTML,W.StoreDiag,W.ContentType,W.Header1,W.Header2,W.GzipEncoding from WebPage W, Customer C, WebPageStatus WPS where W.PageID=13714 and WPS.PageID=W.PageID and W.CustomerNo=C.CustomerNo and (W.Status=1 or W.Status=3)");
            result = connection->Query("select VariableName, VariableValue, Encode from FormVariables where PageID=13714 order by OrderNo asc");
            result = connection->Query("SELECT Phrase, ID from ContentError");
            result = connection->Query("SELECT Word, ID from ObsceneWord");
            result = connection->Query("SELECT Phrase, ErrorCode from WebPagePhrase where PageID=13714 order by PhraseOrder");
            result = connection->Query("select CookieValue, CookieDomain from Cookies where PageID=13714");
            result = connection->Query("select URL, RequiredText from WebPageExtraFiles where PageID=13714 and Type=0");
            result = connection->Query("select URL, RequiredText from WebPageExtraFiles where PageID=13714 and Type=1");
            result = connection->Query("select URL, RequiredText from WebPageExtraFiles where PageID=13714 and Type=2");
            // close the db connection
            connection->Close();
            delete connection;
            connection = NULL;
            Trace("Disonnected from db", "", repNo);

            Trace("Connecting to db", "", repNo);
            connection = new Connection(CConfig::getDBServer(), CConfig::getDBDatabase(),
                                        CConfig::getDBUser(), CConfig::getDBPass(), CConfig::getDBRetryTime());
            result = connection->Query("INSERT INTO ResultHeader040303 (ResultID,PageID,TestServer,StartDateTime,ResultCode,DNSTime,FirstByteTime,CompleteTime,TotalBytes,RunID,BatchID,FirstDataTime) VALUES (0,13714,10,'2004-03-03 14:39:20',1,8,9,5309,25291,0,0,15)");
            result = connection->Query("SELECT LAST_INSERT_ID() from ResultHeader040303 where ResultID=LAST_INSERT_ID()");
            result = connection->Query("INSERT INTO ResultDetail040303 (ResultID,StartDateTime,StartOffset,DNSTime,FirstByteTime,FirstDataTime,CompleteTime,ResultCode,TotalBytes,FileName,ComponentNo) VALUES (40,'2004-03-03 14:39:20',0,8,9,15,892,200,4338,'http://192.168.1.5',1)");
            result = connection->Query("INSERT INTO ResultDetail040303 (ResultID,StartDateTime,StartOffset,DNSTime,FirstByteTime,FirstDataTime,CompleteTime,ResultCode,TotalBytes,FileName,ComponentNo) VALUES (40,'2004-03-03 14:39:21',1012,1,1,7,4188,200,6543,'http://192.168.1.5/g/p10.png',2)");
            result = connection->Query("INSERT INTO ResultDetail040303 (ResultID,StartDateTime,StartOffset,DNSTime,FirstByteTime,FirstDataTime,CompleteTime,ResultCode,TotalBytes,FileName,ComponentNo) VALUES (40,'2004-03-03 14:39:21',1025,0,2,3,4185,200,12237,'http://192.168.1.5/g/MYSQLAuthCSP_small.png',3)");
            result = connection->Query("INSERT INTO ResultDetail040303 (ResultID,StartDateTime,StartOffset,DNSTime,FirstByteTime,FirstDataTime,CompleteTime,ResultCode,TotalBytes,FileName,ComponentNo) VALUES (40,'2004-03-03 14:39:21',1008,1,2,6,4301,200,2173,'http://192.168.1.5/g/newlogo.png',4)");
            result = connection->Query("SELECT PageID from WebPageStatus where PageID=13714");
            result = connection->Query("UPDATE WebPageStatus set LastResultID=40,StartDateTime='2004-03-03 14:39:20',LastResultCode=1,CompleteTime=5309 where PageID=13714");
            result = connection->Query("SELECT WS.ErrorStatus,WS.CurrentErrorRef,WS.AlertCount,C.AlertLevel2Count,C.AlertLevel3Count,C.AlertCount,W.OverallAlertCount from Customer C, WebPage W, WebPageStatus WS WHERE C.CustomerNo=W.CustomerNo and W.PageID=WS.PageID and W.PageID=13714");
            result = connection->Query("UPDATE WebPageStatus SET ErrorStatus=0,CurrentErrorRef=0,AlertCount=0 WHERE PageID=13714");
            result = connection->Query("UPDATE WebPageStatus SET OverallAlertCount=0 WHERE PageID=13714");
            result = connection->Query("select ErrorRef from WebPageError where PageID=13714 and Status<>2");
            // close the db connection
            connection->Close();
            delete connection;
            connection = NULL;
            Trace("Disonnected from db", "", repNo);

        }
        catch (const std::exception &e)
        {
            printf("Exception caught: - %s\r\n", e.what());
            // all done - exit the thread
//			pthread_exit(NULL);
        }

        Trace("Sleeping", "", 100 * sleepTime);
        usleep(100 * sleepTime);
    }

    mysql_thread_end();

    // all done - exit the thread
    pthread_exit(NULL);

    Trace("After Thread end", "", 0);
}