long bmd_load_binary_content_wide(const wchar_t *filename, GenBuf_t **buffer)
{
GenBuf_t *tmpBuffer=NULL;
long fd=-1;
struct stat file_info;
long nread=-1;



	if( (fd=_wopen(filename, O_RDONLY|_O_BINARY)) == -1)
	{
		PRINT_ERROR("LIBBMDUTILSERR Disk error. Error=%i\n",BMD_ERR_DISK);
		return BMD_ERR_DISK;
	}

	if( (fstat(fd,&file_info)==-1) )
	{
		close(fd);
		PRINT_ERROR("LIBBMDUTILSERR Disk error. Error=%i\n",BMD_ERR_DISK);
		return BMD_ERR_DISK;
	}

	tmpBuffer=(GenBuf_t *)calloc(1, sizeof(GenBuf_t));
	if ( tmpBuffer == NULL )
	{
		close(fd);
		PRINT_ERROR("LIBBMDUTILSERR Memory error. Error=%i\n",NO_MEMORY);
		return NO_MEMORY;
	}

	tmpBuffer->buf=(char *)calloc(file_info.st_size, sizeof(char));
	if( tmpBuffer->buf == NULL )
	{
		free(tmpBuffer);
		close(fd);
		PRINT_ERROR("LIBBMDUTILSERR Memory error. Error=%i\n",NO_MEMORY);
		return NO_MEMORY;
	}

	tmpBuffer->size=file_info.st_size;
	nread=read(fd,tmpBuffer->buf, tmpBuffer->size);
	if ( nread == -1 )
	{
		free(tmpBuffer->buf);
		free(tmpBuffer);
		close(fd);
		PRINT_ERROR("LIBBMDUTILSERR Disk error. Error=%i\n",BMD_ERR_DISK);
		return BMD_ERR_DISK;
	}
	close(fd);

	*buffer=tmpBuffer;
	tmpBuffer=NULL;
	return BMD_OK;
}