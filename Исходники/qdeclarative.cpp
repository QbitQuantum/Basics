void FindTrCalls::processComment(const AST::SourceLocation &loc)
{
    if (!loc.length)
        return;

    const QStringRef commentStr = engine->midRef(loc.begin(), loc.length);
    const QChar *chars = commentStr.constData();
    const int length = commentStr.length();

    // Try to match the logic of the C++ parser.
    if (*chars == QLatin1Char(':') && chars[1].isSpace()) {
        if (!extracomment.isEmpty())
            extracomment += QLatin1Char(' ');
        extracomment += QString(chars+2, length-2);
    } else if (*chars == QLatin1Char('=') && chars[1].isSpace()) {
        msgid = QString(chars+2, length-2).simplified();
    } else if (*chars == QLatin1Char('~') && chars[1].isSpace()) {
        QString text = QString(chars+2, length-2).trimmed();
        int k = text.indexOf(QLatin1Char(' '));
        if (k > -1)
            extra.insert(text.left(k), text.mid(k + 1).trimmed());
    } else if (*chars == QLatin1Char('%') && chars[1].isSpace()) {
        sourcetext.reserve(sourcetext.length() + length-2);
        ushort *ptr = (ushort *)sourcetext.data() + sourcetext.length();
        int p = 2, c;
        forever {
            if (p >= length)
                break;
            c = chars[p++].unicode();
            if (std::isspace(c))
                continue;
            if (c != '"') {
                yyMsg(loc.startLine) << qPrintable(LU::tr("Unexpected character in meta string\n"));
                break;
            }
            forever {
                if (p >= length) {
                  whoops:
                    yyMsg(loc.startLine) << qPrintable(LU::tr("Unterminated meta string\n"));
                    break;
                }
                c = chars[p++].unicode();
                if (c == '"')
                    break;
                if (c == '\\') {
                    if (p >= length)
                        goto whoops;
                    c = chars[p++].unicode();
                    if (c == '\r' || c == '\n')
                        goto whoops;
                    *ptr++ = '\\';
                }
                *ptr++ = c;
            }
        }
        sourcetext.resize(ptr - (ushort *)sourcetext.data());
    } else {