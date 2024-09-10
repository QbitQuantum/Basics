void KMapScene::updatePath() {

	if(pathLength == 0){
		return;
	}
	QGraphicsLineItem *path;
	QGraphicsEllipseItem *ellipse;
	QGraphicsLineItem *smallLine;
	QPoint toP (0, 0), fromP (0, 0);
	int r, s, o;
	pathLineListRectReset();
	//setup up in the background the path line and then in the foreground the robot positions
	for (int ways = 0; ways < pathLength; ways++) {
		if (pathR[ways] == -1 && pathS[ways] == -1)
			break;
		r = pathR[ways];
		s = pathS[ways];
		if(r == 255 || s == 255){
			toP.setX (toGrid(0));
			toP.setY (toGrid(0));
		}else{
			toP.setX (cellCenterX[r][s]);
			toP.setY (cellCenterY[r][s]);
		}

		if(ways == 0 || ways == 1){
			fromP.setX (toGrid(0));
			fromP.setY (toGrid(0));
		}else{
			fromP.setX (cellCenterX[pathR[ways-1]][pathS[ways-1]]);
			fromP.setY (cellCenterY[pathR[ways-1]][pathS[ways-1]]);
		}

		path = pathLineList.at (ways);
		path->setLine (fromP.x(), fromP.y(), toP.x(), toP.y() );
		if(ways < pathLength){
			ellipse = pathEllipseList.at (ways);
			QPoint ellipseCenter;// ( cellCenterX[pathR[ways]][pathS[ways]] , cellCenterY[pathR[ways]][pathS[ways]] );
			
			if(r == 255 || s == 255){
				ellipseCenter.setX(toGrid(0));
				ellipseCenter.setY(toGrid(0));
			}else{
				ellipseCenter.setX(cellCenterX[r][s]);
				ellipseCenter.setY(cellCenterY[r][s]);
			}
			ellipse->setRect (ellipseCenter.x() - 5, ellipseCenter.y() - 5, 10, 10);
			float color = 100.0f + 155.0f*((float)(ways+1)/(float)pathLength);
			ellipse->setBrush (QColor ((int) color, 0, 0) );
		
			int pix = 7;
			smallLine = pathSmallLineList.at (ways);
			int orientation = pathO[ways];
			//orientation = orientation*2*M_PI/8;
			//cout << "Mpika " <<  toGrid (targetRing*moveStepInMeters)/2 << " " << toGrid (targetCell*moveStepInMeters)/2 << endl;
			float angle = orientation*2*M_PI/8.0f;
			int newX = -KMath::toCartesianY ( 10, angle);
			int newY = -KMath::toCartesianX ( 10, angle);
			toP.setX ( ellipseCenter.x() + newX);
			toP.setY (ellipseCenter.y() + newY );
			smallLine->setLine (ellipseCenter.x(), ellipseCenter.y(), toP.x(), toP.y() );
			//cout << ways << " " << orientation << endl;
		}
	}
}