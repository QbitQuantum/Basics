void BbScene::testAddRect()
{
	QGraphicsRectItem* item = new QGraphicsRectItem;

	QPen thePen = BbUtil::createPen(5, Qt::red);
	item->setPen(thePen);

	double ww = getPageWidth() - 20;
	double hh = getPageHeight() - 20;
	QRectF theRect(-ww / 2, -hh / 2, ww, hh);
	item->setRect(theRect);

	addItem(item);	
}