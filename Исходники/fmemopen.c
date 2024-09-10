FILE *
fmemopen (void *buf, size_t len, const char *mode)
{
  cookie_io_functions_t iof;
  fmemopen_cookie_t *c;

  if (__builtin_expect (len == 0, 0))
    {
    einval:
      __set_errno (EINVAL);
      return NULL;
    }

  c = (fmemopen_cookie_t *) malloc (sizeof (fmemopen_cookie_t));
  if (c == NULL)
    return NULL;

  c->mybuffer = (buf == NULL);

  if (c->mybuffer)
    {
      c->buffer = (char *) malloc (len);
      if (c->buffer == NULL)
	{
	  free (c);
	  return NULL;
	}
      c->buffer[0] = '\0';
      c->maxpos = 0;
    }
  else
    {
      if (__builtin_expect ((uintptr_t) len > -(uintptr_t) buf, 0))
	{
	  free (c);
	  goto einval;
	}

      c->buffer = buf;

      if (mode[0] == 'w')
	c->buffer[0] = '\0';

      c->maxpos = strnlen (c->buffer, len);
    }

  c->size = len;

  if (mode[0] == 'a')
    c->pos = c->maxpos;
  else
    c->pos = 0;

  c->binmode = mode[0] != '\0' && mode[1] == 'b';

  iof.read = fmemopen_read;
  iof.write = fmemopen_write;
  iof.seek = fmemopen_seek;
  iof.close = fmemopen_close;

  return _IO_fopencookie (c, mode, iof);
}