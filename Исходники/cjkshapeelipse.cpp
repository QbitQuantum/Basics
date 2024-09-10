QPainterPath CCJKShapeElipse::GetShape() const
{
	CJK_D(const CCJKShapeElipse);
	QPainterPath path = GetPath();
	if(d->tracker == TTEdit)
		path.addRect(d->boundRect);
	path = StrokePath(path);
	if (d->brush != Qt::NoBrush)
		path.addEllipse(d->boundRect);

	return path;
}