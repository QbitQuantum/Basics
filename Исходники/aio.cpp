bool aclose_write(void)
{
#ifdef WINDOWS
    if(buffering)
    {
#ifdef PRE_ALLOCATE
        if(!CloseHandle(ofile))
            return false;
        ofile = CreateFile(destination_file, GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if(ofile == INVALID_HANDLE_VALUE)
            return false;
        myFileSeek(ofile, awritten(), SEEK_CUR);
        SetEndOfFile(ofile);  
#endif
        return CloseHandle(ofile) != 0;
    }
    else
    {
        if(ofile == GetStdHandle(STD_OUTPUT_HANDLE))
        {
            return CloseHandle(ofile) != 0;
        }
        else
        {
            // write remaining data in queue, round UP to nearest sector size (we may write
            // too much but file will be trucnated later, below).
            size_t n = (queued | (AIO_MAX_SECTOR_SIZE - 1)) + 1;
            FWRITE(write_buffer, n, ofile);

            if(!CloseHandle(ofile))
                return false;
            ofile = CreateFile(destination_file, GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if(ofile == INVALID_HANDLE_VALUE)
                return false;
            myFileSeek(ofile, awritten(), SEEK_CUR);
            SetEndOfFile(ofile);
            return CloseHandle(ofile) != 0;
        }
    }
#else
	if(ofile != 0)
	    fclose(ofile);
    return true;
#endif
}