double MultitouchNavigation::angleBetween3DVectors(osg::Vec3 v1, osg::Vec3 v2)
{
    // http://codered.sat.qc.ca/redmine/projects/spinframework/repository/revisions/b6245189c19a7c6ba4fdb126940321c41c44e228/raw/src/spin/osgUtil.cpp

    // normalize vectors (note: this must be done alone, not within any vector arithmetic. why?!)
    v1.normalize();
    v2.normalize();

    // Get the dot product of the vectors
    double dotProduct = v1 * v2;

    // for acos, the value has to be between -1.0 and 1.0, but due to numerical imprecisions it sometimes comes outside this range
    if (dotProduct > 1.0)
        dotProduct = 1.0;
    if (dotProduct < -1.0)
        dotProduct = -1.0;

    // Get the angle in radians between the 2 vectors (should this be -acos ? ie, negative?)
    double angle = acos(dotProduct);

    // Here we make sure that the angle is not a -1.#IND0000000 number, which means indefinite
    if (std::isnan(angle)) //__isnand(x)
        return 0;

    // Return the angle in radians
    return (angle);
}