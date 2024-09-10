Tsubtitle* TsubtitleParserSubviewer2::parse(Tstream &fd, int flags, REFERENCE_TIME start, REFERENCE_TIME stop)
{
    wchar_t line[this->LINE_LEN + 1];
    int a1, a2, a3, a4;
    wchar_t *p = NULL;
    int len;
    TsubtitleText current(this->format);
    while (!current.size()) {
        if (!fd.fgets(line, this->LINE_LEN)) {
            return NULL;
        }
        if (line[0] != '{') {
            continue;
        }
        if ((len = swscanf(line, L"{T %d:%d:%d:%d", &a1, &a2, &a3, &a4)) < 4) {
            continue;
        }
        current.start = this->hmsToTime(a1, a2, a3, a4);
        for (/*i=0*/;;) {
            if (!fd.fgets(line, this->LINE_LEN)) {
                goto end;    //break;
            }
            if (line[0] == '}') {
                break;
            }
            len = 0;
            for (p = line; *p != '\n' && *p != '\r' && *p; ++p, ++len) {
                ;
            }
            if (len) {
                current.add(line, len);
            } else {
                break;
            }
        }
        //current->lines=i;
    }
end:
    return current.empty() ? NULL : store(current);
}