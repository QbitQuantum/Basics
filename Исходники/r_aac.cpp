int
aac_reader_c::find_valid_headers(mm_io_c &in,
                                 int64_t probe_range,
                                 int num_headers) {
  try {
    in.setFilePointer(0, seek_beginning);
    memory_cptr buf = memory_c::alloc(probe_range);
    int num_read    = in.read(buf->get_buffer(), probe_range);
    in.setFilePointer(0, seek_beginning);

    return find_consecutive_aac_headers(buf->get_buffer(), num_read, num_headers);
  } catch (...) {
    return -1;
  }
}