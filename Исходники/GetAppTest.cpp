void GetAppTestCase::NullHandle()
{
    BSLERRCODE rc = BSLERR_FAILURE;
    CBSLClient* pClient = new CBSLClient();

    pClient->OnInit();
    rc = pClient->GetApp(NULL, NULL);
    pClient->OnExit();

    delete pClient;

    CPPUNIT_ASSERT(pClient != NULL);
    CPPUNIT_ASSERT(BSLERR_APP_NOT_FOUND == rc);
}