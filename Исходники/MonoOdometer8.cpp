/** Estimate monocular visual odometry.
 * @param std::vector<Match> vector with matches
 * @param Eigen::Matrix3f& (output) estimated rotation matrix
 * @param Eigen::Vector3f& (output) estimated translation vector
 * @param bool show optical flow (true), don't show otherwise
 * @param std::vector<Match> output vector with all inlier matches
 * @param std::vector<Eigen::Vector3f> output vector with 3D points, triangulated from all inlier matches
 * @return bool true is motion successfully estimated, false otherwise */
bool MonoOdometer8::estimateMotion(std::vector<Match> matches, Eigen::Matrix3f &R, Eigen::Vector3f &t, bool showOpticalFlow, std::vector<Match> &inlierMatches, std::vector<Eigen::Vector3f> &points3D)
{
    // check number of correspondences
    int N = matches.size();
    if(N < param_odometerMinNumberMatches_)
    {
        // too few matches to compute F
        R = Eigen::Matrix3f::Identity();
        t << 0.0, 0.0, 0.0;
        return false;
    }

    // normalize 2D features
    Eigen::Matrix3f NormTPrev, NormTCurr;
    std::vector<Match> matchesNorm = normalize2DPoints(matches, NormTPrev, NormTCurr);

    Eigen::Matrix3f F, E;
    std::vector<int> inlierIndices;
		
    // RANSAC loop
    for(int j=0; j<param_odometerRansacIters_; j++)
    {
        // get random sample
        std::vector<int> chosenIndices = getRandomSample(matchesNorm.size(), 8);
            
        // compute fundamental matrix
        F = getF(matchesNorm, chosenIndices);
            
        // get inliers
        std::vector<int> inlierIndicesCurr = getInliers(matchesNorm, F);
            
        if(inlierIndicesCurr.size() > inlierIndices.size())
        {
                inlierIndices = inlierIndicesCurr;
        }
    }

    // check number of inliers
    if(inlierIndices.size() < param_odometerMinNumberMatches_)
    {
        R = Eigen::Matrix3f::Identity();
        t << 0.0, 0.0, 0.0;
        return false;
    }

    // compute fundamental matrix out of all inliers
    F = getF(matchesNorm, inlierIndices);

    // save inlier and outlier matches
    std::vector<Match> outlierMatches;
    for(int i=0; i<matches.size(); i++)
    {
        if(elemInVec(inlierIndices, i))
        {
            inlierMatches.push_back(matches[i]);
        }
        else
        {
            outlierMatches.push_back(matches[i]);
        }
    }

    // plot optical flow and print #inliers (for debugging)
    if(showOpticalFlow)
    {
        cv::Mat image(1024, 768, CV_8UC1, cv::Scalar(0));
        cv::Mat of1 = highlightOpticalFlow(image, inlierMatches, cv::Scalar(0, 255, 0));
        cv::Mat of2 = highlightOpticalFlow(of1, outlierMatches, cv::Scalar(0, 0, 255));
        cv::namedWindow("Optical flow", CV_WINDOW_AUTOSIZE);
        cv::imshow("Optical flow", of2);
        cv::waitKey(10);
    }
    
    // denormalize F
    F = NormTCurr.transpose() * F * NormTPrev;
    
    // compute essential matrix E
    E = F2E(F);

    // get rotation and translation and triangulate points
    Eigen::Matrix<float, 4, Eigen::Dynamic> points3DMat;
    E2Rt(E, inlierMatches, R, t, points3DMat);

    // normalize 3D points (force last coordinate to 0)
    for(int j=0; j<points3DMat.cols(); j++)
    {
        Eigen::Vector3f pt = points3DMat.block<3, 1>(0, j);
        double lastCoord = points3DMat(3, j);
        pt = pt / lastCoord;
        if(pt(2) > 0)
        {
            points3D.push_back(pt);
        }
        else
        {
            // remove match if not a valid point
            inlierMatches.erase(inlierMatches.begin() + j);
        }
    }

    // check number of valid points
    if(points3D.size() < param_odometerMinNumberMatches_)
    {
        R = Eigen::Matrix3f::Identity();
        t << 0.0, 0.0, 0.0;
        return false;
    }

    // inforce translation norm to 1
    t = t / sqrt(t.dot(t));

    return true;
}