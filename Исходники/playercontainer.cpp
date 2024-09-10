static bool decodeUri(QVariantMap &map, const QString& entry) {
    if (map.contains(entry)) {
        QString urlString = map.value(entry).toString();
        QUrl url = QUrl::fromEncoded(urlString.toAscii());
        if (!url.isValid()) {
            // try to be lenient
            url = QUrl(urlString);
        }
        if (url.isValid()) {
            map.insert(entry, QVariant(url));
            return true;
        } else {
            map.remove(entry);
            return false;
        }
    }
    // count it as a success if it doesn't exist
    return true;
}