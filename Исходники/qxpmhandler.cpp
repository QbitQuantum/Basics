static bool read_xpm_string(QByteArray &buf, QIODevice *d, const char * const *source, int &index,
                            QByteArray &state)
{
    if (source) {
        buf = source[index++];
        return true;
    }

    buf = "";
    bool gotQuote = false;
    int offset = 0;
    forever {
        if (offset == state.size() || state.isEmpty()) {
            char buf[2048];
            qint64 bytesRead = d->read(buf, sizeof(buf));
            if (bytesRead <= 0)
                return false;
            state = QByteArray(buf, int(bytesRead));
            offset = 0;
        }

        if (!gotQuote) {
            if (state.at(offset++) == '"')
                gotQuote = true;
        } else {
            char c = state.at(offset++);
            if (c == '"')
                break;
            buf += c;
        }
    }
    state.remove(0, offset);
    return true;
}