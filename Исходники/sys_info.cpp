 // static
 int64 SysInfo::AmountOfFreeDiskSpace(const FilePath& path)
 {
     ULARGE_INTEGER available, total, free;
     if(!GetDiskFreeSpaceExW(path.value().c_str(), &available, &total, &free))
     {
         return -1;
     }
     int64 rv = static_cast<int64>(available.QuadPart);
     if(rv < 0)
     {
         rv = kint64max;
     }
     return rv;
 }