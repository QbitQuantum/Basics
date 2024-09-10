//
// Function: LanaStatus
//
// Description:
//    Perform a LAN adapter status command.
//
int LanaStatus(int lana, char *name)
{
    NCB             ncb;
    MESSAGE_BUFFER  mb;

    ZeroMemory(&mb,  sizeof(MESSAGE_BUFFER));
    ZeroMemory(&ncb,  sizeof(NCB));

    memset(ncb.ncb_callname, ' ', NCBNAMSZ);
    //
    // Check command line options to see if the call is
    // made locally or remotely.
    //
    if ((bLocalName == FALSE) && (bRemoteName == FALSE))
        ncb.ncb_callname[0] = '*';
    else
        strncpy(ncb.ncb_callname, name, strlen(name));

    ncb.ncb_command = NCBASTAT;
    ncb.ncb_buffer  = (UCHAR *)&mb;
    ncb.ncb_length  = sizeof(MESSAGE_BUFFER);
    ncb.ncb_lana_num= lana;

    if (Netbios(&ncb) != NRC_GOODRET)
    {
        printf("Netbios: NCBASTAT failed: %d\n", ncb.ncb_retcode);
        return ncb.ncb_retcode;
    }
    PrintAdapterInfo(lana, mb.adapter);
    PrintNameInfo(mb.names, mb.adapter.name_count);

    return NRC_GOODRET;
}