bool IsDateModifyLess(const MFT_STANDARD & attr, const FILETIME& fileTime)
{
    return (CompareFileTime((const FILETIME*)&attr.n64Modify, &fileTime) < 0);
}