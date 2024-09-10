/*!
  Draw lines from the pole

  \param painter Painter
  \param canvasRect Contents rect of the canvas in painter coordinates
  \param pole Position of the pole in painter coordinates
  \param radius Length of the lines in painter coordinates
  \param azimuthMap Maps azimuth values to values related to 0.0, M_2PI
  \param values Azimuth values, indicating the direction of the lines
*/
void QwtPolarGrid::drawRays(
    QPainter *painter, const QRectF &canvasRect,
    const QPointF &pole, double radius,
    const QwtScaleMap &azimuthMap, const QList<double> &values ) const
{
    for ( int i = 0; i < int( values.size() ); i++ )
    {
        double azimuth = azimuthMap.transform( values[i] );
        azimuth = ::fmod( azimuth, 2 * M_PI );

        bool skipLine = false;
        if ( testDisplayFlag( SmartScaleDraw ) )
        {
            const QwtAbstractScaleDraw::ScaleComponent bone =
                QwtAbstractScaleDraw::Backbone;
            if ( isClose( azimuth, 0.0 ) )
            {
                const AxisData &axis = d_data->axisData[QwtPolar::AxisRight];
                if ( axis.isVisible && axis.scaleDraw->hasComponent( bone ) )
                    skipLine = true;
            }
            else if ( isClose( azimuth, M_PI / 2 ) )
            {
                const AxisData &axis = d_data->axisData[QwtPolar::AxisTop];
                if ( axis.isVisible && axis.scaleDraw->hasComponent( bone ) )
                    skipLine = true;
            }
            else if ( isClose( azimuth, M_PI ) )
            {
                const AxisData &axis = d_data->axisData[QwtPolar::AxisLeft];
                if ( axis.isVisible && axis.scaleDraw->hasComponent( bone ) )
                    skipLine = true;
            }
            else if ( isClose( azimuth, 3 * M_PI / 2.0 ) )
            {
                const AxisData &axis = d_data->axisData[QwtPolar::AxisBottom];
                if ( axis.isVisible && axis.scaleDraw->hasComponent( bone ) )
                    skipLine = true;
            }
        }
        if ( !skipLine )
        {
            const QPointF pos = qwtPolar2Pos( pole, radius, azimuth );

            /*
                Qt4 is horrible slow, when painting primitives,
                with coordinates far outside the visible area.
             */

            QPolygonF polygon( 2 );
            polygon[0] = pole.toPoint();
            polygon[1] = pos.toPoint();

            if ( testDisplayFlag( ClipGridLines ) )
                polygon = QwtClipper::clipPolygonF( canvasRect, polygon );

            QwtPainter::drawPolyline( painter, polygon );
        }
    }
}