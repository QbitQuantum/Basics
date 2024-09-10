void putData(ivc_connection_t *con, void *buffer, size_t size)
{
  void *buf_cur = buffer, *buf_end = (void*)((uintptr_t)buffer + size);
  unsigned long item_size = size;
  uint32_t avail, wrt_amount;

  assert( con->outbuf );

  /* wait until we have enough data to write the size, then do so */
  do { avail = con->outsize - getAvail(con->outmod, con->output); }
    while(avail < sizeof(unsigned long));
  writeRaw(con, &item_size, sizeof(unsigned long));

  /* write out the data */
  while(buf_cur < buf_end) {
    avail = con->outsize - getAvail(con->outmod, con->output);
    wrt_amount = (avail > item_size) ? item_size : avail;
    if(wrt_amount > 0) {
      writeRaw(con, buf_cur, wrt_amount);
      buf_cur = (void*)((uintptr_t)buf_cur + wrt_amount);
      item_size -= wrt_amount;
    } else usleep(0);
  }
  assert(item_size == 0);
}