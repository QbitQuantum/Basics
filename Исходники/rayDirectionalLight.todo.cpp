////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D RayDirectionalLight::getDiffuse(Point3D cameraPosition,RayIntersectionInfo& iInfo){

	Point3D L = -direction;
	Point3D Il = color;
	Point3D Kd = iInfo.material->diffuse;
	Point3D N = iInfo.normal;


	Point3D Id = Kd * (Il * (N.dot(L)));
	if(Id[0]>1) Id[0] = 1;
	if(Id[0]<0) Id[0] = 0;

	if(Id[1]>1) Id[1] = 1;
	if(Id[1]<0) Id[1] = 0;

	if(Id[2]>1) Id[2] = 1;
	if(Id[2]<0) Id[2] = 0;
    //printf("directional light:%f,%f,%f\n",Id[0],Id[1],Id[2]);
	return Id;
}