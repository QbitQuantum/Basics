void WritePasswordJobPrivate::kwalletOpenFinished( QDBusPendingCallWatcher* watcher ) {
    watcher->deleteLater();
    QDBusPendingReply<int> reply = *watcher;

    std::auto_ptr<QSettings> local( !q->settings() ? new QSettings(  q->service() ) : 0 );
    QSettings* actual = q->settings() ? q->settings() : local.get();

    if ( reply.isError() ) {
        if ( q->insecureFallback() ) {
            if ( mode == Delete ) {
                actual->remove( key );
                actual->sync();

                q->emitFinished();
                return;
            }

            actual->setValue( QString( "%1/type" ).arg( key ), (int)mode );
            if ( mode == Text )
                actual->setValue( QString( "%1/data" ).arg( key ), textData.toUtf8() );
            else if ( mode == Binary )
                actual->setValue( QString( "%1/data" ).arg( key ), binaryData );
            actual->sync();

            q->emitFinished();
        } else {
            const QDBusError err = reply.error();
            q->emitFinishedWithError( OtherError, tr("Could not open wallet: %1; %2").arg( QDBusError::errorString( err.type() ), err.message() ) );
        }
        return;
    }

    if ( actual->contains( key ) )
    {
        // If we had previously written to QSettings, but we now have a kwallet available, migrate and delete old insecure data
        actual->remove( key );
        actual->sync();
    }

    const int handle = reply.value();

    if ( handle < 0 ) {
        q->emitFinishedWithError( AccessDenied, tr("Access to keychain denied") );
        return;
    }

    QDBusPendingReply<int> nextReply;

    if ( !textData.isEmpty() )
        nextReply = iface->writePassword( handle, q->service(), key, textData, q->service() );
    else if ( !binaryData.isEmpty() )
        nextReply = iface->writeEntry( handle, q->service(), key, binaryData, q->service() );
    else
        nextReply = iface->removeEntry( handle, q->service(), key, q->service() );

    QDBusPendingCallWatcher* nextWatcher = new QDBusPendingCallWatcher( nextReply, this );
    connect( nextWatcher, SIGNAL(finished(QDBusPendingCallWatcher*)), this, SLOT(kwalletWriteFinished(QDBusPendingCallWatcher*)) );
}