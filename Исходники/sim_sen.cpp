TWCHAR &
SIMCharReaderIterator::operator*() const
{
    FILE *fp = reader->fp;
    std::deque<TWCHAR> & buf = reader->buf;

    for (int i = buf.size(); i <= idx; ) {
        wint_t wch = fgetwc(fp);
        if (wch == 0) {
            wch = 0x20; // make it like a space
        }
        if (wch == WEOF) {
            if (feof(fp)) {
                buf.push_back(TWCHAR(0));
                return buf.back();
            } else {
                fprintf(stderr, "File read error %d\n", ferror(fp));
                throw new int(60);
            }
        } else {
            buf.push_back(wch);
            ++i;
        }
    }
    if (idx >= (int) buf.size() && buf.back() == WCH_NULL)
        return buf.back();
    return buf[idx];
}