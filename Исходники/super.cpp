int Superellipsoid::find_ray_plane_points(const Vector3d& P, const Vector3d& D, int cnt, DBL *dists, DBL mindist, DBL maxdist) const
{
    int i;
    DBL t, d;

    /* Since min and max dist are the distance to two of the bounding planes
       we are considering, there is a high probablity of missing them due to
       round off error. Therefore we adjust min and max. */

    t = EPSILON * (maxdist - mindist);

    mindist -= t;
    maxdist += t;

    /* Check the sets of planes that cut apart the superquadric. */

    for (i = 0; i < PLANECOUNT; i++)
    {
        d = (D[0] * planes[i][0] + D[1] * planes[i][1] + D[2] * planes[i][2]);

        if (fabs(d) < EPSILON)
        {
            /* Can't possibly get a hit for this combination of ray and plane. */

            continue;
        }

        t = (planes[i][3] - (P[0] * planes[i][0] + P[1] * planes[i][1] + P[2] * planes[i][2])) / d;

        if ((t >= mindist) && (t <= maxdist))
        {
            dists[cnt++] = t;
        }
    }

    /* Sort the results for further processing. */

    QSORT(reinterpret_cast<void *>(dists), cnt, sizeof(DBL), compdists);

    return(cnt);
}