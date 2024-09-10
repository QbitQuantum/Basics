bool
AlbumsFilterBar::eventFilter( QObject *obj, QEvent *e )
{
    if( obj == m_editor )
    {
        if( e->type() == QEvent::KeyPress )
        {
            QKeyEvent *kev = static_cast<QKeyEvent*>( e );
            if( kev->key() == Qt::Key_Escape )
            {
                kev->accept();
                emit closeRequested();
                return true;
            }
        }
    }
    return QGraphicsWidget::eventFilter( obj, e );
}