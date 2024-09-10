    int WinFSeek(FileHndl &file, stream_length_type offset, int origin)
    {
		return _fseeki64(file.get(), offset, origin);
    }