bool QAccel::eventFilter( QObject *o, QEvent *e )
{
    if ( e->type() == QEvent::Reparent && d->watch == o ) {
        repairEventFilter();
    } else  if ( d->enabled &&
                 ( e->type() == QEvent::Accel ||
                   e->type() == QEvent::AccelAvailable) &&
                 d->watch && d->watch->isVisible() ) {
        QKeyEvent *k = (QKeyEvent *)e;
        int key = k->key();
        if ( k->state() & ShiftButton )
            key |= SHIFT;
        if ( k->state() & ControlButton )
            key |= CTRL;
        if ( k->state() & AltButton )
            key |= ALT;
        QAccelItem *item = find_key( d->aitems, key, k->text()[0] );
        if ( key == Key_unknown )
            item = 0;
#ifndef QT_NO_WHATSTHIS
        bool b = QWhatsThis::inWhatsThisMode();
#else
        bool b = FALSE;
#endif
        if ( item && ( item->enabled || b )) {
            if (e->type() == QEvent::Accel) {
                if ( b && !d->ignorewhatsthis ) {
#ifndef QT_NO_WHATSTHIS
                    QWhatsThis::leaveWhatsThisMode( item->whatsthis );
#endif
                }
                else if ( item->enabled ) {
                    if ( item->signal )
                        item->signal->activate();
                    else
                        emit activated( item->id );
                }
            }
            k->accept();
            return TRUE;
        }
    }
    return QObject::eventFilter( o, e );
}