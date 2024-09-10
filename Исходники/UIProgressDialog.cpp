int UIProgressDialog::run(int cRefreshInterval)
{
    if (m_progress.isOk())
    {
        /* Start refresh timer */
        int id = startTimer(cRefreshInterval);

        /* Set busy cursor.
         * We don't do this on the Mac, cause regarding the design rules of
         * Apple there is no busy window behavior. A window should always be
         * responsive and it is in our case (We show the progress dialog bar). */
#ifndef Q_WS_MAC
        if (m_fCancelEnabled)
            QApplication::setOverrideCursor(QCursor(Qt::BusyCursor));
        else
            QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif /* Q_WS_MAC */

        /* Create a local event-loop: */
        {
            /* Guard ourself for the case
             * we destroyed ourself in our event-loop: */
            QPointer<UIProgressDialog> guard = this;

            /* Holds the modal loop, but don't show the window immediately: */
            exec(false);

            /* Are we still valid? */
            if (guard.isNull())
                return Rejected;
        }

        /* Kill refresh timer */
        killTimer(id);

#ifndef Q_WS_MAC
        /* Reset the busy cursor */
        QApplication::restoreOverrideCursor();
#endif /* Q_WS_MAC */

        return result();
    }
    return Rejected;
}