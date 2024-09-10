    // This function decides to select a new keyframe when the proposed keyframe does not have keyframes too near/related
    bool shouldSelectKeyframe(Frame360 *candidateKF, std::pair<Eigen::Matrix4f, Eigen::Matrix<float,6,6> > candidateKF_connection, Frame360* currentFrame)
    {
        cout << "shouldSelectKeyframe ...\n";
        double time_start = pcl::getTime();

        RegisterPhotoICP align360; // Dense RGB-D alignment
        align360.setNumPyr(5);
        align360.useSaliency(false);
        align360.setVisualization(true);
        align360.setGrayVariance(3.f/255);

        // The reference of the spherical image and the point Clouds are not the same! I should always use the same coordinate system (TODO)
        float angleOffset = 157.5;
        Eigen::Matrix4f rotOffset = Eigen::Matrix4f::Identity(); rotOffset(1,1) = rotOffset(2,2) = cos(angleOffset*PI/180); rotOffset(1,2) = sin(angleOffset*PI/180); rotOffset(2,1) = -rotOffset(1,2);

        cout << "Align Sphere " << endl;
        double time_start_dense = pcl::getTime();
        align360.setTargetFrame(Map.vpSpheres[nearestKF]->sphereRGB, Map.vpSpheres[nearestKF]->sphereDepth);
        align360.setSourceFrame(candidateKF->sphereRGB, candidateKF->sphereDepth);
        //                align360.alignFrames360(Eigen::Matrix4f::Identity(), RegisterPhotoICP::PHOTO_CONSISTENCY); // PHOTO_CONSISTENCY / DEPTH_CONSISTENCY / PHOTO_DEPTH  Matrix4f relPoseDense = registerer.getPose();
        align360.alignFrames360(rotOffset * candidateKF_connection.first * rotOffset.inverse(), RegisterPhotoICP::PHOTO_DEPTH); // PHOTO_CONSISTENCY / DEPTH_CONSISTENCY / PHOTO_DEPTH  Matrix4f relPoseDense = registerer.getPose();
        Eigen::Matrix4f rigidTransf_dense = rotOffset.inverse() * align360.getOptimalPose() * rotOffset;
        double time_end_dense = pcl::getTime();
        std::cout << "Dense " << (time_end_dense - time_start_dense) << std::endl;
        cout << "Dense regist \n" << rigidTransf_dense << " \nRegist-PbMap \n" << candidateKF_connection.first << endl;

        //        math::mrpt::CPose3D
        if(!rigidTransf_dense.isApprox(candidateKF_connection.first,1e-1))
        {
            std::cout << "shouldSelectKeyframe INVALID KF\n";
            return false;
        }
        else
        {
            candidateKF_connection.first = rigidTransf_dense;
        }

        double dist_candidateKF = candidateKF_connection.first.block(0,3,3,1).norm();
        Eigen::Matrix4f candidateKF_pose = Map.vTrajectoryPoses[nearestKF] * candidateKF_connection.first;
        map<float,unsigned> nearest_KFs;
        for(std::set<unsigned>::iterator itKF = Map.vsAreas[Map.currentArea].begin(); itKF != Map.vsAreas[Map.currentArea].end(); itKF++) // Set the iterator to the previous KFs not matched yet
        {
            if(*itKF == nearestKF)
                continue;

            double dist_to_prev_KF = (candidateKF_pose.block(0,3,3,1) - Map.vTrajectoryPoses[*itKF].block(0,3,3,1)).norm();
            cout << *itKF << " dist_to_prev_KF " << dist_to_prev_KF << " dist_candidateKF " << dist_candidateKF << endl;
            if( dist_to_prev_KF < dist_candidateKF ) // Check if there are even nearer keyframes
                nearest_KFs[dist_to_prev_KF] = *itKF;
        }
        for(map<float,unsigned>::iterator itNearKF = nearest_KFs.begin(); itNearKF != nearest_KFs.end(); itNearKF++) // Set the iterator to the previous KFs not matched yet
        {
            cout << "itNearKF " << itNearKF->first << " " << itNearKF->second << endl;
            bool bGoodRegistration = registerer.RegisterPbMap(Map.vpSpheres[itNearKF->second], candidateKF, MAX_MATCH_PLANES, RegisterRGBD360::PLANAR_3DoF);
            if(bGoodRegistration && registerer.getMatchedPlanes().size() >= min_planes_registration && registerer.getAreaMatched() > 6 )
            {
                nearestKF = itNearKF->second;
                double time_end = pcl::getTime();
                std::cout << "shouldSelectKeyframe INVALID KF. took " << double (time_end - time_start) << std::endl;
                return false;
            }
        }
        double time_end = pcl::getTime();
        std::cout << "shouldSelectKeyframe VALID KF. took " << double (time_end - time_start) << std::endl;
        //      cout << "shouldSelectKeyframe VALID KF\n";
        return true;
    }