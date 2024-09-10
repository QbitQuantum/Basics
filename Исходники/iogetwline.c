_IO_size_t
_IO_getwline_info (_IO_FILE *fp, wchar_t *buf, _IO_size_t n, wint_t delim,
		   int extract_delim, wint_t *eof)
{
  wchar_t *ptr = buf;
  if (eof != NULL)
    *eof = 0;
  if (__builtin_expect (fp->_mode, 1) == 0)
    _IO_fwide (fp, 1);
  while (n != 0)
    {
      _IO_ssize_t len = (fp->_wide_data->_IO_read_end
			 - fp->_wide_data->_IO_read_ptr);
      if (len <= 0)
	{
	  wint_t wc = __wuflow (fp);
	  if (wc == WEOF)
	    {
	      if (eof)
		*eof = wc;
	      break;
	    }
	  if (wc == delim)
	    {
 	      if (extract_delim > 0)
		*ptr++ = wc;
	      else if (extract_delim < 0)
		_IO_sputbackc (fp, wc);
	      if (extract_delim > 0)
		++len;
	      return ptr - buf;
	    }
	  *ptr++ = wc;
	  n--;
	}
      else
	{
	  wchar_t *t;
	  if ((_IO_size_t) len >= n)
	    len = n;
	  t = wmemchr ((void *) fp->_wide_data->_IO_read_ptr, delim, len);
	  if (t != NULL)
	    {
	      _IO_size_t old_len = ptr - buf;
	      len = t - fp->_wide_data->_IO_read_ptr;
	      if (extract_delim >= 0)
		{
		  ++t;
		  if (extract_delim > 0)
		    ++len;
		}
	      wmemcpy ((void *) ptr, (void *) fp->_wide_data->_IO_read_ptr,
		       len);
	      fp->_wide_data->_IO_read_ptr = t;
	      return old_len + len;
	    }
	  wmemcpy ((void *) ptr, (void *) fp->_wide_data->_IO_read_ptr, len);
	  fp->_wide_data->_IO_read_ptr += len;
	  ptr += len;
	  n -= len;
	}
    }
  return ptr - buf;
}