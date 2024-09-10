    bool TouchPlatformFile(PlatformFile file, const base::Time& last_access_time,
        const base::Time& last_modified_time)
    {
        ThreadRestrictions::AssertIOAllowed();
        if(file == kInvalidPlatformFileValue)
        {
            return false;
        }

        FILETIME last_access_filetime = last_access_time.ToFileTime();
        FILETIME last_modified_filetime = last_modified_time.ToFileTime();
        return (SetFileTime(file, NULL, &last_access_filetime,
            &last_modified_filetime) != 0);
    }