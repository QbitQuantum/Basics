ccPlane* ccPlane::Fit(CCLib::GenericIndexedCloudPersist *cloud, double* rms/*=0*/)
{
    //number of points
    unsigned count = cloud->size();
    if (count < 3)
    {
        ccLog::Warning("[ccPlane::Fit] Not enough points in input cloud to fit a plane!");
        return 0;
    }

    CCLib::Neighbourhood Yk(cloud);

    //plane equation
    const PointCoordinateType* theLSPlane = Yk.getLSPlane();
    if (!theLSPlane)
    {
        ccLog::Warning("[ccPlane::Fit] Not enough points to fit a plane!");
        return 0;
    }

    //get the centroid
    const CCVector3* G = Yk.getGravityCenter();
    assert(G);

    //and a local base
    CCVector3 N(theLSPlane);
    const CCVector3* X = Yk.getLSPlaneX(); //main direction
    assert(X);
    CCVector3 Y = N * (*X);

    //compute bounding box in 2D plane
    CCVector2 minXY(0,0), maxXY(0,0);
    cloud->placeIteratorAtBegining();
    for (unsigned k=0; k<count; ++k)
    {
        //projection into local 2D plane ref.
        CCVector3 P = *(cloud->getNextPoint()) - *G;

        CCVector2 P2D( P.dot(*X), P.dot(Y) );

        if (k != 0)
        {
            if (minXY.x > P2D.x)
                minXY.x = P2D.x;
            else if (maxXY.x < P2D.x)
                maxXY.x = P2D.x;
            if (minXY.y > P2D.y)
                minXY.y = P2D.y;
            else if (maxXY.y < P2D.y)
                maxXY.y = P2D.y;
        }
        else
        {
            minXY = maxXY = P2D;
        }
    }

    //we recenter the plane
    PointCoordinateType dX = maxXY.x-minXY.x;
    PointCoordinateType dY = maxXY.y-minXY.y;
    CCVector3 Gt = *G + *X * (minXY.x + dX / 2) + Y * (minXY.y + dY / 2);
    ccGLMatrix glMat(*X,Y,N,Gt);

    ccPlane* plane = new ccPlane(dX, dY, &glMat);

    //compute least-square fitting RMS if requested
    if (rms)
    {
        *rms = CCLib::DistanceComputationTools::computeCloud2PlaneDistanceRMS(cloud, theLSPlane);
        plane->setMetaData(QString("RMS"),QVariant(*rms));
    }


    return plane;
}