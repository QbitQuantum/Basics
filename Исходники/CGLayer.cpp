void CGContextDrawLayerInRect(CGContextRef context, CGRect rect, CGLayerRef layer)
{
	QPainter* painter = CGContextGetPainter(context);
	QTransform tf = painter->worldTransform();
	qreal sx, sy;
	CGSize origSize = CGLayerGetSize(layer);
	
	sx = CGRectGetWidth(rect) / origSize.width;
	sy = CGRectGetHeight(rect) / origSize.height;
	
	painter->scale(sx, sy);
	
	painter->drawPicture(QPointF(rect.origin.x / sx, rect.origin.y / sy), *layer->picture);
	
	painter->setWorldTransform(tf);
}