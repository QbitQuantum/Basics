bool QSpotifySession::event(QEvent *e)
{
    if (e->type() == NotifyMainThreadEventType) {
        qDebug() << "Process spotify event";
        processSpotifyEvents();
        e->accept();
        return true;
    } else if (e->type() == QEvent::Timer) {
        qDebug() << "Timer, start spotify events";
        QTimerEvent *te = static_cast<QTimerEvent *>(e);
        if (te->timerId() == m_timerID) {
            processSpotifyEvents();
            e->accept();
            return true;
        }
    } else if (e->type() == ConnectionErrorEventType) {
        qDebug() << "Connection error";
        QSpotifyConnectionErrorEvent *ev = static_cast<QSpotifyConnectionErrorEvent *>(e);
        setConnectionError(ConnectionError(ev->error()), QString::fromUtf8(sp_error_message(ev->error())));
        e->accept();
        return true;
    } else if (e->type() == MetaDataEventType) {
        qDebug() << "Meta data";
        emit metadataUpdated();
        e->accept();
        return true;
    } else if (e->type() == EndOfTrackEventType) {
        qDebug() << "End track";
        m_trackChangedAutomatically = true;
        playNext();
        e->accept();
        return true;
    } else if (e->type() == StopEventType) {
        qDebug() << "Stop";
        stop();
        e->accept();
        return true;
    } else if (e->type() == TrackProgressEventType) {
        qDebug() << "Track progress";
        if(!m_isPlaying) {
            e->accept();
            return true;
        }
        // Track progressed
        QSpotifyTrackProgressEvent *ev = static_cast<QSpotifyTrackProgressEvent *>(e);
        int currentTrackPositionDelta = ev->delta();
        if (m_previousTrackRemaining > 0) {
            // We're still playing the previous back from our buffer
            int fromPreviousTrack = qMin(currentTrackPositionDelta, m_previousTrackRemaining);
            currentTrackPositionDelta -= fromPreviousTrack;
            m_previousTrackRemaining -= fromPreviousTrack;
        }

        m_currentTrackPosition += currentTrackPositionDelta;
        m_currentTrackPlayedDuration += currentTrackPositionDelta;
        emit currentTrackPositionChanged();
        e->accept();
        return true;
    } else if (e->type() == SendImageRequestEventType) {
        qDebug() << "Send image request";
        QSpotifyRequestImageEvent *ev = static_cast<QSpotifyRequestImageEvent *>(e);
        sendImageRequest(ev->imageId());
        e->accept();
        return true;
    } else if (e->type() == ReceiveImageRequestEventType) {
        qDebug() << "Receive image request";
        QSpotifyReceiveImageEvent *ev = static_cast<QSpotifyReceiveImageEvent *>(e);
        receiveImageResponse(ev->image());
        e->accept();
        return true;
    } else if (e->type() == PlayTokenLostEventType) {
        qDebug() << "Play token lost";
        emit playTokenLost();
        pause();
        e->accept();
        return true;
    } else if (e->type() == LoggedInEventType) {
        qDebug() << "Logged in 1";
        onLoggedIn();
        e->accept();
        return true;
    } else if (e->type() == LoggedOutEventType) {
        qDebug() << "Logged out";
        onLoggedOut();
        e->accept();
        return true;
    } else if (e->type() == OfflineErrorEventType) {
        qDebug() << "Offline error";
        QSpotifyOfflineErrorEvent *ev = static_cast<QSpotifyOfflineErrorEvent *>(e);
        m_offlineErrorMessage = QString::fromUtf8(sp_error_message(ev->error()));
        emit offlineErrorMessageChanged();
        e->accept();
        return true;
    } else if (e->type() == ScrobbleLoginErrorEventType) {
        qDebug() << "Scrobble login error";
        m_lfmLoggedIn = false;
        emit lfmLoggedInChanged();
        emit lfmLoginError();
        e->accept();
        return true;
    } else if (e->type() == ConnectionStateUpdateEventType) {
        qDebug() << "Connectionstate update event";
        setConnectionStatus(ConnectionStatus(sp_session_connectionstate(m_sp_session)));
        if (m_offlineMode && m_connectionStatus == LoggedIn) {
            setConnectionRules(m_connectionRules | AllowNetwork);
            setConnectionRules(m_connectionRules & ~AllowNetwork);
        }
        e->accept();
        return true;
    }
    return QObject::event(e);
}