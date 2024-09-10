CAMLprim value caml_ba_map_file(value vfd, value vkind, value vlayout,
                                value vshared, value vdim, value vstart)
{
  HANDLE fd, fmap;
  int flags, major_dim, mode, perm;
  intnat num_dims, i;
  intnat dim[MAX_NUM_DIMS];
  __int64 currpos, startpos, file_size, data_size;
  uintnat array_size, page, delta;
  char c;
  void * addr;
  LARGE_INTEGER li;
  SYSTEM_INFO sysinfo;

  fd = Handle_val(vfd);
  flags = Int_val(vkind) | Int_val(vlayout);
  startpos = Int64_val(vstart);
  num_dims = Wosize_val(vdim);
  major_dim = flags & BIGARRAY_FORTRAN_LAYOUT ? num_dims - 1 : 0;
  /* Extract dimensions from Caml array */
  num_dims = Wosize_val(vdim);
  if (num_dims < 1 || num_dims > MAX_NUM_DIMS)
    invalid_argument("Bigarray.mmap: bad number of dimensions");
  for (i = 0; i < num_dims; i++) {
    dim[i] = Long_val(Field(vdim, i));
    if (dim[i] == -1 && i == major_dim) continue;
    if (dim[i] < 0 || dim[i] > 0x7FFFFFFFL)
      invalid_argument("Bigarray.create: negative dimension");
  }
  /* Determine file size */
  currpos = caml_ba_set_file_pointer(fd, 0, FILE_CURRENT);
  if (currpos == -1) caml_ba_sys_error();
  file_size = caml_ba_set_file_pointer(fd, 0, FILE_END);
  if (file_size == -1) caml_ba_sys_error();
  /* Determine array size in bytes (or size of array without the major
     dimension if that dimension wasn't specified) */
  array_size = bigarray_element_size[flags & BIGARRAY_KIND_MASK];
  for (i = 0; i < num_dims; i++)
    if (dim[i] != -1) array_size *= dim[i];
  /* Check if the first/last dimension is unknown */
  if (dim[major_dim] == -1) {
    /* Determine first/last dimension from file size */
    if (file_size < startpos)
      failwith("Bigarray.mmap: file position exceeds file size");
    data_size = file_size - startpos;
    dim[major_dim] = (uintnat) (data_size / array_size);
    array_size = dim[major_dim] * array_size;
    if (array_size != data_size)
      failwith("Bigarray.mmap: file size doesn't match array dimensions");
  }
  /* Restore original file position */
  caml_ba_set_file_pointer(fd, currpos, FILE_BEGIN);
  /* Create the file mapping */
  if (Bool_val(vshared)) {
    perm = PAGE_READWRITE;
    mode = FILE_MAP_WRITE;
  } else {
    perm = PAGE_READONLY;       /* doesn't work under Win98 */
    mode = FILE_MAP_COPY;
  }
  li.QuadPart = startpos + array_size;
  fmap = CreateFileMapping(fd, NULL, perm, li.HighPart, li.LowPart, NULL);
  if (fmap == NULL) caml_ba_sys_error();
  /* Determine offset so that the mapping starts at the given file pos */
  GetSystemInfo(&sysinfo);
  delta = (uintnat) (startpos % sysinfo.dwPageSize);
  /* Map the mapping in memory */
  li.QuadPart = startpos - delta;
  addr = 
    MapViewOfFile(fmap, mode, li.HighPart, li.LowPart, array_size + delta);
  if (addr == NULL) caml_ba_sys_error();
  addr = (void *) ((uintnat) addr + delta);
  /* Close the file mapping */
  CloseHandle(fmap);
  /* Build and return the Caml bigarray */
  return alloc_bigarray(flags | BIGARRAY_MAPPED_FILE, num_dims, addr, dim);
}