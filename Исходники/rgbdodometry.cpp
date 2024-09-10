void RGBDOdometry::getIncrementalTransformation(Eigen::Vector3f & trans,
                                                Eigen::Matrix<float, 3, 3, Eigen::RowMajor> & rot,
                                                const bool & rgbOnly,
                                                const float & icpWeight,
                                                const bool & pyramid,
                                                const bool & fastOdom,
                                                const bool & so3)
{
    bool icp = !rgbOnly && icpWeight > 0;
    bool rgb = rgbOnly || icpWeight < 100;

    Eigen::Matrix<float, 3, 3, Eigen::RowMajor> Rprev = rot;
    Eigen::Vector3f tprev = trans;

    Eigen::Matrix<float, 3, 3, Eigen::RowMajor> Rcurr = Rprev;
    Eigen::Vector3f tcurr = tprev;

    if(rgb)
    {
        for(int i = 0; i < NUM_PYRS; i++)
        {
            computeDerivativeImages(nextImage[i], nextdIdx[i], nextdIdy[i]);
        }
    }

    Eigen::Matrix<double, 3, 3, Eigen::RowMajor> resultR = Eigen::Matrix<double, 3, 3, Eigen::RowMajor>::Identity();

    if(so3)
    {
        int pyramidLevel = 2;

        Eigen::Matrix<float, 3, 3, Eigen::RowMajor> R_lr = Eigen::Matrix<float, 3, 3, Eigen::RowMajor>::Identity();

        Eigen::Matrix<double, 3, 3, Eigen::RowMajor> K = Eigen::Matrix<double, 3, 3, Eigen::RowMajor>::Zero();

        K(0, 0) = intr(pyramidLevel).fx;
        K(1, 1) = intr(pyramidLevel).fy;
        K(0, 2) = intr(pyramidLevel).cx;
        K(1, 2) = intr(pyramidLevel).cy;
        K(2, 2) = 1;

        float lastError = std::numeric_limits<float>::max() / 2;
        float lastCount = std::numeric_limits<float>::max() / 2;

        Eigen::Matrix<double, 3, 3, Eigen::RowMajor> lastResultR = Eigen::Matrix<double, 3, 3, Eigen::RowMajor>::Identity();

        for(int i = 0; i < 10; i++)
        {
            Eigen::Matrix<float, 3, 3, Eigen::RowMajor> jtj;
            Eigen::Matrix<float, 3, 1> jtr;

            Eigen::Matrix<double, 3, 3, Eigen::RowMajor> homography = K * resultR * K.inverse();

            mat33 imageBasis;
            memcpy(&imageBasis.data[0], homography.cast<float>().eval().data(), sizeof(mat33));

            Eigen::Matrix<double, 3, 3, Eigen::RowMajor> K_inv = K.inverse();
            mat33 kinv;
            memcpy(&kinv.data[0], K_inv.cast<float>().eval().data(), sizeof(mat33));

            Eigen::Matrix<double, 3, 3, Eigen::RowMajor> K_R_lr = K * resultR;
            mat33 krlr;
            memcpy(&krlr.data[0], K_R_lr.cast<float>().eval().data(), sizeof(mat33));

            float residual[2];

            TICK("so3Step");
            so3Step(lastNextImage[pyramidLevel],
                    nextImage[pyramidLevel],
                    imageBasis,
                    kinv,
                    krlr,
                    sumDataSO3,
                    outDataSO3,
                    jtj.data(),
                    jtr.data(),
                    &residual[0],
                    GPUConfig::getInstance().so3StepThreads,
                    GPUConfig::getInstance().so3StepBlocks);
            TOCK("so3Step");

            lastSO3Error = sqrt(residual[0]) / residual[1];
            lastSO3Count = residual[1];

            //Converged
            if(lastSO3Error < lastError && lastCount == lastSO3Count)
            {
                break;
            }
            else if(lastSO3Error > lastError + 0.001) //Diverging
            {
                lastSO3Error = lastError;
                lastSO3Count = lastCount;
                resultR = lastResultR;
                break;
            }

            lastError = lastSO3Error;
            lastCount = lastSO3Count;
            lastResultR = resultR;

            Eigen::Vector3f delta = jtj.ldlt().solve(jtr);

            Eigen::Matrix<double, 3, 3, Eigen::RowMajor> rotUpdate = OdometryProvider::rodrigues(delta.cast<double>());

            R_lr = rotUpdate.cast<float>() * R_lr;

            for(int x = 0; x < 3; x++)
            {
                for(int y = 0; y < 3; y++)
                {
                    resultR(x, y) = R_lr(x, y);
                }
            }
        }
    }

    iterations[0] = fastOdom ? 3 : 10;
    iterations[1] = pyramid ? 5 : 0;
    iterations[2] = pyramid ? 4 : 0;

    Eigen::Matrix<float, 3, 3, Eigen::RowMajor> Rprev_inv = Rprev.inverse();
    mat33 device_Rprev_inv = Rprev_inv;
    float3 device_tprev = *reinterpret_cast<float3*>(tprev.data());

    Eigen::Matrix<double, 4, 4, Eigen::RowMajor> resultRt = Eigen::Matrix<double, 4, 4, Eigen::RowMajor>::Identity();

    if(so3)
    {
        for(int x = 0; x < 3; x++)
        {
            for(int y = 0; y < 3; y++)
            {
                resultRt(x, y) = resultR(x, y);
            }
        }
    }

    for(int i = NUM_PYRS - 1; i >= 0; i--)
    {
        if(rgb)
        {
            projectToPointCloud(lastDepth[i], pointClouds[i], intr, i);
        }

        Eigen::Matrix<double, 3, 3, Eigen::RowMajor> K = Eigen::Matrix<double, 3, 3, Eigen::RowMajor>::Zero();

        K(0, 0) = intr(i).fx;
        K(1, 1) = intr(i).fy;
        K(0, 2) = intr(i).cx;
        K(1, 2) = intr(i).cy;
        K(2, 2) = 1;

        lastRGBError = std::numeric_limits<float>::max();

        for(int j = 0; j < iterations[i]; j++)
        {
            Eigen::Matrix<double, 4, 4, Eigen::RowMajor> Rt = resultRt.inverse();

            Eigen::Matrix<double, 3, 3, Eigen::RowMajor> R = Rt.topLeftCorner(3, 3);

            Eigen::Matrix<double, 3, 3, Eigen::RowMajor> KRK_inv = K * R * K.inverse();
            mat33 krkInv;
            memcpy(&krkInv.data[0], KRK_inv.cast<float>().eval().data(), sizeof(mat33));

            Eigen::Vector3d Kt = Rt.topRightCorner(3, 1);
            Kt = K * Kt;
            float3 kt = {(float)Kt(0), (float)Kt(1), (float)Kt(2)};

            int sigma = 0;
            int rgbSize = 0;

            if(rgb)
            {
                TICK("computeRgbResidual");
                computeRgbResidual(pow(minimumGradientMagnitudes[i], 2.0) / pow(sobelScale, 2.0),
                                   nextdIdx[i],
                                   nextdIdy[i],
                                   lastDepth[i],
                                   nextDepth[i],
                                   lastImage[i],
                                   nextImage[i],
                                   corresImg[i],
                                   sumResidualRGB,
                                   maxDepthDeltaRGB,
                                   kt,
                                   krkInv,
                                   sigma,
                                   rgbSize,
                                   GPUConfig::getInstance().rgbResThreads,
                                   GPUConfig::getInstance().rgbResBlocks);
                TOCK("computeRgbResidual");
            }

            float sigmaVal = std::sqrt((float)sigma / rgbSize == 0 ? 1 : rgbSize);
            float rgbError = std::sqrt(sigma) / (rgbSize == 0 ? 1 : rgbSize);

            if(rgbOnly && rgbError > lastRGBError)
            {
                break;
            }

            lastRGBError = rgbError;
            lastRGBCount = rgbSize;

            if(rgbOnly)
            {
                sigmaVal = -1; //Signals the internal optimisation to weight evenly
            }

            Eigen::Matrix<float, 6, 6, Eigen::RowMajor> A_icp;
            Eigen::Matrix<float, 6, 1> b_icp;

            mat33 device_Rcurr = Rcurr;
            float3 device_tcurr = *reinterpret_cast<float3*>(tcurr.data());

            DeviceArray2D<float>& vmap_curr = vmaps_curr_[i];
            DeviceArray2D<float>& nmap_curr = nmaps_curr_[i];

            DeviceArray2D<float>& vmap_g_prev = vmaps_g_prev_[i];
            DeviceArray2D<float>& nmap_g_prev = nmaps_g_prev_[i];

            float residual[2];

            if(icp)
            {
                TICK("icpStep");
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
                        sumDataSE3,
                        outDataSE3,
                        A_icp.data(),
                        b_icp.data(),
                        &residual[0],
                        GPUConfig::getInstance().icpStepThreads,
                        GPUConfig::getInstance().icpStepBlocks);
                TOCK("icpStep");
            }

            lastICPError = sqrt(residual[0]) / residual[1];
            lastICPCount = residual[1];

            Eigen::Matrix<float, 6, 6, Eigen::RowMajor> A_rgbd;
            Eigen::Matrix<float, 6, 1> b_rgbd;

            if(rgb)
            {
                TICK("rgbStep");
                rgbStep(corresImg[i],
                        sigmaVal,
                        pointClouds[i],
                        intr(i).fx,
                        intr(i).fy,
                        nextdIdx[i],
                        nextdIdy[i],
                        sobelScale,
                        sumDataSE3,
                        outDataSE3,
                        A_rgbd.data(),
                        b_rgbd.data(),
                        GPUConfig::getInstance().rgbStepThreads,
                        GPUConfig::getInstance().rgbStepBlocks);
                TOCK("rgbStep");
            }

            Eigen::Matrix<double, 6, 1> result;
            Eigen::Matrix<double, 6, 6, Eigen::RowMajor> dA_rgbd = A_rgbd.cast<double>();
            Eigen::Matrix<double, 6, 6, Eigen::RowMajor> dA_icp = A_icp.cast<double>();
            Eigen::Matrix<double, 6, 1> db_rgbd = b_rgbd.cast<double>();
            Eigen::Matrix<double, 6, 1> db_icp = b_icp.cast<double>();

            if(icp && rgb)
            {
                double w = icpWeight;
                lastA = dA_rgbd + w * w * dA_icp;
                lastb = db_rgbd + w * db_icp;
                result = lastA.ldlt().solve(lastb);
            }
            else if(icp)
            {
                lastA = dA_icp;
                lastb = db_icp;
                result = lastA.ldlt().solve(lastb);
            }
            else if(rgb)
            {
                lastA = dA_rgbd;
                lastb = db_rgbd;
                result = lastA.ldlt().solve(lastb);
            }
            else
            {
                assert(false && "Control shouldn't reach here");
            }

            Eigen::Isometry3f rgbOdom;

            OdometryProvider::computeUpdateSE3(resultRt, result, rgbOdom);

            Eigen::Isometry3f currentT;
            currentT.setIdentity();
            currentT.rotate(Rprev);
            currentT.translation() = tprev;

            currentT = currentT * rgbOdom.inverse();

            tcurr = currentT.translation();
            Rcurr = currentT.rotation();
        }
    }

    if(rgb && (tcurr - tprev).norm() > 0.3)
    {
        Rcurr = Rprev;
        tcurr = tprev;
    }

    if(so3)
    {
        for(int i = 0; i < NUM_PYRS; i++)
        {
            std::swap(lastNextImage[i], nextImage[i]);
        }
    }

    trans = tcurr;
    rot = Rcurr;
}