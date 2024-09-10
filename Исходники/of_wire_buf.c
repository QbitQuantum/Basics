void
of_wire_buffer_replace_data(of_wire_buffer_t *wbuf,
                            int offset,
                            int old_len,
                            uint8_t *data,
                            int new_len)
{
    int bytes;
    uint8_t *src_ptr, *dst_ptr;
    int cur_bytes;

    ASSERT(wbuf != NULL);

    cur_bytes = wbuf->current_bytes;

    /* Doesn't make sense; mismatch in current buffer info */
    ASSERT(old_len + offset <= wbuf->current_bytes);

    if (old_len < new_len) {
        of_wire_buffer_grow(wbuf, offset + new_len);
    } else {
        wbuf->current_bytes += (new_len - old_len); // may decrease size
    }

    if ((old_len + offset < cur_bytes) && (old_len != new_len)) {
        /* Need to move back of buffer */
        src_ptr = &wbuf->buf[offset + old_len];
        dst_ptr = &wbuf->buf[offset + new_len];
        bytes = cur_bytes - (offset + old_len);
        MEMMOVE(dst_ptr, src_ptr, bytes);
    }

    dst_ptr = &wbuf->buf[offset];
    MEMCPY(dst_ptr, data, new_len);

    ASSERT(wbuf->current_bytes == cur_bytes + (new_len - old_len));
}