int NetIfGetConfigByName(PNETIFINFO pInfo)
{
    int rc = VINF_SUCCESS;
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
        return VERR_NOT_IMPLEMENTED;
    rc = getInterfaceInfo(sock, pInfo->szShortName, pInfo);
    close(sock);
    return rc;
}