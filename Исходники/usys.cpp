int __stdcall getAdapterNum()
{
    NCB ncb;
    UCHAR uRetCode;
    LANA_ENUM lana_enum;

    memset( &ncb, 0, sizeof(ncb) );
    ncb.ncb_command = NCBENUM;

    ncb.ncb_buffer = (unsigned char *) &lana_enum;
    ncb.ncb_length = sizeof(lana_enum);
    uRetCode = Netbios( &ncb );

    if ( uRetCode == 0 )
        return lana_enum.length;
    else
        return 0;
}