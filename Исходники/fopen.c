/*
 * @implemented
 */
FILE* _wfopen(const wchar_t *file, const wchar_t *mode)
{
  FILE *f;
  int fd, rw, oflags = 0;
   
  if (file == 0)
    return 0;
  if (mode == 0)
    return 0;

  f = __alloc_file();
  if (f == NULL)
    return NULL;

  rw = (wcschr(mode, L'+') == NULL) ? 0 : 1;
  if (wcschr(mode, L'a'))
    oflags = O_CREAT | (rw ? O_RDWR : O_WRONLY);
  if (wcschr(mode, L'r'))
    oflags = rw ? O_RDWR : O_RDONLY;
  if (wcschr(mode, L'w'))
    oflags = O_TRUNC | O_CREAT | (rw ? O_RDWR : O_WRONLY);
  if (wcschr(mode, L't'))
    oflags |= O_TEXT;
  else if (wcschr(mode, L'b'))
    oflags |= O_BINARY;
  else
    oflags |= (_fmode & (O_TEXT|O_BINARY));

  fd = _wopen(file, oflags, 0);
  if (fd < 0)
    return NULL;

// msvcrt ensures that writes will end up at the end of file in append mode
// we just move the file pointer to the end of file initially
  if (wcschr(mode, 'a'))
    lseek(fd, 0, SEEK_END);

  f->_cnt = 0;
  f->_file = fd;
  f->_bufsiz = 0;
  if (rw)
    f->_flag = _IOREAD | _IOWRT;
  else if (wcschr(mode, L'r'))
    f->_flag = _IOREAD;
  else
    f->_flag = _IOWRT;

  if (wcschr(mode, L't'))
    f->_flag |= _IOTEXT;
  else if (wcschr(mode, L'b'))
    f->_flag |= _IOBINARY;
  else if (_fmode & O_BINARY)
    f->_flag |= _IOBINARY;

  f->_base = f->_ptr = NULL;
  return f;
}