ccQuadric* ccQuadric::Fit(CCLib::GenericIndexedCloudPersist *cloud, double* rms/*=0*/)
{
	//number of points
	unsigned count = cloud->size();
	if (count < CC_LOCAL_MODEL_MIN_SIZE[HF])
	{
		ccLog::Warning(QString("[ccQuadric::fitTo] Not enough points in input cloud to fit a quadric! (%1 at the very least are required)").arg(CC_LOCAL_MODEL_MIN_SIZE[HF]));
		return 0;
	}

	//project the points on a 2D plane
	CCVector3 G, X, Y, N;
	{
		CCLib::Neighbourhood Yk(cloud);
		
		//plane equation
		const PointCoordinateType* theLSQPlane = Yk.getLSQPlane();
		if (!theLSQPlane)
		{
			ccLog::Warning("[ccQuadric::Fit] Not enough points to fit a quadric!");
			return 0;
		}

		assert(Yk.getGravityCenter());
		G = *Yk.getGravityCenter();

		//local base
		N = CCVector3(theLSQPlane);
		assert(Yk.getLSQPlaneX() && Yk.getLSQPlaneY());
		X = *Yk.getLSQPlaneX(); //main direction
		Y = *Yk.getLSQPlaneY(); //secondary direction
	}

	//project the points in a temporary cloud
	ccPointCloud tempCloud("temporary");
	if (!tempCloud.reserve(count))
	{
		ccLog::Warning("[ccQuadric::Fit] Not enough memory!");
		return 0;
	}

	cloud->placeIteratorAtBegining();
	for (unsigned k=0; k<count; ++k)
	{
		//projection into local 2D plane ref.
		CCVector3 P = *(cloud->getNextPoint()) - G;

		tempCloud.addPoint(CCVector3(P.dot(X),P.dot(Y),P.dot(N)));
	}

	CCLib::Neighbourhood Zk(&tempCloud);
	{
		//set exact values for gravity center and plane equation
		//(just to be sure and to avoid re-computing them)
		Zk.setGravityCenter(CCVector3(0,0,0));
		PointCoordinateType perfectEq[4] = { 0, 0, 1, 0 };
		Zk.setLSQPlane(	perfectEq,
						CCVector3(1,0,0),
						CCVector3(0,1,0),
						CCVector3(0,0,1));
	}

	uchar hfdims[3];
	const PointCoordinateType* eq = Zk.getHeightFunction(hfdims);
	if (!eq)
	{
		ccLog::Warning("[ccQuadric::Fit] Failed to fit a quadric!");
		return 0;
	}

	//we recenter the quadric object
	ccGLMatrix glMat(X,Y,N,G);

	ccBBox bb = tempCloud.getBB();
	CCVector2 minXY(bb.minCorner().x,bb.minCorner().y);
	CCVector2 maxXY(bb.maxCorner().x,bb.maxCorner().y);

	ccQuadric* quadric = new ccQuadric(minXY, maxXY, eq, hfdims, &glMat);

	quadric->setMetaData(QString("Equation"),QVariant(quadric->getEquationString()));

	//compute rms if necessary
	if (rms)
	{
		const uchar& dX = hfdims[0];
		const uchar& dY = hfdims[1];
		const uchar& dZ = hfdims[2];

		*rms = 0;

		for (unsigned k=0; k<count; ++k)
		{
			//projection into local 2D plane ref.
			const CCVector3* P = tempCloud.getPoint(k);

			PointCoordinateType z = eq[0] + eq[1]*P->u[dX] + eq[2]*P->u[dY] + eq[3]*P->u[dX]*P->u[dX] + eq[4]*P->u[dX]*P->u[dY] + eq[5]*P->u[dY]*P->u[dY];
			*rms += (z-P->z)*(z-P->z);
		}

		if (count)
		{
			*rms = sqrt(*rms / count);
			quadric->setMetaData(QString("RMS"),QVariant(*rms));
		}
	}
	
	return quadric;
}