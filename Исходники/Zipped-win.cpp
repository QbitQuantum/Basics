const zip_fileinfo* setFileInfo(zip_fileinfo* fi, unsigned long long itemFiletime)
{
    const zip_fileinfo* fip;
    if (itemFiletime == 0)
    {
        fip = 0;
    }
    else
    {
        filetime64_t filetime = {itemFiletime};
        FILETIME localFileTime;
        FileTimeToLocalFileTime(&filetime.ft, &localFileTime);
        unsigned short dosDate;
        unsigned short dosTime;
        FileTimeToDosDateTime(&localFileTime, &dosDate, &dosTime);
        memset(fi, 0, sizeof(*fi));
        fi->dosDate = (static_cast<unsigned long>(dosDate) << 16) | dosTime;
        fip = fi;
    }

    return fip;
}