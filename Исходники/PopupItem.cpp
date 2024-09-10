bool PopupItem::eventFilter( QObject *object, QEvent *e )
{
    MarbleWidget *widget = dynamic_cast<MarbleWidget*> ( object );
    if ( !widget ) {
        return BillboardGraphicsItem::eventFilter( object, e );
    }

    if ( e->type() == QEvent::MouseButtonDblClick
            || e->type() == QEvent::MouseMove
            || e->type() == QEvent::MouseButtonPress
            || e->type() == QEvent::MouseButtonRelease )
    {
        // Mouse events are forwarded to the underlying widget
        QMouseEvent *event = static_cast<QMouseEvent*> ( e );
        QPoint const shiftedPos = transform( event->pos() );
        bool const forcedMouseRelease = m_needMouseRelease && e->type() == QEvent::MouseButtonRelease;
        if ( !shiftedPos.isNull() || forcedMouseRelease ) {
            if ( !m_needMouseRelease && e->type() == QEvent::MouseButtonPress ) {
                m_needMouseRelease = true;
            } else if ( forcedMouseRelease ) {
                m_needMouseRelease = false;
            }
            widget->setCursor( Qt::ArrowCursor );
            // transform to children's coordinates
            QMouseEvent shiftedEvent = QMouseEvent( e->type(), shiftedPos,
                                                    event->globalPos(), event->button(), event->buttons(),
                                                    event->modifiers() );
            if ( QApplication::sendEvent( m_webView, &shiftedEvent ) ) {
                widget->setCursor( m_webView->cursor() );
                emit dirty();
                return true;
            }
        }
    } else if ( e->type() == QEvent::Wheel ) {
        // Wheel events are forwarded to the underlying widget
        QWheelEvent *event = static_cast<QWheelEvent*> ( e );
        QPoint const shiftedPos = transform( event->pos() );
        if ( !shiftedPos.isNull() ) {
            widget->setCursor( Qt::ArrowCursor );
            QWheelEvent shiftedEvent = QWheelEvent( shiftedPos,
                                                    event->globalPos(), event->delta(), event->buttons(),
                                                    event->modifiers() );
            if ( QApplication::sendEvent( m_webView, &shiftedEvent ) ) {
                widget->setCursor( m_webView->cursor() );
                emit dirty();
                return true;
            }
        }
    }

    return BillboardGraphicsItem::eventFilter( object, e );
}