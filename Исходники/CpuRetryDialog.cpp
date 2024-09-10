//Implemented from QObject
void CpuRetryDialog::timerEvent(QTimerEvent* event)
{
    (void)(event); // unused
    --m_seconds;

    if (nullptr != m_pText)
    {
        QString text;
        text.sprintf(FORMATSTRING, m_seconds);
        m_pText->setText(text);
    }

    if (0 == m_seconds)
    {
        killTimer(m_timerId);
        m_timerId = 0;
        accept();
    }
}