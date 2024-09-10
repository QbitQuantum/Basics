bool HelpPage::acceptNavigationRequest(QWebFrame *,
    const QNetworkRequest &request, QWebPage::NavigationType)
{
    const QUrl &url = request.url();
    if (isLocalUrl(url)) {
        if (url.path().endsWith(QLatin1String("pdf"))) {
            QString fileName = url.toString();
            fileName = QDir::tempPath() + QDir::separator() + fileName.right
                (fileName.length() - fileName.lastIndexOf(QChar('/')));

            QFile tmpFile(QDir::cleanPath(fileName));
            if (tmpFile.open(QIODevice::ReadWrite)) {
                tmpFile.write(helpEngine->fileData(url));
                tmpFile.close();
            }
            QDesktopServices::openUrl(QUrl(tmpFile.fileName()));
            return false;
        }
        return true;
    }

    QDesktopServices::openUrl(url);
    return false;
}