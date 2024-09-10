enum pipe_error
pb_validate_add_buffer(struct pb_validate *vl,
                       struct pb_buffer *buf)
{
    assert(buf);
    if(!buf)
        return PIPE_ERROR;

    /* We only need to store one reference for each buffer, so avoid storing
     * consecutive references for the same buffer. It might not be the more
     * common pasttern, but it is easy to implement.
     */
    if(vl->used && vl->buffers[vl->used - 1] == buf) {
        return PIPE_OK;
    }

    /* Grow the table */
    if(vl->used == vl->size) {
        unsigned new_size;
        struct pb_buffer **new_buffers;

        new_size = vl->size * 2;
        if(!new_size)
            return PIPE_ERROR_OUT_OF_MEMORY;

        new_buffers = (struct pb_buffer **)REALLOC(vl->buffers,
        vl->size*sizeof(struct pb_buffer *),
        new_size*sizeof(struct pb_buffer *));
        if(!new_buffers)
            return PIPE_ERROR_OUT_OF_MEMORY;

        memset(new_buffers + vl->size, 0, (new_size - vl->size)*sizeof(struct pb_buffer *));

        vl->size = new_size;
        vl->buffers = new_buffers;
    }

    assert(!vl->buffers[vl->used]);
    pb_reference(&vl->buffers[vl->used], buf);
    ++vl->used;

    return PIPE_OK;
}