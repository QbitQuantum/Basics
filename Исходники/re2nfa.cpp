NFA RE2NFA::parseSet2()
{
    QSet<InputType> set;
    bool negate = false;

    QString str = symbol().lexem;
    // strip off brackets
    str.chop(1);
    str.remove(0, 1);

    int i = 0;
    while (i < str.length()) {
        // ###
        QChar ch = str.at(i++);
        if (set.isEmpty() && ch == QLatin1Char('^')) {
            negate = true;
            continue;
        }

        // look ahead for ranges like a-z
        bool rangeFound = false;
        if (i < str.length() - 1 && str.at(i) == QLatin1Char('-')) {
            ++i;
            QChar last = str.at(i++);

            if (ch.unicode() > last.unicode())
                qSwap(ch, last);

            for (ushort i = ch.unicode(); i <= last.unicode(); ++i) {
                if (caseSensitivity == Qt::CaseInsensitive) {
                    set.insert(QChar(i).toLower().unicode());
                } else {
                    set.insert(i);
                }
            }

            rangeFound = true;
        }

        if (!rangeFound) {
            if (caseSensitivity == Qt::CaseInsensitive) {
                set.insert(ch.toLower().unicode());
            } else {
                set.insert(ch.unicode());
            }
        }
    }

    if (negate) {
        QSet<InputType> negatedSet = maxInputSet;
        negatedSet.subtract(set);
        set = negatedSet;
    }

    return NFA::createSetNFA(set);
}