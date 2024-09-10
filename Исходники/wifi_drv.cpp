int WiFiDrv::getHostByName(const char *aHostname, IPAddress &aResult)
{
    uint8_t retry = 10;

    if ( reqHostByName(aHostname) ) {
        while ( !getHostByName(aResult) && --retry > 0 ) {
            delay(1000);
        }
    } else {
        return 0;
    }
    return retry > 0;
}