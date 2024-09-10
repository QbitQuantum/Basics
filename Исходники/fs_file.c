int fs_ioctl_handle(int fd, intptr_t req, intptr_t arg) {
  if (!_valid_file(fd)) {
    klogf("lseek: Invalid file %x\n", fd);
    return -1;
  }
 
  FSFile *file = (FSFile*) fd;
  //int reverse = (!!(file->mode & O_PIPE_MODE)) ^ (!!(file->mode & _O_REVERSE));
  int ret = -1; // *cursor = ((file->mode & O_PIPE_MODE) && reverse) ? &file->pipe_rcursor : &file->cursor;
  
  _lock_file(file);
  
  if (file->fs->ioctl) {
    ret = file->fs->ioctl(file->fs, file->device, file->internalfd, req, arg);
  }
  
  _unlock_file(file);
  
  return ret;
}