/* Returns TRUE if all adapters are loopback adapters */
extern "C" BOOL lana_OnlyLoopback(void)
{
    NCB ncb;
    LANA_ENUM lana_list;
    int status;
    int i;

    memset(&ncb, 0, sizeof(ncb));
    ncb.ncb_command = NCBENUM;
    ncb.ncb_buffer = (UCHAR *) &lana_list;
    ncb.ncb_length = sizeof(lana_list);
    status = Netbios(&ncb);
    if (status != 0) {
#ifndef NOLOGGING
        afsi_log("Netbios NCBENUM failed: status %ld", status);
#endif
        return FALSE;
    }
    for (i = 0; i < lana_list.length; i++) {
	if (!lana_IsLoopback(lana_list.lana[i],FALSE)) {
	    // Found one non-Loopback adapter
	    return FALSE;
	}
    }
    // All adapters are loopback
    return TRUE;
}