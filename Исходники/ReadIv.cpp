void Application::compute(void *)
{
    //
    // ...... do work here ........
    //

    // read input parameters and data object name
    int ofp;
    char *address;
    int length;
    struct stat My_stat_buf;

    err_status = Covise::get_browser_param("path", &Path);
    IvDescr = Covise::get_object_name("descr");

    count++;

#ifdef _WIN32
    if ((ofp = Covise::open(Path, _O_RDONLY)) == -1)
#else
    if ((ofp = Covise::open(Path, O_RDONLY)) == -1)
#endif
    {
        Covise::sendError("ERROR: Can't open file >> ");
        return;
    }

    if (fstat(ofp, &My_stat_buf) < 0)
    {
        Covise::sendError("ERROR: Can't access file :");
        return;
    }
    length = (int)My_stat_buf.st_size;

    if (IvDescr != NULL)
    {
        descr = new coDoText(IvDescr, length);
        if (descr->objectOk())
        {
            descr->getAddress(&address);
            int n = read(ofp, address, length);
            if (n != length)
            {
                fprintf(stderr, "ReadIv: compute(): short read\n");
            }
        }
        else
        {
            Covise::sendError("ERROR: object name not correct for 'Iv-File'");
            return;
        }
    }
    else
    {
        Covise::sendError("ERROR: creation of data object 'descr' failed");
        return;
    }

    delete descr;
    close(ofp);
}