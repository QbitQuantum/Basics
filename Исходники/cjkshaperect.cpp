bool CCJKShapeRect::Intersect( const QRect &rect )
{
	CJK_D(const CCJKShapeRect);
	if (d->brush.style() != Qt::NoBrush)
	{
		return d->boundRect.intersects(rect);
	}
	else
	{
		QPainterPath path = StrokePath(GetPath());
		return path.intersects(rect);
	}
	return false;
}