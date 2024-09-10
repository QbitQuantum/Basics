/**
* \brief Add the second point of a bounding box when we release the clic
* \author Jules Gorny - ALCoV team, ISIT, UMR 6284 UdA – CNRS
**/
void QImageLabel::mouseRelease(int x, int y)
{
	int w = imagesForLabel[*displayedImg-1]->width(); 
	int h = imagesForLabel[*displayedImg-1]->height();
	//If we release the mouse out of the image
	if(x<0) x=0;
	if(x>w) x=w-1;
	if(y<0) y=0;
	if(y>h) y=h-1;
	
	x = int(x*ratio);
	y = int(y*ratio);
	
	BoundingBox *tmp = bbs->at(bbs->size()-1);

	//The BoundingBox box will be define by the upper left corner and the bottom right corner
	if( tmp->x1() < x )
		tmp->setX2(x);
	else
	{
		tmp->setX2(tmp->x1());
		tmp->setX1(x);
	}

	if( tmp->y1() < y )
		tmp->setY2(y);
	else
	{
		tmp->setY2(tmp->y1());
		tmp->setY1(y);
	}
	
	drawBoundingBoxes();
		
	emit signal_bbNumberChanged();
	rectNotEnded = false;
}