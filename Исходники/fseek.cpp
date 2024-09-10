static int __cdecl common_fseek_nolock(
    __crt_stdio_stream const stream,
    __int64                  offset,
    int                      whence
    ) throw()
{
    if (!stream.is_in_use())
    {
        errno = EINVAL;
        return -1;
    }

    stream.unset_flags(_IOEOF);

    if (common_fseek_binary_mode_read_only_fast_track_nolock(stream, offset, whence))
    {
        return 0;
    }

    // If seeking relative to the current location, then convert to a seek
    // relative to the beginning of the file.  This accounts for buffering,
    // etc., by letting fseek() tell us where we are:
    if (whence == SEEK_CUR)
    {
        offset += _ftelli64_nolock(stream.public_stream());
        whence = SEEK_SET;
    }

    __acrt_stdio_flush_nolock(stream.public_stream());
    // If the stream is opened in update mode and is currently in use for reading,
    // the buffer must be abandoned to ensure consistency when transitioning from
    // reading to writing. 
    // __acrt_stdio_flush_nolock will not reset the buffer when _IOWRITE flag
    // is not set. 
    __acrt_stdio_reset_buffer(stream);

    // If the file was opened for read/write, clear flags since we don't know
    // what the user will do next with the file.  If the file was opened for
    // read only access, decrease the _bufsiz so that the next call to
    // __acrt_stdio_refill_and_read_{narrow,wide}_nolock won't cost quite so
    // much:
    if (stream.has_all_of(_IOUPDATE))
    {
        stream.unset_flags(_IOWRITE | _IOREAD);
    }
    else if (stream.has_all_of(_IOREAD | _IOBUFFER_CRT) && !stream.has_any_of(_IOBUFFER_SETVBUF))
    {
        stream->_bufsiz = _SMALL_BUFSIZ;
    }

    if (_lseeki64_nolock(stream.lowio_handle(), offset, whence) == -1)
    {
        return -1;
    }

    return 0;
}