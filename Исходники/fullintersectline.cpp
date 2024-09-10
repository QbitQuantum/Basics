inline bool i_BoundingBoxTest(const LTVector& Point1, const LTVector& Point2, const LTObject *pServerObj, 
    LTVector *pIntersectPt, LTPlane *pIntersectPlane)
{
    float t;
    float testCoords[2];
	const LTVector& min = pServerObj->GetBBoxMin();
	const LTVector& max = pServerObj->GetBBoxMax();

    // Left/Right.
    if (Point1.x < min.x) 
	{
        if (Point2.x < min.x) 
		{
            return false;
        }
    
        DO_PLANE_TEST_X(min.x, x, y, z, -1.0f);
    }
    else if (Point1.x > max.x) 
	{
        if (Point2.x > max.x) 
		{
            return false;
        }

        DO_PLANE_TEST_X(max.x, x, y, z, 1.0f);
    }

    // Top/Bottom.
    if (Point1.y < min.y) 
	{
        if (Point2.y < min.y) 
		{
            return false;
        }
    
        DO_PLANE_TEST_Y(min.y, y, x, z, -1.0f);
    }
    else if (Point1.y > max.y) 
	{
        if (Point2.y > max.y) 
		{
            return false;
        }

        DO_PLANE_TEST_Y(max.y, y, x, z, 1.0f);
    }

    // Front/Back.
    if (Point1.z < min.z) 
	{
        if (Point2.z < min.z) 
		{
            return false;
        }
    
        DO_PLANE_TEST_Z(min.z, z, x, y, -1.0f);
    }
    else if (Point1.z > max.z) 
	{
        if (Point2.z > max.z) 
		{
            return false;
        }

        DO_PLANE_TEST_Z(max.z, z, x, y, 1.0f);
    }


	// If we get here and our hackish backwards compatibility flag is set, we need to check
	// to see if Point1 is completely inside the dims.  The above checks don't catch this case...

	if (g_bCheckIfFromPointIsInsideObject)
	{
		if ( (min.x <= Point1.x && Point1.x <= max.x) &&
			 (min.y <= Point1.y && Point1.y <= max.y) &&
			 (min.z <= Point1.z && Point1.z <= max.z) )
		{
			LTVector vNormal = (Point1 - Point2);
			vNormal.Normalize();

			LTPlane pPlane;
			pPlane.Init(vNormal, Point1);

			*pIntersectPt = Point1;
			*pIntersectPlane = pPlane;

			return true;
		}
	}

    return false;
}