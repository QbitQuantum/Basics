/**
 * Split a line into lexemes.
 */
QStringList scan(const QString& lin)
{
    QStringList result;
    QString line = lin.trimmed();
    if (line.isEmpty())
        return result;  // empty
    QString lexeme;
    const uint len = line.length();
    bool inString = false;
    for (uint i = 0; i < len; ++i) {
        QChar c = line[i];
        if (c == QLatin1Char('"')) {
            lexeme += c;
            if (inString) {
                result.append(lexeme);
                lexeme.clear();
            }
            inString = !inString;
        } else if (inString ||
                   c.isLetterOrNumber() || c == QLatin1Char('_') || c == QLatin1Char('@')) {
            lexeme += c;
        } else {
            if (!lexeme.isEmpty()) {
                result.append(lexeme);
                lexeme.clear();
            }
            if (! c.isSpace()) {
                result.append(QString(c));
            }
        }
    }
    if (!lexeme.isEmpty())
        result.append(lexeme);
    return result;
}