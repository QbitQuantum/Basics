QGeoTileSpec QGeoTileCache::filenameToTileSpec(const QString &filename)
{
    QGeoTileSpec emptySpec;

    QStringList parts = filename.split('.');

    if (parts.length() != 2)
        return emptySpec;

    QString name = parts.at(0);
    QStringList fields = name.split('-');

    int length = fields.length();
    if (length != 5 && length != 6)
        return emptySpec;

    QList<int> numbers;

    bool ok = false;
    for (int i = 1; i < length; ++i) {
        ok = false;
        int value = fields.at(i).toInt(&ok);
        if (!ok)
            return emptySpec;
        numbers.append(value);
    }

    //File name without version, append default
    if (numbers.length() < 5)
        numbers.append(-1);

    return QGeoTileSpec(fields.at(0),
                    numbers.at(0),
                    numbers.at(1),
                    numbers.at(2),
                    numbers.at(3),
                    numbers.at(4));
}