QNetworkReply *AccelTreeResourceLoader::load(const QUrl &uri,
                                             QNetworkAccessManager *const networkManager,
                                             const ReportContext::Ptr &context, ErrorHandling errorHandling)

{
    Q_ASSERT(networkManager);
    Q_ASSERT(uri.isValid());

    const bool ftpSchemeUsed = (uri.scheme() == QStringLiteral("ftp"));
    // QNAM doesn't have support for SynchronousRequestAttribute in its ftp backend.
    QEventLoop ftpNetworkLoop;
    QNetworkRequest request(uri);
    if (!ftpSchemeUsed)
        request.setAttribute(QNetworkRequest::SynchronousRequestAttribute, true);
    QNetworkReply *const reply = networkManager->get(request);
    if (ftpSchemeUsed) {
        ftpNetworkLoop.connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(quit()));
        ftpNetworkLoop.connect(reply, SIGNAL(finished()), SLOT(quit()));
        ftpNetworkLoop.exec(QEventLoop::ExcludeUserInputEvents);
    }

    if (reply->error() != QNetworkReply::NoError) {
        const QString errorMessage(escape(reply->errorString()));

        /* Note, we delete reply before we exit this function with error(). */
        delete reply;

        const QSourceLocation location(uri);

        if(context && (errorHandling == FailOnError))
            context->error(errorMessage, ReportContext::FODC0002, location);

        return 0;
    } else
        return reply;
}