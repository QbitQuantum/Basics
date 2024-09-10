    void removeFile(const char *filename)
    {
        bool isdir;
        isDir(filename,isdir);
        if (isdir) {
#ifdef _WIN32
            // no rmdir?
            if (RemoveDirectory(filename)==0)
                return;
            DWORD err = GetLastError();
            if ( (err==ERROR_FILE_NOT_FOUND) || (err==ERROR_PATH_NOT_FOUND) )
                return;
            throwError((int)err,"removeFile"); // shouldn't really pass win error here
#else
            if (rmdir(filename) == 0)
                return;
#endif
        }
        else {
            if (_unlink(filename) == 0)
                return;
        }
        if (ENOENT!=errno)
            throwError(errno,"removeFile");
    }