int PosixFilesystem::rename (RFs& aFs, const wchar_t* oldname, const wchar_t* newname, int& anErrno)
{
    TFileName oldFullName;
    TInt err = GetFullFile(oldFullName,(const TText16 *)oldname,aFs);
    if (!err)
    {
        TFileName newFullName;
        err = GetFullFile(newFullName,(const TText16 *)newname,aFs);
        if (!err)
        {
            // ANSI doesn't require specific handling when newname exists,
            // so we can just use the EPOC32 semantics and insist that
            // newname doesn't currently exist.
            err=aFs.Rename(oldFullName,newFullName);
        }
    }
    return MapError(err, anErrno);
}