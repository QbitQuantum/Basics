void LyricWikiPlugin::onSongReplyReceived()
{
    QByteArray data = reply->readAll();
    reply->deleteLater();

    // <div class='lyricbox'>(...)<script>(...)</script>(lyrics)<!--
    int i = data.indexOf("<div class='lyricbox'>");
    if (i != -1) {
        i += 22;
        data.remove(data.indexOf("<!--", i), data.length());

        if (data.indexOf("Category:Instrumental", i) != -1) {
            emit error("According to LyricWiki this track is instrumental.");
            return;
        }

        QTextDocument lyrics; lyrics.setHtml(data.mid(data.indexOf("</script>", i) + 9));
        QString plainLyrics = lyrics.toPlainText();

        if (plainLyrics.contains("we are not licensed to display the full lyrics for this song")) {
            emit error("The lyrics for this song are incomplete on LyricWiki.");
        } else {
            emit fetched(plainLyrics);
        }
    } else {
        emit error("The lyrics for this song are missing on LyricWiki.");
    }
}