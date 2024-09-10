/* Calculates the GLOBAL rotation of the world, not relative to the world's current rotation
 * * pFrom, the first point,
 * * pDest, the next point. The two points create a line and the line's angle from the x axis is measured */
double SplineTraveler::calcRotation(Vector3f axis, Vector3f pVertex, Vector3f pDest)
{
	//Vector3f firstBranch = (pFrom - pVertex).Normalize();  
	Vector3f secondBranch = (pDest - pVertex).Normalize(); 

	//TODO handle 180 degree case
	float railAngle;
	//dot product angle. magtides of the vectors are already equal to one
	railAngle = acos(axis.Dot(secondBranch));
	if(secondBranch.z > 0)
	{
		railAngle = 2.0*3.14159265 - railAngle;
	}
	rotationAngle = railAngle;
	rotateAxis = secondBranch.Cross(axis);   //axis of this rotation.
	//rotateAxis = Vector3f(0,1,0);
	/*Vector3f xaxis = Vector3f(1,0,0);
	Vector3f yaxis = Vector3f(0,1,0);
	Vector3f zaxis = Vector3f(0,0,1);
	Vector3f point = pDest - pFrom;
	point.y = 0;
	bool tr = false;
	//if(!(point.x == 0 && point.y == 0))
	{
		tr = true;
		double x = acos((point.Dot(xaxis))/(point.Magnitude()));
		if(point.z > 0)
		{
			x = 2.0*3.14159 - x;
		}

		//double y = acos((point.Dot(yaxis))/(point.Magnitude()));
		
		double y = 0;

		double z = 0;//acos((point.Dot(zaxis))/(point.Magnitude()));

		grotation = Vector3f(x,y,z);
	}*/
	return railAngle;
}