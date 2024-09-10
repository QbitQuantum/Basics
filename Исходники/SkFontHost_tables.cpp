size_t SkFontHost::GetTableData(SkFontID fontID, SkFontTableTag tag,
                                size_t offset, size_t length, void* data) {
    SkStream* stream = SkFontHost::OpenStream(fontID);
    if (NULL == stream) {
        return 0;
    }

    SkAutoUnref au(stream);
    SfntHeader  header;
    if (!header.init(stream)) {
        return 0;
    }

    for (int i = 0; i < header.fCount; i++) {
        if (SkEndian_SwapBE32(header.fDir[i].fTag) == tag) {
            size_t realOffset = SkEndian_SwapBE32(header.fDir[i].fOffset);
            size_t realLength = SkEndian_SwapBE32(header.fDir[i].fLength);
            // now sanity check the caller's offset/length
            if (offset >= realLength) {
                return 0;
            }
            // if the caller is trusting the length from the file, then a
            // hostile file might choose a value which would overflow offset +
            // length.
            if (offset + length < offset) {
                return 0;
            }
            if (offset + length > realLength) {
                length = realLength - offset;
            }
            // skip the stream to the part of the table we want to copy from
            stream->rewind();
            size_t bytesToSkip = realOffset + offset;
            if (stream->skip(bytesToSkip) != bytesToSkip) {
                return 0;
            }
            if (stream->read(data, length) != length) {
                return 0;
            }
            return length;
        }
    }
    return 0;
}