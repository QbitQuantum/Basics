static err_t Open(filestream* p, const tchar_t* URL, int Flags)
{
	if (p->fd>=0)
		fileXioClose(p->fd);

    p->Length = INVALID_FILEPOS_T;
	p->fd = -1;

	if (URL && URL[0])
	{
        tchar_t Tmp[MAXPATH];
		int size;
        int mode = 0;

        URL = CdromPath(URL,Tmp,TSIZEOF(Tmp));

        if (Flags & SFLAG_WRONLY && !(Flags & SFLAG_RDONLY))
            mode = O_WRONLY;
        else if (Flags & SFLAG_RDONLY && !(Flags & SFLAG_WRONLY))
            mode = O_RDONLY;
        else
            mode = O_RDWR;

        if (Flags & SFLAG_CREATE)
            mode |= O_CREAT|O_TRUNC;

		p->fd = fileXioOpen(URL, mode, FIO_S_IRUSR | FIO_S_IWUSR | FIO_S_IXUSR | FIO_S_IRGRP | FIO_S_IWGRP | FIO_S_IXGRP | FIO_S_IROTH | FIO_S_IWOTH | FIO_S_IXOTH );
		if (p->fd<0)
		{
			if ((Flags & (SFLAG_REOPEN|SFLAG_SILENT))==0)
				NodeReportError(p,NULL,ERR_ID,ERR_FILE_NOT_FOUND,URL);
			return ERR_FILE_NOT_FOUND;
		}

		tcscpy_s(p->URL,TSIZEOF(p->URL),URL);

	    if ((size = fileXioLseek(p->fd, 0, SEEK_END)) >= 0)
        {
            fileXioLseek(p->fd, 0, SEEK_SET);
			p->Length = size;
        }
	}
	return ERR_NONE;
}