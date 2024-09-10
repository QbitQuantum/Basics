/*!
    \internal
    Parses \a pattern.
    Allowed is f.ex.:
             qt.core.io.debug      FullText, QtDebugMsg
             qt.core.*             LeftFilter, all types
             *.io.warning          RightFilter, QtWarningMsg
             *.core.*              MidFilter
 */
void QLoggingRule::parse(const QStringRef &pattern)
{
    QStringRef p;

    // strip trailing ".messagetype"
    if (pattern.endsWith(QLatin1String(".debug"))) {
        p = QStringRef(pattern.string(), pattern.position(),
                       pattern.length() - 6); // strlen(".debug")
        messageType = QtDebugMsg;
    } else if (pattern.endsWith(QLatin1String(".info"))) {
        p = QStringRef(pattern.string(), pattern.position(),
                       pattern.length() - 5); // strlen(".info")
        messageType = QtInfoMsg;
    } else if (pattern.endsWith(QLatin1String(".warning"))) {
        p = QStringRef(pattern.string(), pattern.position(),
                       pattern.length() - 8); // strlen(".warning")
        messageType = QtWarningMsg;
    } else if (pattern.endsWith(QLatin1String(".critical"))) {
        p = QStringRef(pattern.string(), pattern.position(),
                       pattern.length() - 9); // strlen(".critical")
        messageType = QtCriticalMsg;
    } else {
        p = pattern;
    }

    if (!p.contains(QLatin1Char('*'))) {
        flags = FullText;
    } else {
        if (p.endsWith(QLatin1Char('*'))) {
            flags |= LeftFilter;
            p = QStringRef(p.string(), p.position(), p.length() - 1);
        }
        if (p.startsWith(QLatin1Char('*'))) {
            flags |= RightFilter;
            p = QStringRef(p.string(), p.position() + 1, p.length() - 1);
        }
        if (p.contains(QLatin1Char('*'))) // '*' only supported at start/end
            flags = 0;
    }

    category = p.toString();
}