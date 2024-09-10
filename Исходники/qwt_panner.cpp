void QwtPanner::showCursor( bool on )
{
    if ( on == d_data->hasCursor )
        return;

    QWidget *w = parentWidget();
    if ( w == NULL || d_data->cursor == NULL )
        return;

    d_data->hasCursor = on;

    if ( on )
    {
        if ( w->testAttribute( Qt::WA_SetCursor ) )
        {
            delete d_data->restoreCursor;
            d_data->restoreCursor = new QCursor( w->cursor() );
        }
        w->setCursor( *d_data->cursor );
    }
    else
    {
        if ( d_data->restoreCursor )
        {
            w->setCursor( *d_data->restoreCursor );
            delete d_data->restoreCursor;
            d_data->restoreCursor = NULL;
        }
        else
            w->unsetCursor();
    }
}