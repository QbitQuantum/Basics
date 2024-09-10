int file_fsync(unsigned int file_id, int thread_id)
{
  FILE_DESCRIPTOR fd = files[file_id];
#ifdef HAVE_LIBAIO
  struct iocb iocb;
#else
  (void)thread_id; /* unused */
#endif

  /*
    FIXME: asynchronous fsync support is missing
    in Linux kernel at the moment
  */
  if (file_io_mode == FILE_IO_MODE_SYNC
      || file_io_mode == FILE_IO_MODE_ASYNC
#if defined(HAVE_MMAP) && SIZEOF_SIZE_T == 4
      /* Use fsync in mmaped mode on 32-bit architectures */
      || file_io_mode == FILE_IO_MODE_MMAP
#endif
      )
  {
    if (file_fsync_mode == FSYNC_ALL)
#ifndef _WIN32
      return fsync(fd);
#else
      return !FlushFileBuffers(fd);
#endif

#ifdef HAVE_FDATASYNC    
    return fdatasync(fd);
#else
    log_text(LOG_ALERT, "Unknown fsync mode: %d", file_fsync_mode);
    return -1;
#endif

  }
#ifdef HAVE_LIBAIO
  else if (file_io_mode == FILE_IO_MODE_ASYNC)
  {
    /* Use asynchronous fsync */
    if (file_fsync_mode == FSYNC_ALL)
      io_prep_fsync(&iocb, fd);
    else
      io_prep_fdsync(&iocb, fd);

    return file_submit_or_wait(&iocb, FILE_OP_TYPE_FSYNC, 0, thread_id);
  }
#endif
#ifdef HAVE_MMAP
  /* Use msync on file on 64-bit architectures */
  else if (file_io_mode == FILE_IO_MODE_MMAP)
  {
#ifndef _WIN32
    msync(mmaps[file_id], file_size, MS_SYNC | MS_INVALIDATE);
#else
    FlushViewOfFile(mmaps[file_id], (size_t)file_size);
#endif
  }
#endif
  
  return 1; /* Unknown I/O mode */
}