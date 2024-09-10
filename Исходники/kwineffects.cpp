ScreenPaintData::ScreenPaintData(const ScreenPaintData &other)
    : PaintData()
    , d(new Private())
{
    translate(other.translation());
    setXScale(other.xScale());
    setYScale(other.yScale());
    setZScale(other.zScale());
    setRotationOrigin(other.rotationOrigin());
    setRotationAxis(other.rotationAxis());
    setRotationAngle(other.rotationAngle());
    d->projectionMatrix = other.d->projectionMatrix;
}