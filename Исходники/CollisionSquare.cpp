bool CollisionSquare::testIntersection(const TVector &position, const TVector &direction, double &lamda)
{
	double DotProduct=direction.dot(normal);
	double l2;
	if(DotProduct >= 0.0)			//chi xet nhung vat di tu huong doi dien mat phang toi
		return false;
	
    //determine if ray paralle to plane
    if ((DotProduct<ZERO)&&(DotProduct>-ZERO)) 
		return false;
	
    l2=(normal.dot(center-position))/DotProduct;		//if direction is unit vector then l2 is distant from current position to collision
														//if direction is velocity then l2 is time from currunt position to collision
	
    if (l2<-ZERO)		
		return false;
	
	lamda=l2;
    return true;
}