int
ac3_reader_c::find_valid_headers(mm_io_c &in,
                                 int64_t probe_range,
                                 int num_headers) {
  try {
    memory_cptr buf(memory_c::alloc(probe_range));

    in.setFilePointer(0, seek_beginning);
    skip_id3v2_tag(in);

    ac3::parser_c parser;
    int num_read = in.read(buf->get_buffer(), probe_range);
    int pos      = parser.find_consecutive_frames(buf->get_buffer(), num_read, num_headers);

    in.setFilePointer(0, seek_beginning);

    return pos;

  } catch (...) {
    return -1;
  }
}