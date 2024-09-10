QPainterPath GraphicsUtils::shapeFromPath(const QPainterPath &path, const QPen &pen, double shapeStrokeWidth, bool includeOriginalPath)
{
	// this function mostly copied from QGraphicsItem::qt_graphicsItem_shapeFromPath


    // We unfortunately need this hack as QPainterPathStroker will set a width of 1.0
    // if we pass a value of 0.0 to QPainterPathStroker::setWidth()
    static const double penWidthZero = double(0.00000001);

    if (path == QPainterPath())
        return path;
    QPainterPathStroker ps;
    ps.setCapStyle(pen.capStyle());
    //ps.setCapStyle(Qt::FlatCap);
    if (shapeStrokeWidth <= 0.0)
        ps.setWidth(penWidthZero);
    else
        ps.setWidth(shapeStrokeWidth);

    ps.setJoinStyle(pen.joinStyle());
    ps.setMiterLimit(pen.miterLimit());
    QPainterPath p = ps.createStroke(path);
	if (includeOriginalPath) {
		p.addPath(path);
	}
    return p;
}