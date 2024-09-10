Point3D RayPointLight::transparency(RayIntersectionInfo& iInfo,RayShape* shape,Point3D cLimit){
	Point3D temp = location - iInfo.iCoordinate;
	double dist = sqrt(temp.dot(temp));
	double atten = 0;
	atten = (constAtten + (linearAtten*dist) + (quadAtten*pow(dist,2.0)));

	Ray3D testRay = Ray3D();
	
	testRay.direction = temp.unit();
	testRay.position = iInfo.iCoordinate + testRay.direction;

	Point3D out = Point3D(1,1,1);	

	if(shape->intersect(testRay, iInfo, dist) != -1){		
		Point3D trans = iInfo.material->transparent;
		out = out * trans;
		out = out * transparency(iInfo, shape, cLimit / trans);
	}
	//1 = inShadow, 0 = no shadow
	return out;
}