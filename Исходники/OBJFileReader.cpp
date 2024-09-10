void preprocessing(Mesh * _mesh, Vector3 rotate, Vector3 scale, Vector3 translate, 	std::vector<Vector3 * >& normals )
{
	// compute bounding box
		Vector3 minPosition;
		Vector3 maxPosition;
		Vector3 centerPosition;
		double radius=0.0;
		maxPosition[0]=std::numeric_limits<double>::min();
		maxPosition[1]=std::numeric_limits<double>::min();
		maxPosition[2]=std::numeric_limits<double>::min();

		minPosition[0]=std::numeric_limits<double>::max();
		minPosition[1]=std::numeric_limits<double>::max();
		minPosition[2]=std::numeric_limits<double>::max();

		for(unsigned int i=0;i<_mesh->numberOfVertices();i++)
		{
			Vector3 point = *(_mesh->getVertex(i)->getPosition());
			if(point[0] < minPosition[0])
			{
				minPosition[0] = point[0];
			}
			if(point[1] <minPosition[1])
			{
				minPosition[1] = point[1];
			}
			if(point[2] <minPosition[2])
			{
				minPosition[2] = point[2];
			}

			if(point[0] >maxPosition[0])
			{
				maxPosition[0] = point[0];
			}
			if(point[1] >maxPosition[1])
			{
				maxPosition[1] = point[1];
			}
			if(point[2] >maxPosition[2])
			{
				maxPosition[2] = point[2];
			}

		}
	// compute center position
	centerPosition[0] = (maxPosition[0] + minPosition[0])/2.0;
	centerPosition[1] = (maxPosition[1] + minPosition[1])/2.0;
	centerPosition[2] = (maxPosition[2] + minPosition[2])/2.0;

	// compute radius
	//radius =	(maxPosition[0]-centerPosition[0])*(maxPosition[0]-centerPosition[0]) +
	//			(maxPosition[1]-centerPosition[1])*(maxPosition[1]-centerPosition[1])	+
	//			(maxPosition[2]-centerPosition[2])*(maxPosition[2]-centerPosition[2]);

	//bounding box diagonal length:
	double bbdl = (maxPosition-minPosition).length();

	// normalize size and translate to origin
	for (unsigned int i=0; i < _mesh->numberOfVertices(); i++) {
		 Vector3 p = *(_mesh->getVertex(i)->getPosition());
			p = (p-centerPosition)/bbdl;
			
		 _mesh->getVertex(i)->setPosition(p);
	}

	// transform mesh corresponding to rotate, translate and scale
	Matrix4 s;
	s.loadScaling(scale);
	Matrix4 rx;
	rx.loadRotation(Vector3(1.,0.,0.),(M_PI/180.)*rotate.x);
	Matrix4 ry;
	ry.loadRotation(Vector3(0.,1.,0.),(M_PI/180.)*rotate.y);
	Matrix4 rz;
	rz.loadRotation(Vector3(0.,0.,1.),(M_PI/180.)*rotate.z);
	Matrix4 Tf;
	Tf.loadIdentity();
	//Tf *= s*rx*ry*rz*t;

	Tf = s*rx*ry*rz;
	Matrix4 invTft = Tf.Inverse().Transpose();

	//Transform points and normals
	for (unsigned int i=0; i < _mesh->numberOfVertices(); i++) {
		Vector3 p = *(_mesh->getVertex(i)->getPosition());
		p = Tf*p + translate;
		_mesh->getVertex(i)->setPosition(p);
	}

	for( std::vector<Vector3*>::iterator it=normals.begin(); it!=normals.end(); ++it)
	{
		Vector3* n = (*it);
		Vector4 n4 = invTft*Vector4(*n,0.);
		*n = Vector3(n4.x,n4.y,n4.z);
		n->normalize();
		//_mesh->getVertex(i)->setNormal(n);
	}
		
}