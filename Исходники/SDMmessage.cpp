long SDMmessage::SendDM()
{
#ifdef BUILD_FOR_PNPSAT
    struct hostent *he;
    unsigned long addr;

    while ((he=gethostbyname("datamanager.spacewire")) == NULL)
    {
        sleep(1);
    }
    memcpy(&addr, he->h_addr, sizeof(addr));

    DataManager.setAddress(addr);
    DataManager.setPort(PORT_DM);
#endif
#ifdef PNP_FAKE
//    struct hostent *he;
//    unsigned long addr;
//
//    while ((he=gethostbyname("datamanager")) == NULL)
//    {
//        sleep(1);
//    }
//    memcpy(&addr, he->h_addr, sizeof(addr));
//
//    DataManager.setAddress(addr);
//    DataManager.setPort(PORT_DM);
#endif
    return SendTo(DataManager);
}