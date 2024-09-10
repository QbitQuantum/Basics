void sbuf_stream::getUTF16(wstring &utf16_string) {
    sbuf.getUTF16(offset, utf16_string);
    size_t num_bytes = utf16_string.length() * 2;
    if (num_bytes > 0) {
        // if anything was read then also skip \U0000
        num_bytes += 2;
    }
    offset += num_bytes;
    return;
}