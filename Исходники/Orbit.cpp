void cOrbit::FromPositionAndVelocity(cOrbit &out, const cBody &referenceBody, const Vector3d &position, const Vector3d &velocity, double t) 
{
    double mu = referenceBody.GravitationalParameter();
    double r = position.norm();
    double v = velocity.norm();
    Vector3d specificAngularMomentum = position.cross(velocity);
    Vector3d nodeVector;
    if (specificAngularMomentum(0) != 0.0 || specificAngularMomentum(1) != 0.0) 
    {
        nodeVector = Vector3d(-specificAngularMomentum(1), specificAngularMomentum(0), 0).normalized();
    } else {
        nodeVector = Vector3d(1, 0, 0);
    }
    Vector3d eccentricityVector = ((1 / mu) * velocity.cross(specificAngularMomentum)) - position.normalized();
    double semiMajorAxis = 1 / (2 / r - v * v / mu);
    double eccentricity = eccentricityVector.norm();    
    double inclination = std::acos(specificAngularMomentum[2] / specificAngularMomentum.norm());
    double longAscNode, argPeriaps;
    if (eccentricity == 0.0) {
        argPeriaps = 0;
        longAscNode = 0;
    } else {
        longAscNode = std::acos(nodeVector[0]);
        if (nodeVector[1] < 0) {
            longAscNode = TWO_PI - longAscNode;
        }
        argPeriaps = std::acos(nodeVector.dot(eccentricityVector) / eccentricity);
        if (eccentricityVector[2] < 0) {
            argPeriaps = TWO_PI - argPeriaps;
        }
    }
    double trueAnomaly = std::acos(eccentricityVector.dot(position) / (eccentricity * r));
    if (position.dot(velocity) < 0) 
    {
        trueAnomaly = -trueAnomaly;
    }

    out.Reset(&referenceBody, semiMajorAxis, eccentricity, inclination, longAscNode, argPeriaps, 0, 0);

    out.m_meanAnomalyAtEpoch = out.MeanAnomalyAtTrueAnomaly(trueAnomaly);
    out.m_timeOfPeriapsisPassage = t - out.m_meanAnomalyAtEpoch / out.MeanMotion();
}