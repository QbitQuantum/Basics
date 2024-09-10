/*!
  \brief Render the plot to a QSvgGenerator

  If the generator has a view box, the plot will be rendered into it.
  If it has no viewBox but a valid size the target coordinates
  will be (0, 0, generator.width(), generator.height()). Otherwise
  the target rectangle will be QRectF(0, 0, 800, 600);

  \param plot Plot to be rendered
  \param generator SVG generator
*/
void QwtPolarRenderer::renderTo(
    QwtPolarPlot *plot, QSvgGenerator &generator ) const
{
    QRectF rect = generator.viewBoxF();
    if ( rect.isEmpty() )
        rect.setRect( 0, 0, generator.width(), generator.height() );

    if ( rect.isEmpty() )
        rect.setRect( 0, 0, 800, 600 ); // something

    QPainter p( &generator );
    render( plot, &p, rect );
}