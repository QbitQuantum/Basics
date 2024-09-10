/*!
  Draw the border of the canvas
  \param painter Painter
*/
void QwtPlotGLCanvas::drawBorder( QPainter *painter )
{
    const int fw = frameWidth();
    if ( fw <= 0 )
        return;

    if ( frameShadow() == QwtPlotGLCanvas::Plain )
    {
        qDrawPlainRect( painter, frameRect(), 
            palette().shadow().color(), lineWidth() );
    }
    else
    {
        if ( frameShape() == QwtPlotGLCanvas::Box )
        {
            qDrawShadeRect( painter, frameRect(), palette(),
                frameShadow() == Sunken, lineWidth(), midLineWidth() );
        }
        else
        {
            qDrawShadePanel( painter, frameRect(), palette(), 
                frameShadow() == Sunken, lineWidth() );
        }
    }
}