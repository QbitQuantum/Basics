static int extract_cabinet( char *cab_dir )
{
    ERF erf;
    int ret = 0;
    HFDI fdi = FDICreate( cab_alloc, cab_free, fdi_open, fdi_read,
                          fdi_write, fdi_close, fdi_lseek, cpuUNKNOWN, &erf );

    if (!FDICopy( fdi, opt_cab_file, cab_dir, 0, extract_notify, NULL, NULL ))
    {
        ret = GetLastError();
        WINE_WARN("FDICopy() failed: code %u\n", ret);
    }
    FDIDestroy( fdi );
    return ret;
}