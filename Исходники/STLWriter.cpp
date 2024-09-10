STLWriter::STLWriter() : filename_(""),
                         filedir_(""), 
                         isBinaryMode_(false)
{
     time_t t = time(0);
    struct tm* n = new tm();
    localtime_s(n, &t);

    // Use the time of construction 
    // for a unique filename
    filename_ = (n->tm_year + 1900) + 
                (n->tm_mon + 1) +
                n->tm_mday + 
                "_" +
                n->tm_hour + 
                n->tm_min + 
                n->tm_sec;
}