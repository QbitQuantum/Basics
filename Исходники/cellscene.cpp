void CellScene::drawPoints()
{
	points.clear();
	for (unsigned i = 0; i < y_count; i++)
		for (unsigned j = 0; j < x_count; j++) {
			QPointF temp;
			temp.setY(i * a * sin(M_PI / 3));
			if (i % 2 != 0) {
				if (j == 0)
					temp.setX(a * cos(M_PI / 3));
				if (j > 0) {
					temp.setX(0);
					for (unsigned k = 1; k <= j; k++)
						temp.setX(temp.x() + ((k - 1) % 2 + 1) * a);
					temp.setX(temp.x() + a * cos(M_PI / 3));
				}
			}
			if (i % 2 == 0) {
				if (j == 0)
					temp.setX(0);
				if (j > 0) {
					temp.setX(0);
					for (unsigned k = 1; k <= j; k++)
						temp.setX(temp.x() + ((k) % 2 + 1) * a);
				}
			}
			points.push_back(temp);
		}
	QGraphicsEllipseItem * pEllipseItem;
	QGraphicsLineItem * pLineItem;
	for (unsigned i = 0; i < points.size(); i++)
	{
		pEllipseItem = new QGraphicsEllipseItem(0, this);
		pEllipseItem->setPen(QPen(Qt::blue, 2));
		pEllipseItem->setRect(QRect(points[i].x(), points[i].y(), 4, 4));
		pEllipseItem->setData(0, "cellpoint");
		pEllipseItem->setData(1, "");
		pEllipseItem->setData(3,points[i]/a);
	}

//for (unsigned j=1;j<=y_count/2;j++)
//	{
//	for (unsigned i=0;i<x_count/2;i++)
//	{
//	pLineItem = new QGraphicsLineItem(0, this);
//	pLineItem->setLine(points[2*i].x(),points[2*i].y(),points[2*i+j*x_count].x(),points[2*i+j*x_count].y());
//	pLineItem->setPen(QPen(Qt::blue, 1));
//	pLineItem->setData(0, "line");

//	pLineItem = new QGraphicsLineItem(0, this);
//	pLineItem->setLine(points[2*i+j*x_count].x(),points[2*i+j*x_count].y(),points[2*i+j*x_count+1].x(),points[2*i+j*x_count+1].y());
//	pLineItem->setPen(QPen(Qt::blue, 1));
//	pLineItem->setData(0, "line");

//	pLineItem = new QGraphicsLineItem(0, this);
//	pLineItem->setLine(points[2*i+1].x(),points[2*i+1].y(),points[2*i+j*x_count+1].x(),points[2*i+j*x_count+1].y());
//	pLineItem->setPen(QPen(Qt::blue, 1));
//	pLineItem->setData(0, "line");

//	//pLineItem = new QGraphicsLineItem(points[2*i].x(),points[2*i].y(),points[2*i+j*x_count].x(),points[2*i+j*x_count].y(),this);

//	}

//}
}