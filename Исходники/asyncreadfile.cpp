QString AsyncReadFile::make_latin1_errmsg(int errno_copy, char const *const fmt, ...)  const
{
    static_var const QString inbetw((QStringLiteral(": ")));

    QString s;
    const int maxl = 20;

    if(m_ofn.length() > maxl) {
        s = QStringLiteral("...");
        const int l = s.length();
        s.append(m_ofn.right(maxl - l));
    }
    else {
        s = m_ofn;
    }

    s.append(inbetw);

    if(strchr(fmt, '%') == NULL) {
        s.append(QLatin1String(fmt));
    }
    else {
        QString qfmt;
        va_list ap;
        va_start(ap, fmt);
        qfmt.vsprintf(fmt, ap);
        va_end(ap);
        s.append(qfmt);
    }

    if(errno_copy != 0) {
        QString errstr(warn_xbin_2_local_qstring(strerror(errno_copy)));
        s.append(inbetw);
        s.append(errstr);
    }

    return s;
}