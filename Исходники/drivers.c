static int win32_getiftable(struct ifstat_driver *driver,
			    PMIB_IFTABLE *iftable) {
  struct win32_driver_data *data = driver->data;
  ULONG size;
  DWORD ret;

  size = data->len;
  while ((ret = GetIfTable((PMIB_IFTABLE) data->buf,
			   &size, 1)) == ERROR_INSUFFICIENT_BUFFER) {
    data->len = size * 2;
    if ((data->buf = realloc(data->buf, data->len)) == NULL) {
      perror("realloc");
      return 0;
    }
  }
  
  if (ret == NO_ERROR) {
    *iftable = (PMIB_IFTABLE) data->buf;
    return 1;
  }
  
  perror("GetIfTable");
  return 0;
}