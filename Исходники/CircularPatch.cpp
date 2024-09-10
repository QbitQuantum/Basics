ctype CircularPatch<ctype>::distanceTo(const StaticVector<ctype,3> &p) const
{
    int i, j;
    ctype bestDist = std::numeric_limits<ctype>::max();

    // check point against triangles
    for (j=0; j<size(); j++){

        const DomainTriangle<ctype>& cT = par->triangles(triangles[j]);

        StaticVector<ctype,3> triPoints[3];
        triPoints[0] = par->vertices(cT.vertices[0]);
        triPoints[1] = par->vertices(cT.vertices[1]);
        triPoints[2] = par->vertices(cT.vertices[2]);

        // local base
        StaticVector<ctype,3> a = triPoints[1] - triPoints[0];
        StaticVector<ctype,3> b = triPoints[2] - triPoints[0];
        StaticVector<ctype,3> c = a.cross(b);
        c.normalize();

        StaticVector<ctype,3> x = p - triPoints[0];

        // write x in the new base  (Cramer's rule)
        StaticMatrix<ctype,3> numerator(a, b, c);
        StaticMatrix<ctype,3> alphaMat(x, b, c);
        StaticMatrix<ctype,3> betaMat(a, x, c);
        StaticMatrix<ctype,3> gammaMat(a, b, x);

        ctype alpha = alphaMat.det()/numerator.det();
        ctype beta  = betaMat.det()/numerator.det();
        ctype gamma = gammaMat.det()/numerator.det();

        // check whether orthogonal projection onto the ab plane is in triangle
        bool isIn = alpha>=0 && beta>=0 && (1-alpha-beta)>=0;

        if (isIn && fabs(gamma)<bestDist){

            //              printf("a(%1.2f %1.2f %1.2f) b(%1.2f %1.2f %1.2f)  c(%1.2f %1.2f %1.2f)  x(%1.2f %1.2f %1.2f)\n",
            //                     a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z, x.x, x.y, x.z);

            //              printf("tri: %d, alpha = %f, beta = %f, gamma = %f\n", j, alpha, beta, gamma);

            bestDist = fabs(gamma);
        }
    }

    // check point against edges
    for (i=0; i<size(); i++){
        for (j=0; j<3; j++){

            const DomainTriangle<ctype>& cT = par->triangles(triangles[i]);

            StaticVector<ctype,3> from = par->vertices(cT.vertices[j]);
            StaticVector<ctype,3> to   = par->vertices(cT.vertices[(j+1)%3]);

            StaticVector<ctype,3> edge = to - from;

            ctype projectLength = edge.dot(p - from)/edge.length();
            StaticVector<ctype,3> projection = edge/edge.length() * projectLength;

            ctype orthoDist = ((p-from) - projection).length();

            if (projectLength>=0 && projectLength<=edge.length() && orthoDist<bestDist)
                bestDist = orthoDist;
        }
    }

    // check point against vertices
    for (i=0; i<size(); i++){
        for (j=0; j<3; j++){
            ctype dist = (p - par->vertices(par->triangles(triangles[i]).vertices[j])).length();
            if (dist < bestDist){
                bestDist = dist;
            }
        }
    }

    return bestDist;
}