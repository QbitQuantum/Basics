// -----------------------------------------------------------------------------
// RsearchServerSession::Connect()
// Connects to the server and create a session.
// -----------------------------------------------------------------------------
EXPORT_C TInt RSearchServerSession::Connect()
	{
    //read the name and Uid of the search server
    TInt err = KErrNotReady;
    // get the watchdog repro 
    //TRAP_IGNORE is used to avoid the code scanner error
    CRepository* wdrepo = NULL;
    TRAP_IGNORE(wdrepo = CRepository::NewL( KWDrepoUidMenu ));
    if ( wdrepo )
        {
        HBufC* servername = NULL;
        TUid serveruid = {0};
        TBuf<KCenrepUidLength> temp;
        TInt64 value;
        TLex uidvalue;
        //read the searchserver UId
        if ( KErrNone == wdrepo->Get( KSearchServerUIDKey, temp ))
            {
            uidvalue.Assign(temp);
            if (KErrNone == uidvalue.Val( value,EHex ))
                serveruid.iUid = value;
            }
        //read the search server name
        if ( KErrNone == wdrepo->Get( KSearchServerNAMEKey, temp ))
            {
            //TRAP_IGNORE is used to avoid the code scanner error
            TRAP_IGNORE(servername = HBufC::NewL( temp.Length() ));
            TPtr ssname = servername->Des(); 
            ssname.Copy( temp );
            }
        // make sure the server is started before creating connection
        if ( servername )
           err = StartServer( *servername , serveruid );
    
        if ( KErrNone == err )
            {
            err = CreateSession(*servername, Version(), KDefaultMessageSlots);
            }
        delete servername;
        }
    delete wdrepo;
	return err;
	}