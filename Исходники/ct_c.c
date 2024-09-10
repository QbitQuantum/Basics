void mltds_binding_buffer_finalize(value buffer)
{
    struct binding_buffer* buf = buffer_ptr(buffer);
    free(buf->data);
    free(buf);
}