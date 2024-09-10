/* This function is for implementation convenience. It is not user-visible.
 * If wr==1 write, wr==0 read.
 *
 * Returns MPI_SUCCESS on success, mpi_errno on failure.
 */
int ADIOI_NTFS_aio(ADIO_File fd, void *buf, int len, ADIO_Offset offset,
		   int wr, MPI_Request *request)
{
    static char myname[] = "ADIOI_NTFS_aio";

    ADIOI_AIO_Request *aio_req;
    static DWORD dwNumWritten, dwNumRead;
    BOOL ret_val = FALSE;
    FDTYPE fd_sys;
    int mpi_errno = MPI_SUCCESS;
    DWORD err;

    fd_sys = fd->fd_sys;

    aio_req = (ADIOI_AIO_Request *)ADIOI_Calloc(sizeof(ADIOI_AIO_Request), 1);
    if (aio_req == NULL)
    {
	mpi_errno = MPIO_Err_create_code(MPI_SUCCESS, MPIR_ERR_RECOVERABLE,
	    myname, __LINE__, MPI_ERR_IO,
	    "**nomem", "**nomem %s", "AIO_REQ");
	return mpi_errno;
    }
    aio_req->lpOvl = (LPOVERLAPPED ) ADIOI_Calloc(sizeof(OVERLAPPED), 1);
    if (aio_req->lpOvl == NULL)
    {
	mpi_errno = MPIO_Err_create_code(MPI_SUCCESS, MPIR_ERR_RECOVERABLE,
	    myname, __LINE__, MPI_ERR_IO,
	    "**nomem", "**nomem %s", "OVERLAPPED");
    ADIOI_Free(aio_req);
	return mpi_errno;
    }
    aio_req->lpOvl->hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (aio_req->lpOvl->hEvent == NULL)
    {
    char errMsg[ADIOI_NTFS_ERR_MSG_MAX];
	err = GetLastError();
    ADIOI_NTFS_Strerror(err, errMsg, ADIOI_NTFS_ERR_MSG_MAX);
	mpi_errno = MPIO_Err_create_code(MPI_SUCCESS, MPIR_ERR_RECOVERABLE,
	    myname, __LINE__, MPI_ERR_IO,
	    "**io", "**io %s", errMsg);
    ADIOI_Free(aio_req->lpOvl);
    ADIOI_Free(aio_req);
	return mpi_errno;
    }
    aio_req->lpOvl->Offset = DWORDLOW(offset);
    aio_req->lpOvl->OffsetHigh = DWORDHIGH(offset);
    aio_req->fd = fd_sys;
    
    /* XXX: initiate async I/O  */
    if (wr)
    {
	ret_val = WriteFile(fd_sys, buf, len, &dwNumWritten, aio_req->lpOvl);
    }
    else
    {
	ret_val = ReadFile(fd_sys, buf, len, &dwNumRead, aio_req->lpOvl);
    }

    /* --BEGIN ERROR HANDLING-- */
    if (ret_val == FALSE) 
    {
	mpi_errno = GetLastError();
	if (mpi_errno != ERROR_IO_PENDING)
	{
        char errMsg[ADIOI_NTFS_ERR_MSG_MAX];
        ADIOI_NTFS_Strerror(mpi_errno, errMsg, ADIOI_NTFS_ERR_MSG_MAX);
	    mpi_errno = MPIO_Err_create_code(MPI_SUCCESS, MPIR_ERR_RECOVERABLE,
		myname, __LINE__, MPI_ERR_IO,
		"**io",
		"**io %s", errMsg);
	    return mpi_errno;
	}
	mpi_errno = MPI_SUCCESS;
    }
    /* --END ERROR HANDLING-- */

    /* XXX: set up generalized request class and request */
    if (ADIOI_NTFS_greq_class == 0) {
	    mpi_errno = MPIX_Grequest_class_create(ADIOI_NTFS_aio_query_fn,
			    ADIOI_NTFS_aio_free_fn, MPIU_Greq_cancel_fn,
			    ADIOI_NTFS_aio_poll_fn, ADIOI_NTFS_aio_wait_fn,
			    &ADIOI_NTFS_greq_class);
        if(mpi_errno != MPI_SUCCESS){
        /* FIXME: Pass appropriate error code to user */
        }
    }
    mpi_errno = MPIX_Grequest_class_allocate(ADIOI_NTFS_greq_class, aio_req, request);
    if(mpi_errno != MPI_SUCCESS){
    /* FIXME: Pass appropriate error code to user */
    }
    memcpy(&(aio_req->req), request, sizeof(MPI_Request));
    return mpi_errno;
}