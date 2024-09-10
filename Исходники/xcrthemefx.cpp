bool XCursorThemeFX::str2num (const QString &s, quint32 &res) {
    quint64 n = 0;
    if (s.isEmpty()) return false;
    for (int f = 0; f < s.length(); f++) {
        QChar ch = s.at(f);
        if (!ch.isDigit()) return false;
        n = n*10+ch.unicode()-'0';
    }
    //if (n >= (quint64)0x100000000LL) n = 0xffffffffLL;
    if (n >= (quint64)0x80000000LL) n = 0x7fffffffLL;
    res = n;
    return true;
}