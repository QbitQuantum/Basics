QString timelineWidget::formatTime( time t )
    {
    if( _renderMode == Seconds )
        {
        return QString::number( t.toSeconds(), 'f', 2 ) + "s";
        }
    else
        {
        return QString::number( t.toSeconds(), 'f', 0 );
        }
    }