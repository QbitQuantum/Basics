ccPlane* ccGenericPointCloud::fitPlane(double* rms /*= 0*/)
{
	//number of points
	unsigned count = size();
	if (count<3)
		return 0;

	CCLib::Neighbourhood Yk(this);

	//we determine plane normal by computing the smallest eigen value of M = 1/n * S[(p-µ)*(p-µ)']
	CCLib::SquareMatrixd eig = Yk.computeCovarianceMatrix().computeJacobianEigenValuesAndVectors();

	//invalid matrix?
	if (!eig.isValid())
	{
		//ccConsole::Warning("[ccPointCloud::fitPlane] Failed to compute plane/normal for cloud '%s'",getName());
		return 0;
	}
	eig.sortEigenValuesAndVectors();

	//plane equation
	PointCoordinateType theLSQPlane[4];

	//the smallest eigen vector corresponds to the "least square best fitting plane" normal
	double vec[3];
	eig.getEigenValueAndVector(2,vec);
	//PointCoordinateType sign = (vec[2] < 0.0 ? -1.0 : 1.0);  //plane normal (always with a positive 'Z' by default)
	for (unsigned i=0;i<3;++i)
		theLSQPlane[i]=/*sign*/(PointCoordinateType)vec[i];
	CCVector3 N(theLSQPlane);

	//we also get centroid
	const CCVector3* G = Yk.getGravityCenter();
	assert(G);

	//eventually we just have to compute 'constant' coefficient a3
	//we use the fact that the plane pass through the centroid --> GM.N = 0 (scalar prod)
	//i.e. a0*G[0]+a1*G[1]+a2*G[2]=a3
	theLSQPlane[3] =  G->dot(N);

	//least-square fitting RMS
	if (rms)
	{
		placeIteratorAtBegining();
		*rms = 0.0;
		for (unsigned k=0;k<count;++k)
		{
			double d = (double)CCLib::DistanceComputationTools::computePoint2PlaneDistance(getNextPoint(),theLSQPlane);
			*rms += d*d;
		}
		*rms = sqrt(*rms)/(double)count;
	}

	//we has a plane primitive to the cloud
	eig.getEigenValueAndVector(0,vec); //main direction
	CCVector3 X(vec[0],vec[1],vec[2]); //plane normal
	//eig.getEigenValueAndVector(1,vec); //intermediate direction
	//CCVector3 Y(vec[0],vec[1],vec[2]); //plane normal
	CCVector3 Y = N * X;

	//we eventually check for plane extents
	PointCoordinateType minX=0.0,maxX=0.0,minY=0.0,maxY=0.0;
	placeIteratorAtBegining();
	for (unsigned k=0;k<count;++k)
	{
		//projetion into local 2D plane ref.
		CCVector3 P = *getNextPoint() - *G;
		PointCoordinateType x2D = P.dot(X);
		PointCoordinateType y2D = P.dot(Y);

		if (k!=0)
		{
			if (minX<x2D)
				minX=x2D;
			else if (maxX>x2D)
				maxX=x2D;
			if (minY<y2D)
				minY=y2D;
			else if (maxY>y2D)
				maxY=y2D;
		}
		else
		{
			minX=maxX=x2D;
			minY=maxY=y2D;
		}
	}

	//we recenter plane (as it is not always the case!)
	float dX = maxX-minX;
	float dY = maxY-minY;
	CCVector3 Gt = *G + X * (minX+dX*0.5);
	Gt += Y * (minY+dY*0.5);
	ccGLMatrix glMat(X,Y,N,Gt);

	return new ccPlane(dX,dY,&glMat);
}