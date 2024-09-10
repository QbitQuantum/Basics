void DxConfiguration::marshall()
{
    SseMsg::marshall(site);
    NTOHL(dxId);
    NTOHD(a2dClockrate);
    NTOHL(archiverPort);

    // no need to marshall archiveHostname char array
}