buf32_t* _read_file(char * file_path)
{
    buf32_t *file_content;
    uint8_t *pd;
	struct  _stat32 s;
	FILE*         fd;
	size_t bytes;
    long l;
    long rest;

	fd = fopen(file_path, "rb");
	if (fd == 0)
	{
		printf("Input file %s does not exist\n", file_path);
		goto open_failed;
	}

	//if (fstat (fd, &s) != 0)
    if (_fstat32(fd->_file, &s) != 0)
	{
		printf("Could not stat input file %s\n", file_path);
		goto stat_failed;
	}

    printf("debug: file size = %d, 0x%x\n",s.st_size, s.st_size);
	l = s.st_size;

    if ((file_content = buf32_Create(4 + l)) == NULL)
	{
		printf("Could not allocate memory for reading file %s\n", file_path);
		goto malloc_failed;
	}

    pd = file_content->buffer;

	rest = l;
	while (rest > 0)
	{
		bytes = fread(pd + (l - rest), 1, rest, fd);
		if (bytes < 0)
		{
			printf("Could not read file %s\n", file_path);
			goto read_failed;
		}
		else if (bytes == 0)
		{
			break;	//end of file
		}
		rest -= bytes;
	}

    file_content->length = l;
	
	// No special error treatment necessary, we need to unmap and close
	// the file anyway.

	fclose(fd);
	
	return file_content;
	
	// Clean up on error.
  read_failed:
    free(file_content);
  
  malloc_failed:
  stat_failed:
    fclose(fd);
  
  open_failed:

	return(0);// NULL;
}