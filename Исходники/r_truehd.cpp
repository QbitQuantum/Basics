bool
truehd_reader_c::find_valid_headers(mm_io_c &in,
                                    int64_t probe_range,
                                    int num_headers) {
  try {
    memory_cptr buf(memory_c::alloc(probe_range));

    in.setFilePointer(0, seek_beginning);
    skip_id3v2_tag(in);

    int num_read = in.read(buf->get_buffer(), probe_range);

    truehd_parser_c parser;
    parser.add_data(buf->get_buffer(), num_read);

    int num_sync_frames = 0;
    while (parser.frame_available()) {
      truehd_frame_cptr frame = parser.get_next_frame();
      if (frame->is_sync())
        ++num_sync_frames;
    }

    return num_sync_frames >= num_headers;

  } catch (...) {
    return false;
  }
}