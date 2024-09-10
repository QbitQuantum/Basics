bool Path::strokeContains(StrokeStyleApplier* applier, const FloatPoint& point) const
{
    ASSERT(applier);

    // FIXME: We should try to use a 'shared Context' instead of creating a new ImageBuffer
    // on each call.
    OwnPtr<ImageBuffer> scratchImage = ImageBuffer::create(IntSize(1, 1));
    GraphicsContext* gc = scratchImage->context();
    QPainterPathStroker stroke;
    applier->strokeStyle(gc);

    QPen pen = gc->pen();
    stroke.setWidth(pen.widthF());
    stroke.setCapStyle(pen.capStyle());
    stroke.setJoinStyle(pen.joinStyle());
    stroke.setMiterLimit(pen.miterLimit());
    stroke.setDashPattern(pen.dashPattern());
    stroke.setDashOffset(pen.dashOffset());

    return stroke.createStroke(m_path).contains(point);
}