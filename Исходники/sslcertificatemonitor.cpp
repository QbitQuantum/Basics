void SslCertificateMonitor::socketReady(QObject *sockobj)
{
    QSslSocket *sock = qobject_cast<QSslSocket *>(sockobj);
    if (!sock)
        return;

    QString peerName = sock->peerName();
    QSslCertificate certificate = sock->peerCertificate();

    if (*(d->acceptedCache.object(peerName)) == certificate)
        return; // Fast path for most recently accepted certificates

    // Have we been here before?
    QSslCertificate previousCertificate = cachedCertificate(peerName);

    if (!previousCertificate.isNull()) {
        if (certificate == previousCertificate) {
            // We need to add the certificate to the cache here as well as when we add to
            // the on-disk cache so that we don't hit the disk again for this site.
            d->acceptedCache.insert(peerName,new QSslCertificate(certificate));
            return; // All is well
        }

        // Cert has changed
        QString message = evaluateCertificateChange( peerName, previousCertificate,
                                                     certificate, sock->sslErrors().isEmpty() );

        d->acceptCurrent = false;
        emit certificateWarning(sock, message);
    }
    else {
        // The certificate is new. We don't show anything to user because then
        // we're simply training them to click through our warning message without
        // thinking.
        d->acceptCurrent = true;
    }

    // If the user has chosen to accept the certificate or the certficate is new
    // then we store the updated entry.
    if (d->acceptCurrent) {
        d->acceptedCache.insert(peerName,new QSslCertificate(certificate));
        addCertificate(peerName, certificate);
    }
    else {
        // Certficate has been considered dangerous by the user
        sock->abort();
    }
}