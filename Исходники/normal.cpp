static void facets (const Vector3d& EPoint, const TNORMAL *Tnormal, Vector3d& normal, TraceThreadData *Thread)
{
    int      i;
    int      thisseed;
    DBL      sum, minsum;
    Vector3d sv, tv, dv, t1, add, newnormal, pert;
    DBL      scale;
    int      UseSquare;
    int      UseUnity;
    DBL      Metric;

    Vector3d *cv = Thread->Facets_Cube;
    Metric = dynamic_cast<FacetsPattern*>(Tnormal->pattern.get())->facetsMetric;

    UseSquare = (Metric == 2 );
    UseUnity  = (Metric == 1 );

    normal.normalize();

    if ( dynamic_cast<FacetsPattern*>(Tnormal->pattern.get())->facetsCoords )
    {
        tv = EPoint;
    }
    else
    {
        tv = normal;
    }

    if ( dynamic_cast<FacetsPattern*>(Tnormal->pattern.get())->facetsSize < 1e-6 )
    {
        scale = 1e6;
    }
    else
    {
        scale = 1. / dynamic_cast<FacetsPattern*>(Tnormal->pattern.get())->facetsSize;
    }

    tv *= scale;

    /*
     * Check to see if the input point is in the same unit cube as the last
     * call to this function, to use cache of cubelets for speed.
     */

    thisseed = PickInCube(tv, t1);

    if (thisseed != Thread->Facets_Last_Seed)
    {
        /*
         * No, not same unit cube.  Calculate the random points for this new
         * cube and its 80 neighbours which differ in any axis by 1 or 2.
         * Why distance of 2?  If there is 1 point in each cube, located
         * randomly, it is possible for the closest random point to be in the
         * cube 2 over, or the one two over and one up.  It is NOT possible
         * for it to be two over and two up.  Picture a 3x3x3 cube with 9 more
         * cubes glued onto each face.
         */

        /* Now store a points for this cube and each of the 80 neighbour cubes. */

        int cvc = 0;

        for (add[X] = -2.0; add[X] < 2.5; add[X] +=1.0)
        {
            for (add[Y] = -2.0; add[Y] < 2.5; add[Y] += 1.0)
            {
                for (add[Z] = -2.0; add[Z] < 2.5; add[Z] += 1.0)
                {
                    /* For each cubelet in a 5x5 cube. */

                    if ((fabs(add[X])>1.5)+(fabs(add[Y])>1.5)+(fabs(add[Z])>1.5) <= 1.0)
                    {
                        /* Yes, it's within a 3d knight move away. */

                        sv = tv + add;

                        PickInCube(sv, t1);

                        cv[cvc] = t1;
                        cvc++;
                    }
                }
            }
        }

        Thread->Facets_Last_Seed = thisseed;
        Thread->Facets_CVC = cvc;
    }

    /*
     * Find the point with the shortest distance from the input point.
     */

    dv = cv[0] - tv;
    if ( UseSquare )
    {
        minsum  = dv.lengthSqr();
    }
    else if ( UseUnity )
    {
        minsum = dv[X]+dv[Y]+dv[Z];
    }
    else
    {
        minsum = pow(fabs(dv[X]), Metric)+
                 pow(fabs(dv[Y]), Metric)+
                 pow(fabs(dv[Z]), Metric);
    }

    newnormal = cv[0];

    /* Loop for the 81 cubelets to find closest. */

    for (i = 1; i < Thread->Facets_CVC; i++)
    {
        dv = cv[i] - tv;

        if ( UseSquare )
        {
            sum  = dv.lengthSqr();
        }
        else
        {
            if ( UseUnity )
            {
                sum = dv[X]+dv[Y]+dv[Z];
            }
            else
            {
                sum = pow(fabs(dv[X]), Metric)+
                      pow(fabs(dv[Y]), Metric)+
                      pow(fabs(dv[Z]), Metric);
            }
        }

        if (sum < minsum)
        {
            minsum = sum;
            newnormal = cv[i];
        }
    }

    if ( dynamic_cast<FacetsPattern*>(Tnormal->pattern.get())->facetsCoords )
    {
        DNoise( pert, newnormal );
        sum = dot(pert, normal);
        newnormal = normal * sum;
        pert -= newnormal;
        normal += dynamic_cast<FacetsPattern*>(Tnormal->pattern.get())->facetsCoords * pert;
    }
    else
    {
        normal = newnormal;
    }
}