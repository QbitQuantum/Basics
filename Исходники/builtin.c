static void cat_cleanup(void *data)
{
    cat_info *pci = (cat_info *) data;
    Rconnection con = pci->con;
    Rboolean wasopen = pci->wasopen;
    int changedcon = pci->changedcon;

    con->fflush(con);
    if(changedcon) switch_stdout(-1, 0);
    /* previous line might have closed it */
    if(!wasopen && con->isopen) con->close(con);
#ifdef Win32
    WinUTF8out = FALSE;
#endif
}