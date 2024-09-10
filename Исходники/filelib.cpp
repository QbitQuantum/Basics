/*
 * ==============
 * getfiledata
 * ==============
 */
long            getfiledata(const char* const filename, char* buffer, const int buffersize)
{
    long            size = 0;
    int             handle;
    time_t            start, end;

    time(&start);

    if ((handle = _open(filename, O_RDONLY)) != -1)
    {
        int             bytesread;

        Log("%-20s Restoring [%-13s - ", "BuildVisMatrix:", filename);
        while ((bytesread = _read(handle, buffer, min(32 * 1024, buffersize - size))) > 0)
        {
            size += bytesread;
            buffer += bytesread;
        }
        _close(handle);
        time(&end);
        Log("%10.3fMB] (%d)\n", size / (1024.0 * 1024.0), end - start);
    }

    if (buffersize != size)
    {
        Warning("Invalid file [%s] found.  File will be rebuilt!\n", filename);
        _unlink(filename);
    }

    return size;
}