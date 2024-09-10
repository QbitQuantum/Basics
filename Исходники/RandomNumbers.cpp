void ompl::RNG::uniformProlateHyperspheroid(const std::shared_ptr<const ProlateHyperspheroid>  &phsPtr, double value[])
{
    // Variables
    // The spherical point as a std::vector
    std::vector<double> sphere(phsPtr->getDimension());

    // Get a random point in the sphere
    uniformInBall(1.0, phsPtr->getDimension(), &sphere[0]);

    // Transform to the PHS
    phsPtr->transform(&sphere[0], value);
}