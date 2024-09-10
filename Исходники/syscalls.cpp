W64 sys_seek(int fd, W64 offset, unsigned int origin) {
  loff_t newoffs;
  int rc = sys_llseek(fd, HI32(offset), LO32(offset), &newoffs, origin);
  return (rc < 0) ? rc : newoffs;
}