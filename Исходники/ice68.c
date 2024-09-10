void *ice_load(istream_t *is, int *ulen)
{
  char header[12], *inbuf = 0, * outbuf = 0;
  int dsize, csize;
  const char * fname;

  fname = istream_filename(is);

  if (istream_read(is,header,12) != 12) {
    SC68error_add("ice_load(%s) : no header", fname);
    goto error;
  }

  csize = 0;
  dsize = unice68_get_depacked_size(header, &csize);

  if (dsize < 0) {
    SC68error_add("ice_load(%s) : not ICE!", fname);
    goto error;
  }

  inbuf = SC68alloc(csize + 12);

  if (!inbuf) {
    SC68error_add("ice_load(%s) : alloc input buffer failed", fname);
    goto error;
  }

  memcpy(inbuf,header,12);
  if (istream_read(is,inbuf+12,csize) != csize) {
    SC68error_add("ice_load(%s) : read failed", fname);
    goto error;
  }

  outbuf = SC68alloc(dsize);

  if (!outbuf) {
    SC68error_add("ice_load(%s) : alloc output buffer failed", fname);
    goto error;
  }

  if (!unice68_depacker(outbuf, inbuf)) {
    goto success;
  }
  
 error:

  SC68free(outbuf);
  outbuf = 0;
  dsize = 0;
 success:
  SC68free(inbuf);
  if (ulen) {
    *ulen = dsize;
  }
  return outbuf;
}