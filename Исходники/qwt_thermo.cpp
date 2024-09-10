/*!
  \brief Set the orientation.
  \param orientation Allowed values are Qt::Horizontal and Qt::Vertical.

  \sa orientation(), scalePosition()
*/
void QwtThermo::setOrientation( Qt::Orientation orientation )
{
    if ( orientation == d_data->orientation )
        return;

    d_data->orientation = orientation;

    if ( !testAttribute( Qt::WA_WState_OwnSizePolicy ) )
    {
        QSizePolicy sp = sizePolicy();
        sp.transpose();
        setSizePolicy( sp );

        setAttribute( Qt::WA_WState_OwnSizePolicy, false );
    }

    layoutThermo( true );
}