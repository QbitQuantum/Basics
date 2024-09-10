void ICPOdometry::getIncrementalTransformation(Eigen::Vector3f & trans, Eigen::Matrix<float, 3, 3, Eigen::RowMajor> & rot, int threads, int blocks)
{
    iterations[0] = 10;
    iterations[1] = 5;
    iterations[2] = 4;

    Eigen::Matrix<float, 3, 3, Eigen::RowMajor> Rprev = rot;
    Eigen::Vector3f tprev = trans;

    Eigen::Matrix<float, 3, 3, Eigen::RowMajor> Rcurr = Rprev;
    Eigen::Vector3f tcurr = tprev;

    Eigen::Matrix<float, 3, 3, Eigen::RowMajor> Rprev_inv = Rprev.inverse();
    Mat33 & device_Rprev_inv = device_cast<Mat33>(Rprev_inv);
    float3& device_tprev = device_cast<float3>(tprev);

    cv::Mat resultRt = cv::Mat::eye(4, 4, CV_64FC1);

    for(int i = NUM_PYRS - 1; i >= 0; i--)
    {
        for(int j = 0; j < iterations[i]; j++)
        {
            Eigen::Matrix<float, 6, 6, Eigen::RowMajor> A_icp;
            Eigen::Matrix<float, 6, 1> b_icp;

            Mat33&  device_Rcurr = device_cast<Mat33> (Rcurr);
            float3& device_tcurr = device_cast<float3>(tcurr);

            DeviceArray2D<float>& vmap_curr = vmaps_curr_[i];
            DeviceArray2D<float>& nmap_curr = nmaps_curr_[i];

            DeviceArray2D<float>& vmap_g_prev = vmaps_g_prev_[i];
            DeviceArray2D<float>& nmap_g_prev = nmaps_g_prev_[i];

            float residual[2];

            icpStep(device_Rcurr,
                    device_tcurr,
                    vmap_curr,
                    nmap_curr,
                    device_Rprev_inv,
                    device_tprev,
                    intr(i),
                    vmap_g_prev,
                    nmap_g_prev,
                    distThres_,
                    angleThres_,
                    sumData,
                    outData,
                    A_icp.data(),
                    b_icp.data(),
                    &residual[0],
                    threads,
                    blocks);

            lastICPError = sqrt(residual[0]) / residual[1];
            lastICPCount = residual[1];

            Eigen::Matrix<double, 6, 1> result;
            Eigen::Matrix<double, 6, 6, Eigen::RowMajor> dA_icp = A_icp.cast<double>();
            Eigen::Matrix<double, 6, 1> db_icp = b_icp.cast<double>();

            lastA = dA_icp;
            lastb = db_icp;
            result = lastA.ldlt().solve(lastb);

            Eigen::Isometry3f incOdom;

            OdometryProvider::computeProjectiveMatrix(resultRt, result, incOdom);

            Eigen::Isometry3f currentT;
            currentT.setIdentity();
            currentT.rotate(Rprev);
            currentT.translation() = tprev;

            currentT = currentT * incOdom.inverse();

            tcurr = currentT.translation();
            Rcurr = currentT.rotation();
        }
    }

    trans = tcurr;
    rot = Rcurr;
}