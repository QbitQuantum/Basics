inline btVector3 findNearestPointToLine(const btVector3 &pt1, const btVector3 &pt2, const btVector3 &testPoint, float &uDistance)
{
    const btVector3 A = testPoint - pt1;
    const btVector3 u = (pt2-pt1).normalized();
	uDistance = A.dot(u);
	
    return pt1 + uDistance * u;
};