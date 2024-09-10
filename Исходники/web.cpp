Web::Translation Web::translate(const QString &dict, const QString &word)
{
    if (! m_loadedDicts.contains(dict))
        return Translation();
    QUrl url(m_loadedDicts[dict].query.replace("%s", word));
    QEventLoop loop;
    QHttp http(url.host(), url.port(80), &loop);
    connect(&http, SIGNAL(done(bool)), &loop, SLOT(quit()));
    http.get(url.path() + "?" + url.encodedQuery());
    loop.exec();
    QTextCodec *codec = QTextCodec::codecForName(m_loadedDicts[dict].codec);
    QString translation;
    if (codec)
        translation = codec->toUnicode(http.readAll());
    else
        translation = QString::fromUtf8(http.readAll());
    return Translation(dict, word, translation);
}