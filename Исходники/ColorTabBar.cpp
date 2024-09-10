void QColorTabBar::timerEvent(QTimerEvent *evt)
{
    if( evt->timerId() == m_nTimerBlink )
    {
        m_bBlinkFalg = !m_bBlinkFalg;

        if( m_nBlinkIndex < 0)
        {
            killTimer( m_nTimerBlink );
            m_nTimerBlink = 0;
            m_bBlinkFalg = false;
        }

        QRect rcTab( tabRect( m_nBlinkIndex ) );
        update( rcTab );
    }

    QTabBar::timerEvent(evt);
}