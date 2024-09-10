void EnumerateTransfersTestCase::InvalidHandle()
{
    BSLERRCODE rc = BSLERR_FAILURE;
    CBSLClient* pClient = new CBSLClient();
    BSLHOST hHost = (BSLHOST) 0x31416;
    std::vector<BSLTRANSFER> oTransfers;

    pClient->OnInit();
    rc = pClient->EnumerateTransfers(hHost, oTransfers);
    pClient->OnExit();

    delete pClient;

    CPPUNIT_ASSERT(pClient != NULL);
    CPPUNIT_ASSERT(BSLERR_HOST_NOT_FOUND == rc);
}