boolean disk_file_query_information(DISK_FILE* file, uint32 FsInformationClass, STREAM* output)
{
    struct STAT st;

    if (STAT(file->fullpath, &st) != 0)
    {
        stream_write_uint32(output, 0); /* Length */
        return false;
    }
    switch (FsInformationClass)
    {
    case FileBasicInformation:
        /* http://msdn.microsoft.com/en-us/library/cc232094.aspx */
        stream_write_uint32(output, 36); /* Length */
        stream_check_size(output, 36);
        stream_write_uint64(output, FILE_TIME_SYSTEM_TO_RDP(st.st_mtime)); /* CreationTime */
        stream_write_uint64(output, FILE_TIME_SYSTEM_TO_RDP(st.st_atime)); /* LastAccessTime */
        stream_write_uint64(output, FILE_TIME_SYSTEM_TO_RDP(st.st_mtime)); /* LastWriteTime */
        stream_write_uint64(output, FILE_TIME_SYSTEM_TO_RDP(st.st_ctime)); /* ChangeTime */
        stream_write_uint32(output, FILE_ATTR_SYSTEM_TO_RDP(file, st)); /* FileAttributes */
        /* Reserved(4), MUST NOT be added! */
        break;

    case FileStandardInformation:
        /*  http://msdn.microsoft.com/en-us/library/cc232088.aspx */
        stream_write_uint32(output, 22); /* Length */
        stream_check_size(output, 22);
        stream_write_uint64(output, st.st_size); /* AllocationSize */
        stream_write_uint64(output, st.st_size); /* EndOfFile */
        stream_write_uint32(output, st.st_nlink); /* NumberOfLinks */
        stream_write_uint8(output, file->delete_pending ? 1 : 0); /* DeletePending */
        stream_write_uint8(output, file->is_dir ? 1 : 0); /* Directory */
        /* Reserved(2), MUST NOT be added! */
        break;

    case FileAttributeTagInformation:
        /* http://msdn.microsoft.com/en-us/library/cc232093.aspx */
        stream_write_uint32(output, 8); /* Length */
        stream_check_size(output, 8);
        stream_write_uint32(output, FILE_ATTR_SYSTEM_TO_RDP(file, st)); /* FileAttributes */
        stream_write_uint32(output, 0); /* ReparseTag */
        break;

    default:
        stream_write_uint32(output, 0); /* Length */
        DEBUG_WARN("invalid FsInformationClass %d", FsInformationClass);
        return false;
    }
    return true;
}