void RemoteDatabase::updateProgress(qint64 bytesTransmitted, qint64 bytesTotal)
{
    // Find out to which pending reply this progress update belongs
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(QObject::sender());

    // Update progress dialog
    if(bytesTotal == -1)
    {
        // We don't know anything about the current progress, but it's still downloading
        m_progress->setMinimum(0);
        m_progress->setMaximum(0);
        m_progress->setValue(0);
    } else if(bytesTransmitted == bytesTotal) {
        // The download has finished
        m_progress->reset();
    } else {
        // It's still downloading and we know the current progress

        // Were using a range 0 to 10000 here, the progress dialog will calculate 0% to 100% values from that. The reason we're not using
        // the byte counts as-is is that they're 64bit wide while the progress dialog takes only 32bit values, so for large files the values
        // would lose precision. The reason why we're not using a range 0 to 100 is that our range increases the precision a bit and this way
        // we're prepared if the progress dialog will show decimal numbers one day on one platform.
        m_progress->setMinimum(0);
        m_progress->setMaximum(10000);
        m_progress->setValue(static_cast<int>((static_cast<float>(bytesTransmitted) / static_cast<float>(bytesTotal)) * 10000.0f));
    }

    // Check if the Cancel button has been pressed
    if(reply && m_progress->wasCanceled())
    {
        reply->abort();
        m_progress->reset();
    }
}