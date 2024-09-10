void CloudControl::uploadCancelled() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *> (sender());
    if (reply != NULL) {
        reply->abort();
    }
    uploadProgress->close();
    uploadProgress->deleteLater();
}