static QString comify(const QString &organization)
{
    for (int i = organization.size() - 1; i >= 0; --i) {
        QChar ch = organization.at(i);
        if (ch == QLatin1Char('.') || ch == QChar(0x3002) || ch == QChar(0xff0e)
                || ch == QChar(0xff61)) {
            QString suffix = organization.mid(i + 1).toLower();
            if (suffix.size() == 2 || suffix == QLatin1String("com")
                    || suffix == QLatin1String("org") || suffix == QLatin1String("net")
                    || suffix == QLatin1String("edu") || suffix == QLatin1String("gov")
                    || suffix == QLatin1String("mil") || suffix == QLatin1String("biz")
                    || suffix == QLatin1String("info") || suffix == QLatin1String("name")
                    || suffix == QLatin1String("pro") || suffix == QLatin1String("aero")
                    || suffix == QLatin1String("coop") || suffix == QLatin1String("museum")) {
                QString result = organization;
                result.replace(QLatin1Char('/'), QLatin1Char(' '));
                return result;
            }
            break;
        }
        int uc = ch.unicode();
        if ((uc < 'a' || uc > 'z') && (uc < 'A' || uc > 'Z'))
            break;
    }

    QString domain;
    for (int i = 0; i < organization.size(); ++i) {
        QChar ch = organization.at(i);
        int uc = ch.unicode();
        if ((uc >= 'a' && uc <= 'z') || (uc >= '0' && uc <= '9')) {
            domain += ch;
        } else if (uc >= 'A' && uc <= 'Z') {
            domain += ch.toLower();
        } else {
            domain += QLatin1Char(' ');
        }
    }
    domain = domain.simplified();
    domain.replace(QLatin1Char(' '), QLatin1Char('-'));
    if (!domain.isEmpty())
        domain.append(QLatin1String(".com"));
    return domain;
}