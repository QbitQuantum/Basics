    void Na2DViewer::transformPainterToCurrentCamera(QPainter& painter)
{
    // adjust painter coordinate system to place image correctly
    float scale = defaultScale * cameraModel.scale();
    // origin at pixel center, not corner
    qreal w2 = (pixmap.width() - 1.0) / 2.0;
    qreal h2 = (pixmap.height() - 1.0) / 2.0;
    qreal tx = w2 + flip_X * (cameraModel.focus().x() - w2) + 0.5;
    qreal ty = h2 + flip_Y * (cameraModel.focus().y() - h2) + 0.5;
    painter.translate(width()/2.0 - tx * scale, height()/2.0 - ty * scale);
    painter.scale(scale, scale);

    // I want to convert screen coordinates to image coordinates;
    // The QPainter object knows this transformation.
    // This nomenclature for the transforms, e.g. X_view_img , comes from the
    // advanced dynamics community at Stanford, specifically the disciples of Thomas Kane.
    X_view_img = painter.transform();
    X_img_view = painter.transform().inverted();
}