bool InputEventRecorder::eventFilter(QObject *obj, QEvent *ev)
{
    if (m_InReplay || !m_ReplayFilter.isEmpty())
    {
        if (!m_ReplayFilter.remove(ev) && isRecordable(ev))
            return true; /* filtering external events during replays */
        else if (m_ReplayFilter.isEmpty() && !m_InReplay)
            qApp->removeEventFilter(this);
        return false;
    }

    if ((obj != m_Obj) && !isChild(obj, m_Obj))
        return false;

    /* stop recording when we detect ctrl-c */
    if (ev && ev->type() == QEvent::KeyPress)
    {
        QKeyEvent *kev = static_cast<QKeyEvent *>(ev);
        if ((kev->modifiers() == Qt::ControlModifier) &&
                (kev->key() == Qt::Key_C))
        {
            stop();
            return false;
        }
    }

    QEvent *clonedEv = cloneEvent(ev);

    if (clonedEv)
    {
        int timeOffset;
        QDateTime curDt(QDateTime::currentDateTime());
        timeOffset = m_RecordingStartTime.daysTo(curDt) * 24 * 3600 * 1000 + m_RecordingStartTime.time().msecsTo(curDt.time());
        m_Recording.push_back(EventDelivery(timeOffset, obj, clonedEv));
    }

    return false;
}