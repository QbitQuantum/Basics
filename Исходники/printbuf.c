void printbuf(printbuf_t* buf, const char* fmt, ...)
{
  size_t avail = buf->size - buf->offset;
  va_list ap;

  va_start(ap, fmt);
  int r = vsnprintf(buf->m + buf->offset, avail, fmt, ap);
  va_end(ap);

  if(r < 0)
  {
#ifdef PLATFORM_IS_WINDOWS
    va_start(ap, fmt);
    r = _vscprintf(fmt, ap);
    va_end(ap);

    if(r < 0)
      return;
#else
    return;
#endif
  }

  if((size_t)r >= avail)
  {
    size_t new_size = buf->size + r + 1;
    buf->m = (char*)ponyint_pool_realloc_size(buf->size, new_size, buf->m);
    buf->size = new_size;
    avail = buf->size - buf->offset;

    va_start(ap, fmt);
    r = vsnprintf(buf->m + buf->offset, avail, fmt, ap);
    va_end(ap);

    pony_assert((r > 0) && ((size_t)r < buf->size));
  }

  buf->offset += r;
}