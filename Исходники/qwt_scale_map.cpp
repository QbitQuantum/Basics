/*!
   Transform a point from scale to paint coordinates

   \param xMap X map
   \param yMap Y map
   \param pos Position in scale coordinates
   \return Position in paint coordinates

   \sa invTransform()
*/
QPointF QwtScaleMap::transform( const QwtScaleMap &xMap,
    const QwtScaleMap &yMap, const QPointF &pos )
{
    return QPointF( 
        xMap.transform( pos.x() ), 
        yMap.transform( pos.y() )
    );
}