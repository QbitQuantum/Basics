/*!
  \brief Set the wheel's orientation.

  The default orientation is Qt::Horizontal.

  \param orientation Qt::Horizontal or Qt::Vertical.
  \sa orientation()
*/
void QwtWheel::setOrientation( Qt::Orientation orientation )
{
    if ( d_data->orientation == orientation )
        return;

    if ( !testAttribute( Qt::WA_WState_OwnSizePolicy ) )
    {
        QSizePolicy sp = sizePolicy();
        sp.transpose();
        setSizePolicy( sp );

        setAttribute( Qt::WA_WState_OwnSizePolicy, false );
    }

    d_data->orientation = orientation;
    update();
}