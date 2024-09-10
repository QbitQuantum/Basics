void MarkerLocator::TVectToRangeBaring(Mat r_tVec, double& rr_range, double& rr_bearing)
{
    // Get the vector relative to the robot rather than the camera
    subtract(r_tVec, m_robotLoc, r_tVec);

    // Start by projecting our transform vector onto the robot's plane
    ChangeSpace(r_tVec);

    // Range is easy
    rr_range = sqrt(r_tVec.dot(r_tVec));
    rr_bearing = atan(r_tVec.at<double>(0, 0)/r_tVec.at<double>(2, 0));
}