/*******************************************************************************
* wceex_stat - Get file attributes for file and store them in buffer.
*
* Description:
*
*   File times on Windows CE: Windows CE object store keeps track of only
*   one time, the time the file was last written to.
*
* Return value:
*
*   Upon successful completion, 0 shall be returned.
*   Otherwise, -1 shall be returned and errno set to indicate the error.
*
*   XXX - mloskot - errno is not yet implemented
*
* Reference:
*   IEEE Std 1003.1, 2004 Edition
*
*******************************************************************************/
int wceex_stat(const char* filename, struct stat *buffer)
{
    HANDLE findhandle;
    WIN32_FIND_DATA findbuf;
    wchar_t pathWCE[MAX_PATH];

    //Don't allow wildcards to be interpreted by system
    if(strpbrk(filename, "?*"))
        //if(wcspbrk(path, L"?*"))
    {
        //errno = ENOENT;
        return(-1);
    }

    //search file/dir
    mbstowcs(pathWCE, filename, strlen(filename) + 1);
    findhandle = FindFirstFile(pathWCE, &findbuf);
    if(findhandle == INVALID_HANDLE_VALUE)
    {
        //is root
        if(_stricmp(filename, ".\\")==0)
        {
            findbuf.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;

            //dummy values
            findbuf.nFileSizeHigh = 0;
            findbuf.nFileSizeLow = 0;
            findbuf.cFileName[0] = '\0';

            buffer->st_mtime = wceex_local_to_time_r(1980 - TM_YEAR_BASE, 0, 1, 0, 0, 0);
            buffer->st_atime = buffer->st_mtime;
            buffer->st_ctime = buffer->st_mtime;
        }

        //treat as an error
        else
        {
            //errno = ENOENT;
            return(-1);
        }
    }
    else
    {
        /* File is found*/

        SYSTEMTIME SystemTime;
        FILETIME LocalFTime;

        //Time of last modification
        if(!FileTimeToLocalFileTime( &findbuf.ftLastWriteTime, &LocalFTime) ||
            !FileTimeToSystemTime(&LocalFTime, &SystemTime))
        {
            //errno = ::GetLastError();
            FindClose( findhandle );
            return( -1 );
        }

        buffer->st_mtime = wceex_local_to_time(&SystemTime);

        //Time od last access of file
        if(findbuf.ftLastAccessTime.dwLowDateTime || findbuf.ftLastAccessTime.dwHighDateTime)
        {
            if(!FileTimeToLocalFileTime(&findbuf.ftLastAccessTime, &LocalFTime) ||
                !FileTimeToSystemTime(&LocalFTime, &SystemTime))
            {
                //errno = ::GetLastError();
                FindClose( findhandle );
                return( -1 );
            }
            buffer->st_atime = wceex_local_to_time(&SystemTime);
        }
        else
        {
            buffer->st_atime = buffer->st_mtime;
        }


        //Time of creation of file
        if(findbuf.ftCreationTime.dwLowDateTime || findbuf.ftCreationTime.dwHighDateTime)
        {
            if(!FileTimeToLocalFileTime(&findbuf.ftCreationTime, &LocalFTime) ||
                !FileTimeToSystemTime(&LocalFTime, &SystemTime))
            {
                //errno = ::GetLastError();
                FindClose( findhandle );
                return( -1 );
            }
            buffer->st_ctime = wceex_local_to_time(&SystemTime);
        }
        else
        {
            buffer->st_ctime = buffer->st_mtime;
        }

        //close handle
        FindClose(findhandle);
    }

    //file mode
    buffer->st_mode = __wceex_get_file_mode(filename, findbuf.dwFileAttributes);

    //file size
    buffer->st_size = findbuf.nFileSizeLow;

    //drive letter 0
    buffer->st_rdev = buffer->st_dev = 0;

    //set the common fields
    buffer->st_gid = 0;
    buffer->st_ino = 0;
    buffer->st_uid = 0;

    //1 dla nlink
    buffer->st_nlink = 1;


    return 0;
}