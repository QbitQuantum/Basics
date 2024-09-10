void StarCamera::calculateSpotVectors()
{
    if(mSpots.empty())
        throw std::runtime_error("No extracted spots in List");

    bool zeroNorm = !(mDistortionCoeffi.norm() != 0.0f);

    // Clear SpotVectors
    mSpotVectors.clear();

    std::vector<Spot>::iterator pSpot;
    for(pSpot=mSpots.begin(); pSpot != mSpots.end(); ++pSpot)
    {
        // Substract principal point and divide by the focal length

        Eigen::Vector2f Xd(pSpot->center.x, pSpot->center.y);
        Xd = (Xd - mPrincipalPoint).array() / mFocalLength.array();

        // Undo skew
        Xd(0) = Xd(0) - mPixelSkew * Xd(1);

        Eigen::Vector3f spotVec;
        if(!zeroNorm)  // Use epsilon environment?
        {
            Xd = undistortRadialTangential(Xd);
        }
        spotVec << Xd(0), Xd(1), 1.0f;
        spotVec.normalize();
        mSpotVectors.push_back(spotVec);
    }
}