void WfsFileBase::set_size(offset_type newsize) {
    std::unique_lock<std::mutex> fd_lock(fd_mutex_);
    offset_type cur_size = _size();

    if (!(mode_ & RDONLY))
    {
        LARGE_INTEGER desired_pos;
        desired_pos.QuadPart = newsize;

        bool direct_with_bad_size = (mode_& FileBase::DIRECT) && (newsize % bytes_per_sector);
        if (direct_with_bad_size)
        {
            if (!CloseHandle(file_des_))
                THRILL_THROW_WIN_LASTERROR(IoError, "closing file (call of ::CloseHandle() from set_size) ");

            file_des_ = INVALID_HANDLE_VALUE;
            file_des_ = open_file_impl(filename, WRONLY);
        }

        if (!SetFilePointerEx(file_des_, desired_pos, nullptr, FILE_BEGIN))
            THRILL_THROW_WIN_LASTERROR(IoError,
                                       "SetFilePointerEx() in wfs_file_base::set_size(..) oldsize=" << cur_size <<
                                       " newsize=" << newsize << " ");

        if (!SetEndOfFile(file_des_))
            THRILL_THROW_WIN_LASTERROR(IoError, "SetEndOfFile() oldsize=" << cur_size <<
                                       " newsize=" << newsize << " ");

        if (direct_with_bad_size)
        {
            if (!CloseHandle(file_des_))
                THRILL_THROW_WIN_LASTERROR(IoError, "closing file (call of ::CloseHandle() from set_size) ");

            file_des_ = INVALID_HANDLE_VALUE;
            file_des_ = open_file_impl(filename, mode_ & ~TRUNC);
        }
    }
}