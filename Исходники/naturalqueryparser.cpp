QStringList NaturalQueryParser::split(const QString &query, bool is_user_query, QList<int> *positions) const
{
    QStringList parts;
    QString part;
    int size = query.size();
    bool between_quotes = false;
    bool split_at_every_char = !localeWordsSeparatedBySpaces();

    for (int i=0; i<size; ++i) {
        QChar c = query.at(i);

        if (!between_quotes && (is_user_query || part != QLatin1String("$")) &&
            (split_at_every_char || c.isSpace() || (is_user_query && d->separators.contains(c)))) {
            // If there is a cluster of several spaces in the input, part may be empty
            if (part.size() > 0) {
                parts.append(part);
                part.clear();
            }

            // Add a separator, if any
            if (!c.isSpace()) {
                if (positions) {
                    positions->append(i);
                }

                part.append(c);
            }
        } else if (c == QLatin1Char('"')) {
            between_quotes = !between_quotes;
        } else {
            if (is_user_query && part.length() == 1 && d->separators.contains(part.at(0))) {
                // The part contains only a separator, split "-KMail" to "-", "KMail"
                parts.append(part);
                part.clear();
            }

            if (positions && part.size() == 0) {
                // Start of a new part, save its position in the stream
                positions->append(i);
            }

            part.append(c);
        }
    }

    if (!part.isEmpty()) {
        parts.append(part);
    }

    return parts;
}