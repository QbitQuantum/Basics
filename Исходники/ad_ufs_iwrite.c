int ADIOI_UFS_aio(ADIO_File fd, void *buf, int len, ADIO_Offset offset,
		  int wr, void *handle)
{
    int err=-1, fd_sys;

#ifndef NO_AIO
    int error_code;
#ifdef AIO_SUN 
    aio_result_t *result;
#else
    struct aiocb *aiocbp;
#endif
#endif

    fd_sys = fd->fd_sys;

#ifdef AIO_SUN
    result = (aio_result_t *) ADIOI_Malloc(sizeof(aio_result_t));
    result->aio_return = AIO_INPROGRESS;
    if (wr) err = aiowrite(fd_sys, buf, len, offset, SEEK_SET, result); 
    else err = aioread(fd_sys, buf, len, offset, SEEK_SET, result);

    if (err == -1) {
	if (errno == EAGAIN) { 
       /* the man pages say EPROCLIM, but in reality errno is set to EAGAIN! */

        /* exceeded the max. no. of outstanding requests.
           complete all previous async. requests and try again.*/

	    ADIOI_Complete_async(&error_code);
	    if (wr) err = aiowrite(fd_sys, buf, len, offset, SEEK_SET, result); 
	    else err = aioread(fd_sys, buf, len, offset, SEEK_SET, result);

	    while (err == -1) {
		if (errno == EAGAIN) {
                    /* sleep and try again */
                    sleep(1);
		    if (wr) err = aiowrite(fd_sys, buf, len, offset, SEEK_SET, result); 
		    else err = aioread(fd_sys, buf, len, offset, SEEK_SET, result);
		}
                else {
                    FPRINTF(stderr, "Unknown errno %d in ADIOI_UFS_aio\n", errno);
                    MPI_Abort(MPI_COMM_WORLD, 1);
                }
	    }
	}
        else {
            FPRINTF(stderr, "Unknown errno %d in ADIOI_UFS_aio\n", errno);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    *((aio_result_t **) handle) = result;
#endif

#ifdef NO_FD_IN_AIOCB
/* IBM */
    aiocbp = (struct aiocb *) ADIOI_Malloc(sizeof(struct aiocb));
    aiocbp->aio_whence = SEEK_SET;
    aiocbp->aio_offset = offset;
    aiocbp->aio_buf = buf;
    aiocbp->aio_nbytes = len;
    if (wr) err = aio_write(fd_sys, aiocbp);
    else err = aio_read(fd_sys, aiocbp);

    if (err == -1) {
	if (errno == EAGAIN) {
        /* exceeded the max. no. of outstanding requests.
          complete all previous async. requests and try again. */

	    ADIOI_Complete_async(&error_code);
	    if (wr) err = aio_write(fd_sys, aiocbp);
	    else err = aio_read(fd_sys, aiocbp);

            while (err == -1) {
                if (errno == EAGAIN) {
                    /* sleep and try again */
                    sleep(1);
		    if (wr) err = aio_write(fd_sys, aiocbp);
		    else err = aio_read(fd_sys, aiocbp);
		}
                else {
                    FPRINTF(stderr, "Unknown errno %d in ADIOI_UFS_aio\n", errno);
                    MPI_Abort(MPI_COMM_WORLD, 1);
                }
            }
	}
        else {
            FPRINTF(stderr, "Unknown errno %d in ADIOI_UFS_aio\n", errno);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    *((struct aiocb **) handle) = aiocbp;

#elif (!defined(NO_AIO) && !defined(AIO_SUN))
/* DEC, SGI IRIX 5 and 6 */

    aiocbp = (struct aiocb *) ADIOI_Calloc(sizeof(struct aiocb), 1);
    aiocbp->aio_fildes = fd_sys;
    aiocbp->aio_offset = offset;
    aiocbp->aio_buf = buf;
    aiocbp->aio_nbytes = len;

#ifdef AIO_PRIORITY_DEFAULT
/* DEC */
    aiocbp->aio_reqprio = AIO_PRIO_DFL;   /* not needed in DEC Unix 4.0 */
    aiocbp->aio_sigevent.sigev_signo = 0;
#else
    aiocbp->aio_reqprio = 0;
#endif

#ifdef AIO_SIGNOTIFY_NONE
/* SGI IRIX 6 */
    aiocbp->aio_sigevent.sigev_notify = SIGEV_NONE;
#else
    aiocbp->aio_sigevent.sigev_signo = 0;
#endif

    if (wr) err = aio_write(aiocbp);
    else err = aio_read(aiocbp);

    if (err == -1) {
	if (errno == EAGAIN) {
        /* exceeded the max. no. of outstanding requests.
           complete all previous async. requests and try again. */

	    ADIOI_Complete_async(&error_code);
	    if (wr) err = aio_write(aiocbp);
	    else err = aio_read(aiocbp);

	    while (err == -1) {
		if (errno == EAGAIN) {
		    /* sleep and try again */
		    sleep(1);
		    if (wr) err = aio_write(aiocbp);
		    else err = aio_read(aiocbp);
		}
		else {
		    FPRINTF(stderr, "Unknown errno %d in ADIOI_UFS_aio\n", errno);
		    MPI_Abort(MPI_COMM_WORLD, 1);
		}
	    }
        }
	else {
	    FPRINTF(stderr, "Unknown errno %d in ADIOI_UFS_aio\n", errno);
	    MPI_Abort(MPI_COMM_WORLD, 1);
	}
    }

    *((struct aiocb **) handle) = aiocbp;
#endif

    return err;
}