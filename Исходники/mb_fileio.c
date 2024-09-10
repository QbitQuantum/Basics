/*--------------------------------------------------------------------*/
int mb_fileio_open(int verbose, void *mbio_ptr, int *error)
{
	char	*function_name = "mb_fileio_open";
	int	status = MB_SUCCESS;
	struct mb_io_struct *mb_io_ptr;
	int	fileiobuffer;
	size_t	fileiobufferbytes;
	int	buffer_status = MB_SUCCESS;
	int	buffer_error = MB_ERROR_NO_ERROR;

	/* print input debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> called\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Input arguments:\n");
		fprintf(stderr,"dbg2       verbose:    %d\n",verbose);
		fprintf(stderr,"dbg2       mbio_ptr:   %p\n",(void *)mbio_ptr);
		}

	/* get mbio descriptor */
	mb_io_ptr = (struct mb_io_struct *) mbio_ptr;

	/* open the file for reading */
	if (mb_io_ptr->filemode == MB_FILEMODE_READ)
		{
		if ((mb_io_ptr->mbfp = fopen(mb_io_ptr->file, "r")) == NULL)
			 {
			 *error = MB_ERROR_OPEN_FAIL;
			 status = MB_FAILURE;
			 }
		}
	else if (mb_io_ptr->filemode == MB_FILEMODE_WRITE)
		{
		if ((mb_io_ptr->mbfp = fopen(mb_io_ptr->file, "wb")) == NULL)
			 {
			 *error = MB_ERROR_OPEN_FAIL;
			 status = MB_FAILURE;
			 }
		}

	/* set buffering if desired
		fileiomode: mode of single normal file i/o:
                        0   use fread() and fwrite() with standard buffering
                        >0  use fread() and fwrite() with user defined buffer
                        <0  use mmap for file i/o */
	if (status == MB_SUCCESS)
		{
		mb_fileiobuffer(verbose, &fileiobuffer);
		if (fileiobuffer > 0)
			{
			/* the buffer size must be a multiple of 512, plus 8 to be efficient */
			fileiobufferbytes = (fileiobuffer * 1024) + 8;

			/* allocate the buffer */
			buffer_error = MB_ERROR_NO_ERROR;
			buffer_status = mb_mallocd(verbose,__FILE__, __LINE__, fileiobufferbytes,
							(void **) &mb_io_ptr->file_iobuffer, &buffer_error);

			/* apply the buffer */
			if (buffer_status == MB_SUCCESS)
				{
				buffer_status = setvbuf(mb_io_ptr->mbfp, mb_io_ptr->file_iobuffer, _IOFBF, fileiobufferbytes);
/* printf(stderr,"Called setvbuf size:%d status:%d\n",fileiobufferbytes,buffer_status); */
				}
			}
		}

	/* print output debug statements */
	if (verbose >= 2)
		{
		fprintf(stderr,"\ndbg2  MBIO function <%s> completed\n",function_name);
		fprintf(stderr,"dbg2  Revision id: %s\n",rcs_id);
		fprintf(stderr,"dbg2  Return values:\n");
		fprintf(stderr,"dbg2       error:      %d\n",*error);
		fprintf(stderr,"dbg2  Return status:\n");
		fprintf(stderr,"dbg2       status:  %d\n",status);
		}

	/* return status */
	return(status);
}