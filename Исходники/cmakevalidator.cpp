static void extractKeywords(const QByteArray &input, QStringList *destination)
{
    if (!destination)
        return;

    QString keyword;
    int ignoreZone = 0;
    for (int i = 0; i < input.count(); ++i) {
        const QChar chr = QLatin1Char(input.at(i));
        if (chr == QLatin1Char('{'))
            ++ignoreZone;
        if (chr == QLatin1Char('}'))
            --ignoreZone;
        if (ignoreZone == 0) {
            if ((chr.isLetterOrNumber() && chr.isUpper())
                || chr == QLatin1Char('_')) {
                keyword += chr;
            } else {
                if (!keyword.isEmpty()) {
                    if (keyword.size() > 1)
                        *destination << keyword;
                    keyword.clear();
                }
            }
        }
    }
    if (keyword.size() > 1)
        *destination << keyword;
}