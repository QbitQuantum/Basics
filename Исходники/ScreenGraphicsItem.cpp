bool ScreenGraphicsItem::eventFilter( QObject *object, QEvent *e )
{
    MarbleWidget *widget = dynamic_cast<MarbleWidget*>(object);
    if ( !widget ) {
        return MarbleGraphicsItem::eventFilter( object, e );
    }
    
    if ( !p()->m_floatItemMoving ) {
        if ( MarbleGraphicsItem::eventFilter( object, e ) ) {
            return true;
        }
    
        if ( !visible() || !p()->isMovable() ) {
            return false;
        }
        
        if ( e->type() == QEvent::MouseMove ) {
            return false;
        }
        
        // Move ScreenGraphicsItem
        if ( e->type() == QEvent::MouseButtonPress )
        {
            QMouseEvent *event = static_cast<QMouseEvent*>(e);

            // Click and move above a float item triggers moving the float item
            if ( contains( event->pos() ) ) {
                if ( event->button() == Qt::LeftButton ) {
                    p()->m_floatItemMoveStartPos = event->pos();
                    p()->m_floatItemMoving = true;
                    return true;
                }
            }
        }
        
        return false;
    }
    else {
        // Move ScreenGraphicsItem
        bool cursorAboveFloatItem = false;
        if ( e->type() == QEvent::MouseMove
            || e->type() == QEvent::MouseButtonPress
            || e->type() == QEvent::MouseButtonRelease )
        {
            QMouseEvent *event = static_cast<QMouseEvent*>( e );
            // The rect the item was painted on before. We add one pixel as antialiasing could
            // result into painting on these pixels to.
            QRectF floatItemRect = QRectF( positivePosition() - QPoint( 1, 1 ),
                                           size() + QSize( 2, 2 ) );

            // Click and move above a float item triggers moving the float item
            if ( contains( event->pos() ) ) {
                cursorAboveFloatItem = true;

                if ( e->type() == QEvent::MouseButtonPress && event->button() == Qt::LeftButton ) {
                    p()->m_floatItemMoveStartPos = event->pos();
                    return true;
                }
            }

            if ( e->type() == QEvent::MouseMove && event->buttons() & Qt::LeftButton && p()->isMovable() )
            {
                p()->m_floatItemMoving = true;
                const QPoint &point = event->pos();
                QPointF position = positivePosition();
                qreal newX = position.x()+point.x()-p()->m_floatItemMoveStartPos.x();
                qreal newY = position.y()+point.y()-p()->m_floatItemMoveStartPos.y();
                if ( newX >= 0 && newY >= 0 ) {
                    // docking behavior
                    const qreal dockArea = 60.0; // Alignment area width/height
                    const qreal dockJump = 30.0; // Alignment indicator jump size
                    if ( widget->width()-size().width()-newX < dockArea ) {
                        newX = qMin( qreal( -1.0 ), size().width() + newX-widget->width() );
                        if ( p()->m_floatItemMoveStartPos.x() < event->pos().x() ) {
                            // Indicate change to right alignment with a short jump
                            newX = qMax( newX, -(dockArea-dockJump) );
                        }
                    }
                    if ( widget->height()-size().height()-newY < dockArea ) {
                        newY = qMin( qreal( -1.0 ), size().height() + newY-widget->height() );
                        if (p()->m_floatItemMoveStartPos.y()<event->pos().y()) {
                        // Indicate change to bottom alignment with a short jump
                        newY = qMax( newY, -( dockArea - dockJump ) );
                        }
                    }

                    setPosition( QPointF( newX,newY ) );
                    // The rect the item will be painted on now. We add one pixel as
                    // antialiasing could result into painting on these pixels to.
                    QRect newFloatItemRect = QRectF( positivePosition() - QPoint( 1, 1 ),
                                                     size() + QSize( 2, 2 ) ).toRect();
                    p()->m_floatItemMoveStartPos = event->pos();
                    QRegion dirtyRegion( floatItemRect.toRect() );
                    dirtyRegion = dirtyRegion.united( newFloatItemRect );

                    widget->setAttribute( Qt::WA_NoSystemBackground,  false );
                    widget->update(dirtyRegion);
                    widget->setAttribute( Qt::WA_NoSystemBackground, widget->viewport()->mapCoversViewport() );
                    return true;
                }
            }

            if ( e->type() == QEvent::MouseButtonRelease ) {
                p()->m_floatItemMoving = false;
            }

            // Adjusting Cursor shape
            if ( cursorAboveFloatItem || p()->m_floatItemMoving ) {
                widget->setCursor(QCursor(Qt::SizeAllCursor));
                return true;
            }
        }
        
        return MarbleGraphicsItem::eventFilter( object, e );
    }
}