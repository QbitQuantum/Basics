void LastFmContext::readContextReply() {
    qDebug("Got reply!");
    QString replyString = QString::fromUtf8(contextReply->readAll());

    if (replyString.isEmpty()) {
        emit contextError();
        return; // Avoid empty parsing of XML
    }

    // Parametres
    QString status;
    QString artistName;
    QString artistPicture;
    QString artistSummary;
    QString artistProfile;

    QXmlQuery query;
    query.setFocus(replyString);
    query.setQuery("lfm[@status = 'ok']/count(artist)");
    query.evaluateTo(&status);
    status = status.trimmed();
    qDebug("Status: " + status.toUtf8());

    /*
     * If we got the data successfully, let's read it.
     * I hate XML.
     */
    if (status == "1") {
        query.setQuery("lfm/artist/name/text()");
        query.evaluateTo(&artistName);
        artistName = artistName.trimmed();

        query.setQuery("lfm/artist/url/text()");
        query.evaluateTo(&artistProfile);
        artistProfile = artistProfile.trimmed();

        query.setQuery("lfm/artist/image[@size=\"extralarge\"]/text()");
        query.evaluateTo(&artistPicture);
        artistPicture = artistPicture.trimmed();

        // Summary has HTML entities that must be un-replaced.
        query.setQuery("lfm/artist/bio/summary/text()");
        query.evaluateTo(&artistSummary);
        artistSummary = artistSummary.trimmed().replace("&lt;","<").replace("&gt;",">");

        // Store the context data into... contextData. Nice!
        contextData.clear();
        contextData.insert("artist", artistName);
        contextData.insert("picture", artistPicture);
        contextData.insert("summary", artistSummary);
        contextData.insert("profile", artistProfile);

        // Emit the signal
        emit contextUpdated(contextData);
    }
    else {
        qDebug("FAIL!");
        emit contextError();
    }
}