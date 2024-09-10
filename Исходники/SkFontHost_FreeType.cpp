    static unsigned long sk_stream_read(FT_Stream       stream,
                                        unsigned long   offset,
                                        unsigned char*  buffer,
                                        unsigned long   count ) {
        SkStream* str = (SkStream*)stream->descriptor.pointer;

        if (count) {
            if (!str->rewind()) {
                return 0;
            } else {
                unsigned long ret;
                if (offset) {
                    ret = str->read(NULL, offset);
                    if (ret != offset) {
                        return 0;
                    }
                }
                ret = str->read(buffer, count);
                if (ret != count) {
                    return 0;
                }
                count = ret;
            }
        }
        return count;
    }