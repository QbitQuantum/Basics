int TestServices2::execute()
{
    bool bStarted = MVTApp::startStore() ;
    if ( !bStarted ) { TVERIFY2(0,"Could not start store, bailing out completely") ; return -1; }
    mSession = MVTApp::startSession();

    doCase1();
    doCase2();
    //case 3 and 4 are expected to be run manually
    //doCase3_receiver();
    //doCase3_sender();
    //doCase4_chatting();
    mSession->terminate(); 
    MVTApp::stopStore();
    return RC_OK;
}