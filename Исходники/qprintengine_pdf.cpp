int QPdfEnginePrivate::addBrushPattern(const QTransform &m, bool *specifyColor, int *gStateObject)
{
    int paintType = 2; // Uncolored tiling
    int w = 8;
    int h = 8;

    *specifyColor = true;
    *gStateObject = 0;

    QTransform matrix = m;
    matrix.translate(brushOrigin.x(), brushOrigin.y());
    matrix = matrix * pageMatrix();
    //qDebug() << brushOrigin << matrix;

    Qt::BrushStyle style = brush.style();
    if (style == Qt::LinearGradientPattern) {// && style <= Qt::ConicalGradientPattern) {
#ifdef USE_NATIVE_GRADIENTS
        *specifyColor = false;
        return gradientBrush(b, matrix, gStateObject);
#else
        return 0;
#endif
    }

    if ((!brush.isOpaque() && brush.style() < Qt::LinearGradientPattern) || opacity != 1.0)
        *gStateObject = addConstantAlphaObject(qRound(brush.color().alpha() * opacity),
                                               qRound(pen.color().alpha() * opacity));

    int imageObject = -1;
    QByteArray pattern = QPdf::patternForBrush(brush);
    if (pattern.isEmpty()) {
        if (brush.style() != Qt::TexturePattern)
            return 0;
        QImage image = brush.texture().toImage();
        bool bitmap = true;
        imageObject = addImage(image, &bitmap, qt_pixmap_id(brush.texture()));
        if (imageObject != -1) {
            QImage::Format f = image.format();
            if (f != QImage::Format_MonoLSB && f != QImage::Format_Mono) {
                paintType = 1; // Colored tiling
                *specifyColor = false;
            }
            w = image.width();
            h = image.height();
            QTransform m(w, 0, 0, -h, 0, h);
            QPdf::ByteStream s(&pattern);
            s << QPdf::generateMatrix(m);
            s << "/Im" << imageObject << " Do\n";
        }
    }

    QByteArray str;
    QPdf::ByteStream s(&str);
    s << "<<\n"
        "/Type /Pattern\n"
        "/PatternType 1\n"
        "/PaintType " << paintType << "\n"
        "/TilingType 1\n"
        "/BBox [0 0 " << w << h << "]\n"
        "/XStep " << w << "\n"
        "/YStep " << h << "\n"
        "/Matrix ["
      << matrix.m11()
      << matrix.m12()
      << matrix.m21()
      << matrix.m22()
      << matrix.dx()
      << matrix.dy() << "]\n"
        "/Resources \n<< "; // open resource tree
    if (imageObject > 0) {
        s << "/XObject << /Im" << imageObject << ' ' << imageObject << "0 R >> ";
    }
    s << ">>\n"
        "/Length " << pattern.length() << "\n"
        ">>\n"
        "stream\n"
      << pattern
      << "endstream\n"
        "endobj\n";

    int patternObj = addXrefEntry(-1);
    write(str);
    currentPage->patterns.append(patternObj);
    return patternObj;
}