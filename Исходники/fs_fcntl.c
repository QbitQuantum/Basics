static inline int file_vfcntl(int fildes, int cmd, va_list ap)
{
  FAR struct filelist *list;
  FAR struct file *this_file;
  int err = 0;
  int ret = OK;

  /* Get the thread-specific file list */

  list = sched_getfiles();
  if (!list)
    {
      err = EMFILE;
      goto errout;
    }

  /* Was this file opened ? */

  this_file = &list->fl_files[fildes];
  if (!this_file->f_inode)
    {
      err = EBADF;
      goto errout;
    }

  switch (cmd)
    {
      case F_DUPFD:
        /* Return a new file descriptor which shall be the lowest numbered
         * available (that is, not already open) file descriptor greater than
         * or equal to the third argument, arg, taken as an integer of type
         * int. The new file descriptor shall refer to the same open file
         * description as the original file descriptor, and shall share any
         * locks.  The FD_CLOEXEC flag associated  with the new file descriptor
         * shall be cleared to keep the file open across calls to one of the
         * exec functions.
         */

        {
          ret = file_dup(fildes, va_arg(ap, int));
        }
        break;

      case F_GETFD:
        /* Get the file descriptor flags defined in <fcntl.h> that are associated
         * with the file descriptor fildes.  File descriptor flags are associated
         * with a single file descriptor and do not affect other file descriptors
         * that refer to the same file.
         */

      case F_SETFD:
        /* Set the file descriptor flags defined in <fcntl.h>, that are associated
         * with fildes, to the third argument, arg, taken as type int. If the
         * FD_CLOEXEC flag in the third argument is 0, the file shall remain open
         * across the exec functions; otherwise, the file shall be closed upon
         * successful execution of one  of  the  exec  functions.
         */

        err = ENOSYS;
        break;

      case F_GETFL:
        /* Get the file status flags and file access modes, defined in <fcntl.h>,
         * for the file description associated with fildes. The file access modes
         * can be extracted from the return value using the mask O_ACCMODE, which is
         * defined  in <fcntl.h>. File status flags and file access modes are associated
         * with the file description and do not affect other file descriptors that
         * refer to the same file with different open file descriptions.
         */

        {
          ret = this_file->f_oflags;
        }
        break;

      case F_SETFL:
        /* Set the file status flags, defined in <fcntl.h>, for the file description
         * associated with fildes from the corresponding  bits in the third argument,
         * arg, taken as type int. Bits corresponding to the file access mode and
         * the file creation flags, as defined in <fcntl.h>, that are set in arg shall
         * be ignored. If any bits in arg other than those mentioned here are changed
         * by the application, the result is unspecified.
         */

        {
          int oflags = va_arg(ap, int);

          oflags              &=  FFCNTL;
          this_file->f_oflags &= ~FFCNTL;
          this_file->f_oflags |=  oflags;
        }
        break;

      case F_GETOWN:
        /* If fildes refers to a socket, get the process or process group ID specified
         * to receive SIGURG signals when out-of-band data is available. Positive values
         * indicate a process ID; negative values, other than -1, indicate a process group
         * ID. If fildes does not refer to a socket, the results are unspecified.
         */

      case F_SETOWN:
        /* If fildes refers to a socket, set the process or process group ID specified
         * to receive SIGURG signals when out-of-band data is available, using the value
         * of the third argument, arg, taken as type int. Positive values indicate a 
         * process ID; negative values, other than -1, indicate a process group ID. If
         * fildes does not refer to a socket, the results are unspecified.
         */

        err = EBADF; /* Only valid on socket descriptors */
        break;

      case F_GETLK:
        /* Get the first lock which blocks the lock description pointed to by the third
         * argument, arg, taken as a pointer to type struct flock, defined in <fcntl.h>.
         * The information retrieved shall overwrite the information passed to fcntl() in
         * the structure flock. If no lock is found that would prevent this lock from being
         * created, then the structure shall be left unchanged except for the lock type
         * which shall be set to F_UNLCK.
         */

      case F_SETLK:
        /* Set or clear a file segment lock according to the lock description pointed to
         * by the third argument, arg, taken as a pointer to type struct flock, defined in
         * <fcntl.h>. F_SETLK can establish shared (or read) locks (F_RDLCK) or exclusive
         * (or write) locks (F_WRLCK), as well  as  to  remove  either  type  of  lock  (F_UNLCK).
         * F_RDLCK, F_WRLCK, and F_UNLCK are defined in <fcntl.h>. If a shared or exclusive
         * lock cannot be set, fcntl() shall return immediately with a return value of -1.
         */

      case F_SETLKW:
        /* This command shall be equivalent to F_SETLK except that if a shared or exclusive
         * lock is blocked by other locks, the thread shall wait until the request can be
         * satisfied. If a signal that is to be caught is received while fcntl() is waiting
         * for a region, fcntl() shall be interrupted. Upon return from the signal handler,
         * fcntl() shall return -1 with errno set to [EINTR], and the lock operation shall
         * not be done.
         */

        err = ENOSYS; /* Not implemented */
        break;

      default:
        err = EINVAL;
        break;
    }

errout:
  if (err != 0)
    {
      set_errno(err);
      return ERROR;
    }

  return ret;
}