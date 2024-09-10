SimpleCloud* MeshSamplingTools::samplePointsOnMesh(GenericMesh* theMesh,
													double samplingDensity,
													unsigned theoricNumberOfPoints,
													GenericProgressCallback* progressCb,
													GenericChunkedArray<1,unsigned>* triIndices/*=0*/)
{
	assert(theMesh);
	unsigned triCount = (theMesh ? theMesh->size() : 0);
	if (triCount==0)
		return 0;

	if (theoricNumberOfPoints < 1)
        return 0;


	SimpleCloud* sampledCloud = new SimpleCloud();
	if (!sampledCloud->reserve(theoricNumberOfPoints)) //not enough memory
	{
		delete sampledCloud;
		return 0;
	}

	if (triIndices)
	{
	    triIndices->clear();
		//not enough memory? DGM TODO: we should warn the caller
		if (!triIndices->reserve(theoricNumberOfPoints) || triIndices->capacity() < theoricNumberOfPoints)
		{
			delete sampledCloud;
			triIndices->clear();
			return 0;
		}
	}

	NormalizedProgress* normProgress=0;
    if(progressCb)
    {
		normProgress = new NormalizedProgress(progressCb,triCount);
		progressCb->setMethodTitle("Mesh sampling");
		char buffer[256];
		sprintf(buffer,"Triangles: %i\nPoints: %i",triCount,theoricNumberOfPoints);
		progressCb->setInfo(buffer);
        progressCb->reset();
		progressCb->start();
	}

	unsigned addedPoints=0;

	//for each triangle
	theMesh->placeIteratorAtBegining();
	for (unsigned n=0;n<triCount;++n)
	{
		const GenericTriangle* tri = theMesh->_getNextTriangle();

		//summits (OAB)
		const CCVector3 *O = tri->_getA();
		const CCVector3 *A = tri->_getB();
		const CCVector3 *B = tri->_getC();

		//edges (OA and OB)
		CCVector3 u = *A - *O;
		CCVector3 v = *B - *O;

		//we compute the (twice) the triangle area
		CCVector3 N = u.cross(v);
		double S = N.norm()/2.0;

		//we deduce the number of points to generate on this face
		double fPointsToAdd = S*samplingDensity;
		unsigned pointsToAdd = static_cast<unsigned>(fPointsToAdd);

        //if the face area is smaller than the surface/random point
		if (pointsToAdd == 0)
		{
			//we add a point with the same probability as its (relative) area
			if (static_cast<double>(rand()) <= fPointsToAdd * static_cast<double>(RAND_MAX))
                pointsToAdd = 1;
		}

		if (pointsToAdd)
		{
			if (addedPoints + pointsToAdd >= theoricNumberOfPoints)
			{
				theoricNumberOfPoints+=pointsToAdd;
				if (!sampledCloud->reserve(theoricNumberOfPoints)
					|| (triIndices && triIndices->capacity() < theoricNumberOfPoints && !triIndices->reserve(theoricNumberOfPoints))) //not enough memory
				{
					delete sampledCloud;
					sampledCloud = 0;
					triIndices->clear();
					break;
				}
			}

			for (unsigned i=0; i<pointsToAdd; ++i)
			{
				//we generates random points as in:
				//'Greg Turk. Generating random points in triangles. In A. S. Glassner, editor,Graphics Gems, pages 24-28. Academic Press, 1990.'
				double x = static_cast<double>(rand())/static_cast<double>(RAND_MAX);
				double y = static_cast<double>(rand())/static_cast<double>(RAND_MAX);

				//we test if the generated point lies on the right side of (AB)
				if (x+y > 1.0)
				{
                    x = 1.0-x;
                    y = 1.0-y;
                }

				CCVector3 P = (*O) + static_cast<PointCoordinateType>(x) * u + static_cast<PointCoordinateType>(y) * v;

				sampledCloud->addPoint(P);
				if (triIndices)
					triIndices->addElement(n);
				++addedPoints;
			}
		}

		if (normProgress && !normProgress->oneStep())
			break;
	}

	if (normProgress)
	{
        delete normProgress;
		normProgress = 0;
	}

	if (sampledCloud) //can be in case of memory overflow!
	{
		if (addedPoints)
		{
			sampledCloud->resize(addedPoints); //should always be ok as addedPoints<theoricNumberOfPoints
			if (triIndices)
				triIndices->resize(addedPoints);
		}
		else
		{
			delete sampledCloud;
			sampledCloud = 0;
			if (triIndices)
				triIndices->clear();
		}
	}

	return sampledCloud;
}