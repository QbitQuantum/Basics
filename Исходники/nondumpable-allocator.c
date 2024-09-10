gpointer
nondumpable_buffer_alloc(gsize len)
{
  gsize minimum_size = len + ALLOCATION_HEADER_SIZE;
  gsize pagesize = sysconf(_SC_PAGE_SIZE);
  gsize alloc_size = round_to_nearest(minimum_size, pagesize);

  Allocation *buffer = _mmap(alloc_size);
  if (buffer == MAP_FAILED)
    return NULL;

  buffer->alloc_size = alloc_size;
  buffer->data_len = len;
  return buffer->user_data;
}