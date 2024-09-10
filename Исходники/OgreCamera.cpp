	//_______________________________________________________
	//|														|
	//|	forwardIntersect									|
	//|	-----------------------------						|
	//|	Forward intersect the camera's frustum rays with	|
	//| a specified plane of interest.						|
	//| Note that if the frustum rays shoot out and would	|
	//| back project onto the plane, this means the forward	|
	//| intersection of the frustum would occur at the		|
	//| line at infinity.									|
	//|_____________________________________________________|
	//
	void Camera::forwardIntersect(const Plane& worldPlane, vector<Vector4>::type* intersect3d) const
	{
		if(!intersect3d)
			return;

		Vector3 trCorner = getWorldSpaceCorners()[0];
		Vector3 tlCorner = getWorldSpaceCorners()[1];
		Vector3 blCorner = getWorldSpaceCorners()[2];
		Vector3 brCorner = getWorldSpaceCorners()[3];

		// need some sort of rotation that will bring the plane normal to the z axis
		Plane pval = worldPlane;
		if(pval.normal.z < 0.0)
		{
			pval.normal *= -1.0;
			pval.d *= -1.0;
		}
		Quaternion invPlaneRot = pval.normal.getRotationTo(Vector3::UNIT_Z);

		// get rotated light
		Vector3 lPos = invPlaneRot * getDerivedPosition();
		Vector3 vec[4];
		vec[0] = invPlaneRot * trCorner - lPos;
		vec[1] = invPlaneRot * tlCorner - lPos; 
		vec[2] = invPlaneRot * blCorner - lPos; 
		vec[3] = invPlaneRot * brCorner - lPos; 

		// compute intersection points on plane
		vector<Vector4>::type iPnt = getRayForwardIntersect(lPos, vec, -pval.d);


		// return wanted data
		if(intersect3d) 
		{
			Quaternion planeRot = invPlaneRot.Inverse();
			(*intersect3d).clear();
			for(unsigned int i=0; i<iPnt.size(); i++)
			{
				Vector3 intersection = planeRot * Vector3(iPnt[i].x, iPnt[i].y, iPnt[i].z);
				(*intersect3d).push_back(Vector4(intersection.x, intersection.y, intersection.z, iPnt[i].w));
			}
		}
	}