static void
show_fstat_error (void)
{	static const char *filename = "fstat.dat" ;
	static char data [256] ;

	STATBUF 	statbuf ;
	int fd, mode, flags ;

	if (sizeof (statbuf.st_size) != sizeof (INT64))
	{	printf ("\n\nLine %d: Error, sizeof (statbuf.st_size) != 8.\n\n", __LINE__) ;
		return ;
		} ;

	puts ("\n64 bit fstat() test.\n--------------------") ;

	printf ("0) Create a file, write %d bytes and close it.\n", SIGNED_SIZEOF (data)) ;
	mode = O_WRONLY | O_CREAT | O_TRUNC | O_BINARY ;
	flags = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH ;
	if ((fd = open (filename, mode, flags)) < 0)
	{	printf ("\n\nLine %d: open() failed : %s\n\n", __LINE__, strerror (errno)) ;
		return ;
		} ;
	assert (write (fd, data, sizeof (data)) > 0) ;
	close (fd) ;

	printf ("1) Re-open file in read/write mode and write another %d bytes at the end.\n", SIGNED_SIZEOF (data)) ;
	mode = O_RDWR | O_BINARY ;
	flags = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH ;
	if ((fd = open (filename, mode, flags)) < 0)
	{	printf ("\n\nLine %d: open() failed : %s\n\n", __LINE__, strerror (errno)) ;
		return ;
		} ;
	LSEEK (fd, 0, SEEK_END) ;
	assert (write (fd, data, sizeof (data)) > 0) ;

	printf ("2) Now use system (\"%s %s\") to show the file length.\n\n", dir_cmd, filename) ;

	/* Would use snprintf, but thats not really available on windows. */
	memset (data, 0, sizeof (data)) ;
	strncpy (data, dir_cmd, sizeof (data) - 1) ;
	strncat (data, " ", sizeof (data) - 1 - strlen (data)) ;
	strncat (data, filename, sizeof (data) - 1 - strlen (data)) ;

	assert (system (data) >= 0) ;
	puts ("") ;

	printf ("3) Now use fstat() to get the file length.\n") ;
	if (FSTAT (fd, &statbuf) != 0)
	{	printf ("\n\nLine %d: fstat() returned error : %s\n", __LINE__, strerror (errno)) ;
		return ;
		} ;

	printf ("4) According to fstat(), the file length is %ld, ", (long) statbuf.st_size) ;

	close (fd) ;

	if (statbuf.st_size != 2 * sizeof (data))
		printf ("but thats just plain ***WRONG***.\n\n") ;
	else
	{	printf ("which is correct.\n\n") ;
		unlink (filename) ;
		} ;

} /* show_fstat_error */