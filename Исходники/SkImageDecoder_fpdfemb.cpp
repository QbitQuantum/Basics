    static FPDFEMB_RESULT file_readblock(FPDFEMB_FILE_ACCESS* file, void* dst,
                                    unsigned int offset, unsigned int size) {
        SkStream* stream = (SkStream*)file->user;
//        SkDebugf("---- readblock %p %p %d %d\n", stream, dst, offset, size);
        if (!stream->rewind()) {
            SkDebugf("---- rewind failed\n");
            return FPDFERR_ERROR;
        }
        if (stream->skip(offset) != offset) {
            SkDebugf("---- skip failed\n");
            return FPDFERR_ERROR;
        }
        if (stream->read(dst, size) != size) {
            SkDebugf("---- read failed\n");
            return FPDFERR_ERROR;
        }
        return FPDFERR_SUCCESS;
    }