mm_read_buffer_io_c::mm_read_buffer_io_c(mm_io_c *in,
                                         size_t buffer_size,
                                         bool delete_in)
  : mm_proxy_io_c(in, delete_in)
  , m_af_buffer(memory_c::alloc(buffer_size))
  , m_buffer(m_af_buffer->get_buffer())
  , m_cursor(0)
  , m_eof(false)
  , m_fill(0)
  , m_offset(0)
  , m_size(buffer_size)
  , m_buffering(true)
  , m_debug_seek(debugging_requested("read_buffer_io") || debugging_requested("read_buffer_io_read"))
  , m_debug_read(debugging_requested("read_buffer_io") || debugging_requested("read_buffer_io_read"))
{
  setFilePointer(0, seek_beginning);
}