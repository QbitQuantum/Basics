bool CollisionBox::checkPointInSquare(unsigned int squareNumber, TVector point)
{
	TVector tmp = point - collisionSquare[squareNumber].center;

	if(tmp.dot(xNormal) > xLong)
		return false;
	if(tmp.dot(xNormal) < -xLong)
		return false;
	if(tmp.dot(yNormal) > yHeight)
		return false;
	if(tmp.dot(yNormal) <-yHeight)
		return false;
	if(tmp.dot(zNormal) > zWidth)
		return false;
	if(tmp.dot(zNormal) <-zWidth)
		return false;
	return true;
}