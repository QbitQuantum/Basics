bool XLIFFHandler::characters(const QString &ch)
{
    if (currentContext() == XC_ph) {
        // handle the content of <ph> elements
        for (int i = 0; i < ch.count(); ++i) {
            QChar chr = ch.at(i);
            if (accum.endsWith(QLatin1Char('\\')))
                accum[accum.size() - 1] = QLatin1Char(charFromEscape(chr.toAscii()));
            else
                accum.append(chr);
        }
    } else {
        QString t = ch;
        t.replace(QLatin1String("\r"), QLatin1String(""));
        accum.append(t);
    }
    return true;
}