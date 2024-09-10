/** Get the inliers among all matches that comply with a given fundamental matrix.
 * @param std::vector<Match> vector with feature matches
 * @param Eigen::Matrix3f fundamental matrix
 * @return std::vector<int> vector with indices of the inliers */
std::vector<int> MonoOdometer5::getInliers(std::vector<Match> matches, Eigen::Matrix3f F)
{
    std::vector<int> inlierIndices;
    
    for(int i=0; i<matches.size(); i++)
    {
        cv::Point2f pPrev = matches[i].pPrev_;
        cv::Point2f pCurr = matches[i].pCurr_;
        Eigen::Vector3f pPrevHomog, pCurrHomog;
        pPrevHomog << pPrev.x, pPrev.y, 1.0;
        pCurrHomog << pCurr.x, pCurr.y, 1.0;

		// xCurr^T * F * xPrev 
        double x2tFx1 = pCurrHomog.transpose() * F * pPrevHomog;

		// F * xPrev
        Eigen::Vector3f Fx1 = F * pPrevHomog;
		
		// F^T * xCurr
        Eigen::Vector3f Ftx2 = F.transpose() * pCurrHomog;
        
		// compute Sampson distance (distance to epipolar line)
        double dSampson = (x2tFx1 * x2tFx1) / ((Fx1(0)*Fx1(0)) + (Fx1(1)*Fx1(1)) + (Ftx2(0)*Ftx2(0)) + (Ftx2(1)*Ftx2(1)));

        if(dSampson < param_odometerInlierThreshold_)
        {
            inlierIndices.push_back(i);
        }
    }
    return inlierIndices;
}