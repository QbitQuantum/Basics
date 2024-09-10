/*!
  Render a plot to a file

  Supported formats are:

  - pdf\n
    Portable Document Format PDF
  - ps\n
    Postcript
  - svg\n
    Scalable Vector Graphics SVG
  - all image formats supported by Qt\n
    see QImageWriter::supportedImageFormats()

  Scalable vector graphic formats like PDF or SVG are superior to
  raster graphics formats.

  \param plot Plot widget
  \param fileName Path of the file, where the document will be stored
  \param format Format for the document
  \param sizeMM Size for the document in millimeters.
  \param resolution Resolution in dots per Inch (dpi)

  \sa renderTo(), render(), QwtPainter::setRoundingAlignment()
*/
void QwtPlotRenderer::renderDocument( QwtPlot *plot,
    const QString &fileName, const QString &format,
    const QSizeF &sizeMM, int resolution )
{
    if ( plot == NULL || sizeMM.isEmpty() || resolution <= 0 )
        return;

    QString title = plot->title().text();
    if ( title.isEmpty() )
        title = "Plot Document";

    const double mmToInch = 1.0 / 25.4;
    const QSizeF size = sizeMM * mmToInch * resolution;

    const QRectF documentRect( 0.0, 0.0, size.width(), size.height() );

    const QString fmt = format.toLower();
    if ( fmt == "pdf" )
    {
#ifndef QT_NO_PRINTER
        QPrinter printer;
        printer.setColorMode( QPrinter::Color );
        printer.setFullPage( true );
        printer.setPaperSize( sizeMM, QPrinter::Millimeter );
        printer.setDocName( title );
        printer.setOutputFileName( fileName );
        printer.setOutputFormat( QPrinter::PdfFormat );
        printer.setResolution( resolution );

        QPainter painter( &printer );
        render( plot, &painter, documentRect );
#endif
    }
    else if ( fmt == "ps" )
    {
#if QT_VERSION < 0x050000
#ifndef QT_NO_PRINTER
        QPrinter printer;
        printer.setColorMode( QPrinter::Color );
        printer.setFullPage( true );
        printer.setPaperSize( sizeMM, QPrinter::Millimeter );
        printer.setDocName( title );
        printer.setOutputFileName( fileName );
        printer.setOutputFormat( QPrinter::PostScriptFormat );
        printer.setResolution( resolution );

        QPainter painter( &printer );
        render( plot, &painter, documentRect );
#endif
#endif
    }
    else if ( fmt == "svg" )
    {
#ifndef QWT_NO_SVG
#ifdef QT_SVG_LIB
#if QT_VERSION >= 0x040500
        QSvgGenerator generator;
        generator.setTitle( title );
        generator.setFileName( fileName );
        generator.setResolution( resolution );
        generator.setViewBox( documentRect );

        QPainter painter( &generator );
        render( plot, &painter, documentRect );
#endif
#endif
#endif
    }
    else
    {
        if ( QImageWriter::supportedImageFormats().indexOf(
            format.toLatin1() ) >= 0 )
        {
            const QRect imageRect = documentRect.toRect();
            const int dotsPerMeter = qRound( resolution * mmToInch * 1000.0 );

            QImage image( imageRect.size(), QImage::Format_ARGB32 );
            image.setDotsPerMeterX( dotsPerMeter );
            image.setDotsPerMeterY( dotsPerMeter );
            image.fill( QColor( Qt::white ).rgb() );

            QPainter painter( &image );
            render( plot, &painter, imageRect );
            painter.end();

            image.save( fileName, format.toLatin1() );
        }
    }
}