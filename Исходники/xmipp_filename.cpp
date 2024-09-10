/* Wait until file has a stable size --------------------------------------- */
void FileName::waitUntilStableSize(size_t time_step)
{
    size_t idx;
    FileName basicName;
    decompose(idx, basicName);

    if (!exists())
        return;
    Stat info1, info2;
    if (stat(basicName.c_str(), &info1))
        REPORT_ERROR(ERR_UNCLASSIFIED,
                     (String)"FileName::waitUntilStableSize: Cannot get size of file " + *this);
    off_t size1 = info1.st_size;
    do
    {
        usleep(time_step);
        if (stat(basicName.c_str(), &info2))
            REPORT_ERROR(ERR_UNCLASSIFIED,
                         (String)"FileName::waitUntilStableSize: Cannot get size of file " + *this);
        off_t size2 = info2.st_size;
        if (size1 == size2)
            break;
        size1 = size2;
    }
    while (true);
    return;
}