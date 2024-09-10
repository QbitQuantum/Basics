void PolygonLine :: computeNormalSignDist(double &oDist, const FloatArray &iPoint) const
{
    const FloatArray &point = {iPoint[0], iPoint[1]};

    oDist = std :: numeric_limits< double > :: max();
    int numSeg = this->giveNrVertices() - 1;

    // TODO: This can probably be done in a nicer way.
    // Ensure that we work in 2d.
    const int dim = 2;

    for ( int segId = 1; segId <= numSeg; segId++ ) {
        // Crack segment
        const FloatArray &crackP1( this->giveVertex ( segId ) );

        const FloatArray &crackP2( this->giveVertex ( segId + 1 ) );

        double dist2 = 0.0;
        if ( segId == 1 ) {
            // Vector from start P1 to point X
            FloatArray u = {point.at(1) - crackP1.at(1), point.at(2) - crackP1.at(2)};

            // Line tangent vector
            FloatArray t = {crackP2.at(1) - crackP1.at(1), crackP2.at(2) - crackP1.at(2)};
            double l2 = t.computeSquaredNorm();

            if ( l2 > 0.0 ) {
                double l = t.normalize();
                double s = dot(u, t);

                if ( s > l ) {
                    // X is closest to P2
                    dist2 = point.distance_square(crackP2);
                } else {
                    double xi = s / l;
                    FloatArray q = ( 1.0 - xi ) * crackP1 + xi * crackP2;
                    dist2 = point.distance_square(q);
                }
            } else {
                // If the points P1 and P2 coincide,
                // we can compute the distance to any
                // of these points.
                dist2 = point.distance_square(crackP1);
            }
        } else if ( segId == numSeg ) {
            // Vector from start P1 to point X
            FloatArray u = {point.at(1) - crackP1.at(1), point.at(2) - crackP1.at(2)};

            // Line tangent vector
            FloatArray t = {crackP2.at(1) - crackP1.at(1), crackP2.at(2) - crackP1.at(2)};
            double l2 = t.computeSquaredNorm();

            if ( l2 > 0.0 ) {
                double l = t.normalize();
                double s = dot(u, t);

                if ( s < 0.0 ) {
                    // X is closest to P1
                    dist2 = point.distance_square(crackP1);
                } else {
                    double xi = s / l;
                    FloatArray q = ( 1.0 - xi ) * crackP1 + xi * crackP2;
                    dist2 = point.distance_square(q);
                }
            } else {
                // If the points P1 and P2 coincide,
                // we can compute the distance to any
                // of these points.
                dist2 = point.distance_square(crackP1);
            }
        } else {
            double arcPos = -1.0, dummy;
            dist2 = point.distance_square(crackP1, crackP2, arcPos, dummy);
        }

        if ( dist2 < oDist*oDist ) {
            FloatArray lineToP;
            lineToP.beDifferenceOf(point, crackP1, dim);

            FloatArray t;
            t.beDifferenceOf(crackP2, crackP1, dim);

            FloatArray n = {-t.at(2), t.at(1)};

            oDist = sgn( lineToP.dotProduct(n) ) * sqrt(dist2);
        }
    }
}