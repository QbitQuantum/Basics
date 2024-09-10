/*!
  \brief Set the orientation.
  \param o Orientation. Allowed values are Qt::Horizontal and Qt::Vertical.
  
  If the new orientation and the old scale position are an invalid combination,
  the scale position will be set to QwtSlider::NoScale.
  \sa QwtAbstractSlider::orientation()
*/
void QwtSlider::setOrientation(Qt::Orientation o) 
{
    if ( o == orientation() )
        return;

    if (o == Qt::Horizontal)
    {
        if ((d_data->scalePos == LeftScale) || (d_data->scalePos == RightScale))
            d_data->scalePos = NoScale;
    }
    else // if (o == Qt::Vertical)
    {
        if ((d_data->scalePos == BottomScale) || (d_data->scalePos == TopScale))
            d_data->scalePos = NoScale;
    }

#if QT_VERSION >= 0x040000
    if ( !testAttribute(Qt::WA_WState_OwnSizePolicy) )
#else
    if ( !testWState( WState_OwnSizePolicy ) ) 
#endif
    {
        QSizePolicy sp = sizePolicy();
        sp.transpose();
        setSizePolicy(sp);

#if QT_VERSION >= 0x040000
        setAttribute(Qt::WA_WState_OwnSizePolicy, false);
#else
        clearWState( WState_OwnSizePolicy );
#endif
    }

    QwtAbstractSlider::setOrientation(o);
    layoutSlider();
}