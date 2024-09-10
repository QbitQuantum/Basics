bool ElevationProfileFloatItem::eventFilter( QObject *object, QEvent *e )
{
    if ( !enabled() || !visible() ) {
        return false;
    }

    MarbleWidget *widget = dynamic_cast<MarbleWidget*>( object );
    if ( !widget ) {
        return AbstractFloatItem::eventFilter(object,e);
    }

    if ( widget && !m_marbleWidget ) {
        m_marbleWidget = widget;
        connect( this, SIGNAL(dataUpdated()), this, SLOT(updateVisiblePoints()) );
        connect( m_marbleWidget, SIGNAL(visibleLatLonAltBoxChanged(GeoDataLatLonAltBox)),
                 this, SLOT(updateVisiblePoints()) );
        connect( this, SIGNAL(settingsChanged(QString)), this, SLOT(updateVisiblePoints()) );
    }

    if ( e->type() == QEvent::MouseButtonDblClick || e->type() == QEvent::MouseMove ) {
        GeoDataTreeModel *const treeModel = const_cast<MarbleModel *>( marbleModel() )->treeModel();

        QMouseEvent *event = static_cast<QMouseEvent*>( e  );
        QRectF plotRect = QRectF ( m_leftGraphMargin, 0, m_eleGraphWidth, contentSize().height() );
        plotRect.translate( positivePosition() );
        plotRect.translate( padding(), padding() );

        // for antialiasing: increase size by 1 px to each side
        plotRect.translate(-1, -1);
        plotRect.setSize(plotRect.size() + QSize(2, 2) );

        const bool cursorAboveFloatItem = plotRect.contains(event->pos());

        if ( cursorAboveFloatItem ) {
            const int start = m_zoomToViewport ? m_firstVisiblePoint : 0;
            const int end = m_zoomToViewport ? m_lastVisiblePoint : m_eleData.size();

            // Double click triggers recentering the map at the specified position
            if ( e->type() == QEvent::MouseButtonDblClick ) {
                const QPointF mousePosition = event->pos() - plotRect.topLeft();
                const int xPos = mousePosition.x();
                for ( int i = start; i < end; ++i) {
                    const int plotPos = ( m_eleData.value(i).x() - m_axisX.minValue() ) * m_eleGraphWidth / m_axisX.range();
                    if ( plotPos >= xPos ) {
                        widget->centerOn( m_points[i], true );
                        break;
                    }
                }
                return true;
            }

            if ( e->type() == QEvent::MouseMove && !(event->buttons() & Qt::LeftButton) ) {
                // Cross hair cursor when moving above the float item
                // and mark the position on the graph
                widget->setCursor(QCursor(Qt::CrossCursor));
                if ( m_cursorPositionX != event->pos().x() - plotRect.left() ) {
                    m_cursorPositionX = event->pos().x() - plotRect.left();
                    const qreal xpos = m_axisX.minValue() + ( m_cursorPositionX / m_eleGraphWidth ) * m_axisX.range();
                    GeoDataCoordinates currentPoint; // invalid coordinates
                    for ( int i = start; i < end; ++i) {
                        if ( m_eleData.value(i).x() >= xpos ) {
                            currentPoint = m_points[i];
                            currentPoint.setAltitude( m_eleData.value(i).y() );
                            break;
                        }
                    }
                    m_markerPlacemark->setCoordinate( currentPoint );
                    if ( m_documentIndex < 0 ) {
                        m_documentIndex = treeModel->addDocument( &m_markerDocument );
                    }
                    emit repaintNeeded();
                }

                return true;
            }
        }
        else {
            if ( m_documentIndex >= 0 ) {
                m_markerPlacemark->setCoordinate( GeoDataCoordinates() ); // set to invalid
                treeModel->removeDocument( &m_markerDocument );
                m_documentIndex = -1;
                emit repaintNeeded();
            }
        }
    }

    return AbstractFloatItem::eventFilter(object,e);
}