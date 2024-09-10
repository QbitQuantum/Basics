    int Vector2::ConvexHullInPlace(Vector2* pointArray, size_t nPoints)
    {
        if(nPoints <= 3)
            return nPoints;

        // Lowest point of the set
        Vector2* lowest = &pointArray[0];
        for(int i = 1; i < nPoints; ++i)
        {
            if(lowest->y > pointArray[i].y)
                lowest = &pointArray[i];
        }

        lowest->swap(pointArray[0]);
        SortByPolarAngle pred;
        pred.perspective = pointArray[0];
        quicksort(pointArray + 1, nPoints - 1, pred);
        int nPointsInHull = 2;
        for(int i = 2; i < nPoints; ++i)
        {
            Vector2 lineA = pointArray[nPointsInHull - 1] - pointArray[nPointsInHull - 2];
            Vector2 lineB = pointArray[i] - pointArray(nPointsInHull - 2);
            Real lineAlen = lineA.lenght();
            Real lineBlen = lineB.lenght();
            bool dropLastPointFromHull = false;
            if(lineAlen >= 1e-5f)
                lineA /= Math::Sqrt(lineAlen);
            else
                dropLastPointFromHull = true;
            if(lineBlen >= 1e-5f)
                lineB /= Math::Sqrt(lineBlen);

            Vector2 normal(-lineA.y, lineA.x);
            if(dropLastPointFromHull || normal.dotProduct(lineB) > 0.f || (normal.dotProduct(lineB) > -1e-4f && lineBlen >= lineAlen))
            {
                if(nPointsInHull > 2)
                {
                    --nPointsInHull;
                    --i;
                }
                else
                {
                    pointArray[nPointsInHull - 1] = pointArray[i];
                }
            }
            else
            {
                pointArray[nPointsInHull++] = pointArray[i];
            }
        }

        for(int i = 0; i < nPointsInHull && nPointsInHull > 3; ++i)
        {
            if(pointArray[i].equals(pointArray[(i+1)%nPointsInHull]))
            {
                for(int j = i; j+1 < nPointsInHull; ++j)
                    pointArray[j] = pointArray[j+1];
                --nPointsInHull;
                --i;
                continue;
            }

            Vector2 dirA = pointArray[(i+1)%nPointsInHull] - pointArray[i];
            dirA.normalize();
            Vector2 dirB = pointArray[i] - pointArray[(i+nPointsInHull-1)%nPointsInHull];
            dirB.normalize();
            if(dirA.dotProduct(dirB) >= 1.f - 1e-3f)
            {
                for(int j = i; j+1 < nPointsInHull; ++j)
                    pointArray[j] = pointArray[j+1];
                --nPointsInHull;
                --i;
                continue;
            }
        }

        return nPointsInHull;
    }